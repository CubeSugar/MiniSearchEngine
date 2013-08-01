#ifndef __POSINTERFACE_H__
#define __POSINTERFACE_H__

#include <string>
using namespace std;
#ifdef ELUS_DLL
#undef ELUS_DLL
#endif
#define ELUS_DLL

#ifndef _POSINTERFACE_
#define _POSINTERFACE_
const int pm_HMM = 1;		
const int pm_ME = 2;		
const int pm_MEMM = 3;		
#endif


class ELUS_DLL CELUSPos		
{
public:
	
	static void HMMPos(const wstring & AInSentence, wstring & AOutSentence, const wstring & ASegTag = JGB2WSTR("  "), bool ATriModeFlag = false);

	static int PosFile(const wstring & AFileName, const wstring & APosFileName = JGB2WSTR(""), const wstring & ASegTag = JGB2WSTR("  "), bool ATriModeFlag = false);
			
	
	static void HMMPosA(const string & AInSentence, string & AOutSentence, const string & ASegTag = "  ", bool ATriModeFlag = false);

	static int PosFileA(const string & AFileName, const string & APosFileName = "", const string & ASegTag = "  ", bool ATriModeFlag = false);
			
};


extern "C"		
{	
	
	
	ELUS_DLL const wchar_t * HMMPos(const wchar_t * AInSentence, const wchar_t * ASegTag = NULL, int ATriModeFlag = false);
			

	ELUS_DLL int PosFile(const wchar_t * AFileName, const wchar_t * APosFileName = NULL, const wchar_t * ASegTag = NULL, int ATriModeFlag = false);
			

	ELUS_DLL const char * HMMPosA(const char * AInSentence, const char * ASegTag = NULL, bool ATriModeFlag = false);
			

	ELUS_DLL int PosFileA(const char * AFileName, const char * APosFileName = NULL, const char * ASegTag = NULL, bool ATriModeFlag = false);
			
};


#endif
