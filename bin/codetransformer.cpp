////////////////////////////////////////////////////////////////
//codetransformer.cpp                                         //
//author: HE, yong                                            //
//Revision: 0.1.0623                                          //
//Last Revise Date: 2006-06-23                                //
////////////////////////////////////////////////////////////////


#include <string>
#include <vector>

#include <mcheck.h>

#include "codetransformer.h"

using namespace std;

extern CDictionary WordDic;
extern Segment segment;

CCodeTransformer::CCodeTransformer()
{
}

CCodeTransformer::~CCodeTransformer()
{
}

void CCodeTransformer::Clear()
{
}

bool CCodeTransformer::IsGb2312(string strraw)
{
  // mtrace();
	if(strraw.size() == 0)
		return false;

  //	segment.initializeInsunAbs();
	wstring chi;
	string strtemp;
	vector<string> *words=new vector<string>;
	
	chi.erase();
	strtemp.erase();


	unsigned int pos = 0;
	int start = 0;
	while((pos = strraw.find("\n", start)) != string::npos)
	{
		strtemp += gb2312_extract(strraw.substr(start, pos - start));

		//��stringת��wstring
		
		chi = GB2WSTR(strtemp);
		
		vector<wstring> wstrvec;
		
		//���÷ִʳ���
		segment(chi, wstrvec);

		string word;
		vector<wstring>::const_iterator p;
		for (p = wstrvec.begin(); p!= wstrvec.end(); ++p)
		{
			word = WSTR2GB(*p);
			words->push_back(word);
		}
		if(chi.size() > 300)
			break;
		start = pos + 1;
	}

	if(chi.size() == 0)
	{
	  	delete words;
		return false;
	}
//	cout<<"gb2312   words = "<<words->size()<<endl;
//	cout<<"gb2312   characters = "<<chi.size()<<endl;
	if((words->size() / chi.size()) < 0.8)
	{
	  	delete words;
		return true;
	}
	else
	{
	  	delete words;
	        return false;
	}
	//	muntrace();
}

bool CCodeTransformer::IsUtf8(string strraw)
{
	if(strraw.size() == 0)
		return false;
//	segment.initializeInsunAbs();
	wstring chi;
	string strtemp;
	vector<string> *words=new vector<string>;
	
	chi.erase();
	strtemp.erase();

	size_t pos = 0, start = 0;
	while((pos = strraw.find("\n", start)) != string::npos)
	{
		if(pos - start > 3)
		{
//cout<<"start = "<<start<<endl;
//cout<<"pos = "<<pos<<endl;
			strtemp += utf8_extract(strraw.substr(start, pos - start));
		}
		else
		{
			start = pos + 1;
			continue;
		}
//cout<<"hello1"<<endl;
		chi = UTF2WSTR(strtemp);
		if(chi.size() == 0)
		{
			start = pos + 1;
			continue;
		}
	
		vector<wstring> wstrvec;
		
		//���÷ִʳ���
		segment(chi, wstrvec);
		
		string word;
		vector<wstring>::const_iterator p;
		for (p = wstrvec.begin(); p!= wstrvec.end(); ++p)
		{
			word = WSTR2GB(*p);
			words->push_back(word);
		}
		if(chi.size() > 300)
			break;
		start = pos + 1;
	}

	if(chi.size() == 0)
	{
	        delete words;
		return false;
	}
//	cout<<"utf8   words = "<<words->size()<<endl;
//	cout<<"utf8   characters = "<<chi.size()<<endl;
	if((words->size() / chi.size()) < 0.8)
	{
	        delete words;
		return true;
	}
	else
	{
	        delete words;
		return false;
	}
}

string CCodeTransformer::gb2312_extract(string strraw)
{

	string chi;
	string::iterator iter;

	for(iter = strraw.begin(); iter != strraw.end(); iter++)
	{
		//����Ǻ���
		while((unsigned char)(*iter) < 0xA1 || (unsigned char)(*iter) > 0xF7)
		{
			iter++;
			if(iter == strraw.end())
			{
				return chi;
			}
		}
		//����gb2312����
		if(0xA1 <= (unsigned char)(*iter) && (unsigned char)(*iter) <= 0xF7)
		{
			iter++;
			if(iter == strraw.end())
			{
				return chi;
			}

			if((unsigned char)(*iter) < 0xA1 || (unsigned char)(*iter) > 0xFE)
			{
			}
			else
			{
				iter--;
				chi += (*iter);
				iter++;
				chi += (*iter);
			}
		}
	}

	return chi;
} 

//utf-8�����ļ���ͷ�����ַ�һ��Ϊ EF BB BF������Ϊ��ʾ
//������unicode�б��뷶ΧΪ4E 00 - 9F FF
//������utf-8�еı��뷶ΧΪE4 B8 80 - E9 BF BF
//����unicode��utf-8��ת������Ϊ1110XXXX 10XXXXXX 10XXXXXX
//����X��ʾ��������Ӧ��16λunicode����
string CCodeTransformer::utf8_extract(string strraw)
{
	string chi;
	string::iterator iter;
	chi.erase();

	iter = strraw.begin();
	if(strraw.size() == 0)
		return chi;
	iter += 3; // ����EF BB BF
	while( iter != strraw.end())
	{
//cout<<"hello"<<endl;
		//����Ǻ���
		if(((unsigned char)(*iter) < 0xE4) || ((unsigned char)(*iter) > 0xE9))
		{
		}
		else if((unsigned char)(*iter) == 0xE4)
		{
			iter++;
			if(iter == strraw.end())
				return chi;
			if((unsigned char)(*iter) < 0xB8)
			{
			}
			else if((unsigned char)(*iter) == 0xB8)
			{
				iter++;
				if(iter == strraw.end())
					return chi;
				if((unsigned char)(*iter) < 0x80)
				{
				}
				else
				{
					iter--;
					iter--;
					chi += (*iter);
					iter++;
					chi += (*iter);
					iter++;
					chi += (*iter);
				}
			}
			else
			{
				iter++;
				if(iter == strraw.end())
					return chi;
				iter--;
				iter--;
				chi += (*iter);
				iter++;
				chi += (*iter);
				iter++;
				chi += (*iter);
			}
		}
		else if((unsigned char)(*iter) == 0xE9)
		{
			iter++;
			if(iter == strraw.end())
				return chi;
			if((unsigned char)(*iter) > 0xBF)
			{
			}
			else if((unsigned char)(*iter) == 0xBF)
			{
				iter++;
				if(iter == strraw.end())
					return chi;
				if((unsigned char)(*iter) > 0xBF)
				{
				}
				else
				{
					iter--;
					iter--;
					chi += (*iter);
					iter++;
					chi += (*iter);
					iter++;
					chi += (*iter);
				}
			}
			else
			{
				iter++;
				if(iter == strraw.end())
					return chi;
				iter--;
				iter--;
				chi += (*iter);
				iter++;
				chi += (*iter);
				iter++;
				chi += (*iter);
			}
		}
		else
		{
			iter++;
			if(iter == strraw.end())
				return chi;
			iter++;
			if(iter == strraw.end())
				return chi;
			iter--;
			iter--;
			chi += (*iter);
			iter++;
			chi += (*iter);
			iter++;
			chi += (*iter);
		}
		iter++;
	}

	return chi;
}

vector<wstring> CCodeTransformer::word_segment(string & strraw)
{
//	segment.initializeInsunAbs();

	wstring chi;
	vector<wstring> words;
	chi.erase();
	words.clear();
	
	if(IsGb2312(strraw))
	{
		chi = GB2WSTR(strraw);
		//���÷ִʳ���
		segment(chi, words);
	}
	else if(IsUtf8(strraw))
	{
		chi = UTF2WSTR(strraw);
		//���÷ִʳ���
		segment(chi, words);
	}

	return words;
}

wstring CCodeTransformer::gb2wstr(string & strraw)
{
	return GB2WSTR(strraw);
}

wstring CCodeTransformer::utf2wstr(string & strraw)
{
	return UTF2WSTR(strraw);
}
string CCodeTransformer::wstr2gb(wstring &wstr)
{
	return WSTR2GB(wstr);
}

