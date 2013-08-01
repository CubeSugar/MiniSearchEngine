#ifndef J_T_CHARCODE_CONVERT__H
#define J_T_CHARCODE_CONVERT__H

#include <iostream>
#include <vector>
using namespace std;

#ifdef DLL_TAG
#undef DLL_TAG
#endif
#define DLL_TAG

struct DLL_TAG _JGB2WSTR
{
	wstring operator() (const string& gbStr);
	wstring operator() ( string& gbStr );
	wstring operator() (const char * pchGb);
	wstring operator() (const char AChar);		
};

struct DLL_TAG _JWSTR2GB
{
	string operator() (const wstring& uniStr);
	string operator() ( wstring& uniStr );
	string operator() (const wchar_t * pwchUni);
	string operator() (const wchar_t AWChar);		
};

DLL_TAG extern _JGB2WSTR JGB2WSTR;
DLL_TAG extern _JWSTR2GB JWSTR2GB;
//DLL_TAG extern _JGB2WSTR GB2WSTR;
//DLL_TAG extern _JWSTR2GB WSTR2GB;

	class  CJGb2UniConvert{
		typedef unsigned short WORD;
		typedef unsigned long DWORD;
		typedef unsigned char BYTE;
	protected:
		enum CodeTableScope {
			GbBegin=0x8140,
			GbEnd=0xfe50,	
			UniBegin=0x00a4,
			UniEnd=0xffe6
		};

		//bool m_bLibLoaded;
		//static vector<unsigned short>  gb2312, unicode;
		vector<unsigned short>  gb2312, unicode;
		
		void ReadCodeValue(unsigned short& ,
								unsigned short &,
								istream&, 
								vector<unsigned short>&);
								
	public:
		static CJGb2UniConvert & Instance()
		{
			static CJGb2UniConvert mm;
			return mm;		 
		}	   

	private:
		CJGb2UniConvert(){CodeTableLoad(); }
		~CJGb2UniConvert() { ReleaseLib();}
	
	public:	
		int CodeTableLoad();	
		void Gb2312ToUnicode(const string& GbRawText,wstring& UniResult);
		void UnicodeToGb2312(const wstring& UniRawText, string& GbResult);
		void ReleaseLib(){
			gb2312.clear();unicode.clear();
			cout<<"code convert lib released!\n";
		}

	public:
		string m_RootPath;		
	};


inline wstring _JGB2WSTR::operator() (const string& gbStr)
{
	wstring wstruni;
	CJGb2UniConvert::Instance().Gb2312ToUnicode(gbStr, wstruni);
	return wstruni;
}

inline wstring _JGB2WSTR::operator() ( string& gbStr )
{
	wstring wstruni;
	CJGb2UniConvert::Instance().Gb2312ToUnicode(const_cast<string &>(gbStr), wstruni);
	return wstruni;
}

inline wstring _JGB2WSTR::operator() (const char * pchGb)
{
	wstring wstruni;
	CJGb2UniConvert::Instance().Gb2312ToUnicode(string(pchGb), wstruni);
	return wstruni;
}

inline wstring _JGB2WSTR::operator() (const char AChar)
{
	string mStr;
	mStr = AChar;
	wstring wstruni;
	CJGb2UniConvert::Instance().Gb2312ToUnicode(mStr, wstruni);
	return wstruni;
}


inline string _JWSTR2GB::operator() (const wstring& uniStr){
	string _S;
	CJGb2UniConvert::Instance().UnicodeToGb2312(uniStr, _S);
	return _S;
}

inline string _JWSTR2GB::operator() ( wstring& uniStr )
{
	string _S;
	CJGb2UniConvert::Instance().UnicodeToGb2312(const_cast<wstring &>(uniStr), _S);
	return _S;
}

inline string _JWSTR2GB::operator() (const wchar_t * pwchUni)
{
	string _S;
	CJGb2UniConvert::Instance().UnicodeToGb2312(wstring(pwchUni), _S);
	return _S;
}

inline string _JWSTR2GB::operator() (const wchar_t AWChar)
{
	wstring mWStr;
	mWStr = AWChar;
	string _S;
	CJGb2UniConvert::Instance().UnicodeToGb2312(mWStr, _S);
	return _S;
}
#endif
