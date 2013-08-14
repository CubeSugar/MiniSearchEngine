#include <vector>
#include "Document.h"

Document::Document()
{
    
}

Document::~Document()
{
	m_DocPos = 0;
	m_DocID = "";
	m_URL = "";
	m_Title = "";
	m_ContentPos = 0;
	m_isDuplicate = false;
	m_UnqWords.clear();
	m_TopWords.clear();
}

int Document::compareDocuments(Document &otherdoc)
{
	int counter = 0;
    
	for (vector<string>::iterator itrthis = this->m_TopWords.begin();
	     itrthis != this->m_TopWords.end();
	     ++itrthis)
	{
		for (vector<string>::iterator itrother = otherdoc.m_TopWords.begin();
		     itrother != otherdoc.m_TopWords.end();
		     ++itrother)
		{
			if (*itrthis == *itrother)
			{
				++counter;
			}
		}
	}
    
	if (counter >= 6)
	{
		//this->m_isDuplicate = true;
		return 1;
	}
	else
	{
		return 0;
	}
}

bool Document::operator== (const Document &otherdoc)
{
	int counter = 0;
    
	for (vector<string>::iterator itrthis = this->m_TopWords.begin();
	     itrthis != this->m_TopWords.end();
	     ++itrthis)
	{
		for (vector<string>::const_iterator itrother = otherdoc.m_TopWords.begin();
		     itrother != otherdoc.m_TopWords.end();
		     ++itrother)
		{
			if (*itrthis == *itrother)
			{
				++counter;
			}
		}
	}
    
	if (counter >= 6)
	{
		//this->m_isDuplicate = true;
		return true;
	}
	else
	{
		return false;
	}
}

bool Document::operator!= (const Document &otherdoc)
{
	return !(*this == otherdoc);
}