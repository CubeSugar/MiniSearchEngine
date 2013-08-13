#include <iostream>
#include <fstream>
#include <sstream>
//#include <cstring>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <stdlib.h>
#include <locale>

#include "MiniSearchEngineStd.h"
#include "Document.h"
#include "DocumentKits.h"

using namespace std;

const static int BUF_SIZE = 2*1024*1024;

int main(int argc, char * argv[])
{
    DocumentKits DKits;

    wstring DocID = L"";
    wstring URL = L"";
    wstring Title = L"";
    
    vector<string> StopWords;
    map<int, string> QueryIndex;
    list<Document*> DocumentsSet;
    map<string, list<string> > AllWords;
    
    //设置宽字符环境
    //ios::sync_with_stdio(false);
    //locale::global(locale(""));
    //setlocale(LC_CTYPE, "");
    //wcout.imbue(locale(""));

    //load index lib
    ifstream QueryIndexFile("../data/index.lib");
    if (!QueryIndexFile.is_open())
    {
        cout << "con not open index lib" << endl;
    }

    DKits.loadIndexLib(QueryIndexFile, QueryIndex);

    /*
    for (map<int, string>::iterator itr1 = QueryIndex.begin();
         itr1 != QueryIndex.end();
         ++itr1)
    {
        cout << itr1->first << "\t" << itr1->second <<endl;
    }
    */

    QueryIndexFile.close();

    //load stop words
    ifstream StopWordsFile("../src/stopList.txt");
    if (!StopWordsFile.is_open())
    {
        cout << "can not open stopwordsfile" << endl;
    }

    DKits.loadStopWords(StopWordsFile, StopWords);

    StopWordsFile.close();


	//load ripe page lib
	string infile = "../data/ripepage.lib";
	
	ifstream infs16(infile.c_str());
	if(!infs16.is_open())
	{
		std::cout << "Open error," << infile <<std::endl;
		return 0;
	}
	
    //skip UTF-16 LE BOM
    //int pos = 2;

    wstring wline = L"";
    wstring wtrash = L"";//get trash value

    //get file total number of byte
    infs16.seekg(0, ios::end);
    int length = infs16.tellg();
    infs16.seekg(0, ios::beg);
    //cout << "length = " << length << endl;

    //stop loop condition
    QueryIndex[length + 2] = "";
    
    map<int, string>::iterator itrindex = QueryIndex.begin();
    map<int, string>::iterator nxtindex = QueryIndex.begin();
    ++nxtindex;
    
    int RPFilePos;
    list<Document *> querydocset;
    while (nxtindex != QueryIndex.end())
    {
        RPFilePos = itrindex->first + QueryOffset;     //query
        //cout << itrindex->second << endl;   
        wtrash = DKits.readWLine(infs16, RPFilePos);//query

        while (RPFilePos < (nxtindex->first - QueryOffsetE - 4))
        {   
            Document *Doc = new Document;

            RPFilePos = RPFilePos + DocOffset;
            wtrash = DKits.readWLine(infs16, RPFilePos);//doc

            Doc->m_DocPos = RPFilePos;//docpos

            RPFilePos = RPFilePos + DocIDOffset;
            DocID = DKits.readWLine(infs16, RPFilePos);//docid
            Doc->m_DocID = DKits.convertWtStr(DocID);

            RPFilePos = RPFilePos + URLOffset;
            URL = DKits.readWLine(infs16, RPFilePos);//url
            Doc->m_URL = DKits.convertWtStr(URL);
            //cout << RPFilePos << " " << Doc->m_URL << endl;

            RPFilePos = RPFilePos + TitleOffset;
            Title = DKits.readWLine(infs16, RPFilePos);//title
            Doc->m_Title = DKits.convertWtStr(Title);
            //cout << RPFilePos << " " << Doc->m_Title << endl;

            Doc->m_ContentPos = RPFilePos + ContentOffset;
            //cout << Doc->m_ContentPos << endl;
            
            RPFilePos = RPFilePos + ContentOffset;
            wline = DKits.readWLine(infs16, RPFilePos);//content

            wtrash = DKits.readWLine(infs16, RPFilePos);// </doc>

            DKits.segementWords(wline, Doc->m_UnqWords);
            //cout << "unique word counter = " << Doc->m_UnqWords.size() << endl;
            
            DKits.removeStopWords(StopWords, Doc->m_UnqWords);
            //cout << "unique word counter = " << Doc->m_UnqWords.size() << endl;

            DKits.getTopWords(Doc->m_UnqWords, Doc->m_TopWords);
            //cout << "TopWords size = " << Doc->m_TopWords.size() << endl;

            /*
            for (vector<string>::iterator itr = Doc->m_TopWords.begin();
                 itr != Doc->m_TopWords.end();
                 ++itr)
            {
                cout << *itr << "  ";
            }
            //cout << endl;
            */

            //DocumentsSet.push_back(Doc);
            querydocset.push_back(Doc);
        }


        cout << "before delDuplicate, size = " << querydocset.size() << endl;

        DKits.delDuplicate(querydocset);

        cout << "after delDuplicate, size = " << querydocset.size() << endl;

        DocumentsSet.splice(DocumentsSet.end(), querydocset);

        querydocset.clear();

        ++itrindex;
        ++nxtindex;
        wline = L"";
        wtrash = L"";
    }
    cout << "DocumentsSet size = " << DocumentsSet.size() << endl;
    //cout << "DocumentsSet capa = " << DocumentsSet.capacity() << endl;
	infs16.close();

    DKits.generateAllWordsSet(DocumentsSet, AllWords);

    cout << "all words size = " << AllWords.size() << endl;

    //-----------------------------------------
    map<string, int> DocHash;
    int index = 0;

    for (list<Document *>::iterator itrdoc = DocumentsSet.begin();
         itrdoc != DocumentsSet.end();
         ++itrdoc)
    {
        DocHash[(**itrdoc).m_DocID] = index++;

        DKits.initDocVector(AllWords, **itrdoc);

        cout << "initDocVector = " << index << endl;
    }

    ofstream SmlrtyMtrxFile;
    string outfile = "../data/SmlrtyMtrx.lib";
    SmlrtyMtrxFile.open(outfile.c_str(), ios::out | ios::binary);
    if(!SmlrtyMtrxFile.is_open())
    {
        cout << "Open SmlrtyMtrxFile error," << endl ;
        return 0;
    }


    vector<double> SimilarityMatrix;
    double smlrty = 0.0;
    for (list<Document *>::iterator itrdoci = DocumentsSet.begin();
         itrdoci != DocumentsSet.end();
         ++itrdoci)
    {
        for (list<Document *>::iterator itrdocj = itrdoci;
             itrdocj != DocumentsSet.end();
             ++itrdocj)
        {
            if (itrdocj == itrdoci)
            {
                SimilarityMatrix.push_back(1.0);
                smlrty = 1.0;
                continue;
            }
            else
            {
                smlrty = DKits.calcDocSimilarity(**itrdoci, **itrdocj);
                SimilarityMatrix.push_back(smlrty);
            }
            
            SmlrtyMtrxFile << smlrty << " ";
        }

        SmlrtyMtrxFile << endl;
    }
    
    SmlrtyMtrxFile.close();
    /*
    ofstream AllWordsFile;
    string outfile = "../data/allwods.lib";
    AllWordsFile.open(outfile.c_str(), ios::out | ios::binary);
    if(!AllWordsFile.is_open())
    {
        cout << "Open allwordsfile error," << endl ;
        return 0;
    }

    for (map<string, list<string> >::iterator itrall = AllWords.begin();
         itrall != AllWords.end();
         ++itrall)
    {
        AllWordsFile << itrall->first << "\t";
        for (list<string>::iterator itrdocid = (itrall->second).begin();
             itrdocid != (itrall->second).end();
             ++itrdocid)
        {
            AllWordsFile << *itrdocid << "\t"; //<< *(++itrdocid) << "\t";
        }

        AllWordsFile << endl;
    }

    AllWordsFile.close();
    */

	return 0;
}


