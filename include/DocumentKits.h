#ifndef DCOUMENTKITS_H
#define DocumentKits_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>
#include <stdlib.h>

#include "Document.h"
using namespace std;

//封装成工具类，单实例模式
class DocumentKits
{
public:
    DocumentKits();

    ~DocumentKits();

    int loadIndexLib(ifstream &queryindexfile, map<int, string> &indexlib);

    int loadStopWords(ifstream &stopwordsfile, vector<string> &stopwords);

    wstring readWLine(ifstream &utf16file, int &pos);

    int segementWords(const wstring &wline, map<string, int>  &unqwords);

    int removeStopWords(const vector<string> &stopwords, map<string, int> &unqwords);

    string convertWtStr(wstring &wstr);

    int getTopWords(const map<string, int> &unqwords, vector<string> &topwords);

    int delDuplicate(vector<Document *> &documentset);

    int generateAllWordsSet(const vector<Document *> &documentset, map<string, list<string> > &allwordset);
};

#endif