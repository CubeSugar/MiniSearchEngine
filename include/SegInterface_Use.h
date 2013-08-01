#include "JTCharCodeConvert.h"

#ifndef __SEGINTERFACE_H__
#define __SEGINTERFACE_H__

#include <string>
using namespace std;

#ifdef ELUS_DLL
#undef ELUS_DLL
#endif
#define ELUS_DLL


#ifndef _SEGINTERFACE_
#define _SEGINTERFACE_
const int sm_FMM = 1;		
const int sm_BMM = 2;		
const int sm_Viterbi = 3;	
#endif


class ELUS_DLL CELUSSeg		
{
public:
	
	static void FMMSeg(const wstring & AInSentence, wstring & AOutSentence);
	static void BMMSeg(const wstring & AInSentence, wstring & AOutSentence);
	static void ViterbiSeg(const wstring & AInSentence, wstring & AOutSentence);

	static int SegFile(const wstring & AFileName, const wstring & ASegFileName = JGB2WSTR(""), int ASegMode = sm_BMM);
			
	
	static void FMMSegA(const string & AInSentence, string & AOutSentence);
	static void BMMSegA(const string & AInSentence, string & AOutSentence);
	static void ViterbiSegA(const string & AInSentence, string & AOutSentence);

	static int SegFileA(const string & AFileName, const string & ASegFileName = "", int ASegMode = sm_BMM);
			
public:
	static bool OptionSet(const string & AOptionKey, const string & AOptionValue);	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
public:
	static int GetErrorCode() {return FErrorCode;}	
	static int GetFileErrorLineNumber() {return FErrorFileLineNumber;}	
private:
	static int FErrorCode;
	static int FErrorFileLineNumber;
};

class CELUSSegOption	
{
public:
	static bool SetFactoid(bool AValue) {if (AValue) return CELUSSeg::OptionSet("Factoid","true"); return CELUSSeg::OptionSet("Factoid","false");}
	static bool SetMorphology(bool AValue) {if (AValue) return CELUSSeg::OptionSet("Morphology","true"); return CELUSSeg::OptionSet("Morphology","false");}
	static bool SetTagType(bool AValue) {if (AValue) return CELUSSeg::OptionSet("TagType","true"); return CELUSSeg::OptionSet("TagType","false");}
	static bool SetFileSuffix(const string & AValue) {return CELUSSeg::OptionSet("FileSuffix",AValue);}
	static bool SetSEG_TAG(const string & AValue) {return CELUSSeg::OptionSet("SEG_TAG",AValue);}
		
	static bool SetSegPatch(bool AValue) {if (AValue) return CELUSSeg::OptionSet("SegPatch","true"); return CELUSSeg::OptionSet("SegPatch","false");}
	static bool SetMMSegPatch(bool AValue) {if (AValue) return CELUSSeg::OptionSet("MMSegPatch","true"); return CELUSSeg::OptionSet("MMSegPatch","false");}
	static bool SetSegNE(bool AValue) {if (AValue) return CELUSSeg::OptionSet("SegNE","true"); return CELUSSeg::OptionSet("SegNE","false");}
	static bool SetMMSegNE(bool AValue) {if (AValue) return CELUSSeg::OptionSet("MMSegNE","true"); return CELUSSeg::OptionSet("MMSegNE","false");}
	static bool SetNameSeperator(bool AValue) {if (AValue) return CELUSSeg::OptionSet("NameSeperator","true"); return CELUSSeg::OptionSet("NameSeperator","false");}
	static bool SetSegNEOnlyName(bool AValue) {if (AValue) return CELUSSeg::OptionSet("SegNEOnlyName","true"); return CELUSSeg::OptionSet("SegNEOnlyName","false");}	
	static bool SetNETagType(int AValue) {string mValue = "1"; char buf[20];/*mValue = itoa(AValue, buf , 10);*/sprintf(buf,"%d",AValue); return CELUSSeg::OptionSet("NETagType",mValue); }	
};


extern "C"		
{	
	
	
	ELUS_DLL bool SegOptionSet(const char * AOptionKey, const char * AOptionValue);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	ELUS_DLL const wchar_t * FMMSeg(const wchar_t * AInSentence);
	ELUS_DLL const wchar_t * BMMSeg(const wchar_t * AInSentence);
	ELUS_DLL const wchar_t * ViterbiSeg(const wchar_t * AInSentence);

	ELUS_DLL int SegFile(const wchar_t * AFileName, const wchar_t * ASegFileName, int ASegMode = sm_BMM);
			
	
	ELUS_DLL const char * FMMSegA(const char * AInSentence);
	ELUS_DLL const char * BMMSegA(const char * AInSentence);
	ELUS_DLL const char * ViterbiSegA(const char * AInSentence);

	ELUS_DLL int SegFileA(const char * AFileName, const char * ASegFileName, int ASegMode = sm_BMM);
			

	
	ELUS_DLL int GetErrorCode(); 	
	ELUS_DLL int GetFileErrorLineNumber(); 	

};

#endif
