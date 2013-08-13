#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

class Document
{
public:
	int m_DocPos;
	string m_DocID;
	string m_URL;
	string m_Title;
	int m_ContentPos;
	bool m_isDuplicate;
	map<string, int> m_UnqWords;
	vector<string> m_TopWords;
	map<string, double> m_DocVector;
	
public:
	Document();

	~Document();

	int compareDocuments(Document &otherdoc);

	bool operator== (const Document &otherdoc);

	bool operator!= (const Document &otherdoc);
};

#endif