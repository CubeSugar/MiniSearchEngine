#include <cmath>
#include "DocumentKits.h"
#include "SegInterface_Use.h"
#include "PosInterface_Use.h"
#include "codetransformer.h"
#include "JTCharCodeConvert.h"

DocumentKits::DocumentKits()
{
    
}

DocumentKits::~DocumentKits()
{
    
}

int DocumentKits::loadIndexLib(ifstream &queryindexfile, map<int, string> &indexlib)
{
    string line;
    string queryword;
    int pos;
    while (getline(queryindexfile, line))
    {
        istringstream stream(line);
        stream >> queryword;
        stream >> pos;
        indexlib[pos] = queryword;
    }
    return 0;
}

int DocumentKits::loadStopWords(ifstream &stopwordsfile, vector<string> &stopwords)
{
	string word;
    while (stopwordsfile >> word)
    {
        stopwords.push_back(word);
    }
	return 0;
}

wstring DocumentKits::readWLine(ifstream &utf16file, int &pos)
{
	char cc[3]={'\0'} ;/*当前读入的字符*/
	char pc[3]={'\0'} ;/*当前的前驱的字符*/
    
    wstring wline = L"";
    
    utf16file.seekg(pos, ios::beg);
    
    bool BeginFlag = false;
    bool EndFlag = false;
    
	while (utf16file.read(cc, 2))
	{
	    //一次读入两个字节
        unsigned short wc;
		
		if (cc[0] == '/' && cc[1] == 0 && pc[0] == '<' && pc[1] == 0)
		{
		    EndFlag = true;
		    continue;
		}
		
		if (cc[0] == '\n' && cc[1] == 0)
		{
		    pos = utf16file.tellg();
		    break;
		}
		
		if (BeginFlag && !EndFlag)
		{
		    wc = (unsigned char)pc[1] ;
		    wc = wc << 8;
		    wc += (unsigned char)pc[0];
            
		    wline += wc;
		}
		
		pc[0] = cc[0];
		pc[1] = cc[1];
		
		BeginFlag = true;
	}
    
    return wline;
}

int DocumentKits::segementWords(const wstring &wline, map<string, int>  &unqwords)
{
	string segwordsstr;
	CCodeTransformer codeTransformer;
    
    try
    {
        wstring wstr_with_black;
        CELUSSegOption::SetSEG_TAG("SingleSpace");
	    wstring SegTag(L" ");
        
	    CELUSSeg::BMMSeg(wline, wstr_with_black);
	    segwordsstr = codeTransformer.wstr2utf(wstr_with_black);
        //log
    }
    catch(...)
    {
        //cout << "error in test, ensure config elus.ini" << endl;
        //log
    }
    
    string word;
    istringstream wordstream(segwordsstr);
    
    //int sum = 0;
    
    while (wordstream >> word)
    {
    	++unqwords[word];
    	//++sum;
    }
    
    /*log
     for (map<string, int>::iterator itr = unqwords.begin(); itr != unqwords.end(); ++itr)
     {
     cout << itr->first << "\t" << itr->second << endl;
     }
     */
	//cout << "sum = " << sum << endl;
    return 0;
}


string DocumentKits::convertWtStr(wstring &wstr)
{
	CCodeTransformer codeTransformer;
	return codeTransformer.wstr2utf(wstr);
}


int DocumentKits::getTopWords(const map<string, int> &unqwords, vector<string> &topwords)
{
    multimap<int, string> unqwordsbyfrq;
    for (map<string, int>::const_iterator itr_unq = unqwords.begin();
         itr_unq != unqwords.end(); ++itr_unq)
    {
        unqwordsbyfrq.insert(make_pair(itr_unq->second, itr_unq->first));
    }
    
    int counter = 10;
    for (multimap<int, string>::reverse_iterator itr_frq = unqwordsbyfrq.rbegin();
         itr_frq != unqwordsbyfrq.rend(); ++itr_frq)
    {
        if (counter < 1)
        {
            break;
        }
        topwords.push_back(itr_frq->second);
        --counter;
    }
    
    return 0;
}

int DocumentKits::removeStopWords(const vector<string> &stopwords, map<string, int> &unqwords)
{
    for (vector<string>::const_iterator itr = stopwords.begin(); itr != stopwords.end(); ++itr)
    {
        unqwords.erase(*itr);
    }
    
    return 0;
}

int DocumentKits::delDuplicate(list<Document *> &documentset)
{
    //itrdocf --> fix
    //itrdocm --> move
    
    for (list<Document *>::iterator itrdocf = documentset.begin();
         itrdocf != documentset.end();
         ++itrdocf)
    {
        //do ++itrdocf at init statement
        list<Document *>::iterator itrdocm = itrdocf;
        ++itrdocm;
        while (itrdocm != documentset.end())
        {
            if (**itrdocf == **itrdocm)
            {
                delete *itrdocm;
                itrdocm = documentset.erase(itrdocm);
            }
            else
            {
                ++itrdocm;
            }
        }
    }
    return 0;
}

int DocumentKits::generateAllWordsSet(const list<Document *> &documentset, map<string, list<string> > &allwordset)
{
    for (list<Document *>::const_iterator itrdoc = documentset.begin();
         itrdoc != documentset.end();
         ++itrdoc)
    {
        for (map<string, int>::const_iterator itrwords = (*itrdoc)->m_UnqWords.begin();
             itrwords != (*itrdoc)->m_UnqWords.end();
             ++itrwords)
        {
            allwordset[itrwords->first].push_back((*itrdoc)->m_DocID);
            
            //int to string
            string pos;
            stringstream sst;
            sst << (*itrdoc)->m_DocPos;
            sst >> pos;
            
            allwordset[itrwords->first].push_back(pos);
        }
    }
    return 0;
}

int DocumentKits::initDocVector(const map<string, list<string> > &allwords, Document &doc)
{
    //cout << "docid = " << doc.m_DocID << endl;
    double len = 0.0;
    for (map<string, int>::iterator itrword = doc.m_UnqWords.begin();
         itrword != doc.m_UnqWords.end();
         ++itrword)
    {
        //cout << "sumw = " << sumw << endl;
        
        map<string, list<string> >::const_iterator itrall = allwords.find(itrword->first);
        
        //cout << "on finding " << endl;
        
        if (itrall != allwords.end())
        {
            //cout << "find & copy" << " ";
            double weight = (itrword->second) * ((itrall->second).size()) / 2;
            doc.m_DocVector[itrword->first] = weight;
            
            //cout << "copy done!" << " ";
            len += weight * weight;
        }
    }
    
    //cout << "sumw = " << sumw << endl;
    
    //gui 1 hua
    for (map<string, double>::iterator itr = doc.m_DocVector.begin();
         itr != doc.m_DocVector.end();
         ++itr)
    {
        itr->second /= sqrt(len);
    }
    
    //cout << "gui 1 hua done!" << endl;
    return 0;
}

double DocumentKits::calcDocSimilarity(const Document &doc1, const Document &doc2)
{
    double similarity = 0.0;
    
    for (map<string, double>::const_iterator itr1 = doc1.m_DocVector.begin();
         itr1 != doc1.m_DocVector.end();
         ++itr1)
    {
        map<string, double>::const_iterator itr2 = doc2.m_DocVector.find(itr1->first);
        if (itr2 != doc2.m_DocVector.end())
        {
            similarity += itr1->second * itr2->second;
        }
    }
    
    return similarity;
}