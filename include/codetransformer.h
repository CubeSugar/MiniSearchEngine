/**************************************************************************
** �ļ���:    codetransformer.h
** ��    Ȩ�� Copyright (c) 2000-2001 ���ܼ����о����� 
** ������:    ������
** ��  ��:    2007��10��20�� 
** ��  ��:    �����ַ�����ת���� 
** �汾:      V1.00
** �޸ļ�¼			
** ��  ��        �汾       �޸���         �޸�ժҪ
**                
**************************************************************************/

#ifndef _Inar_CodeTransformer_H_
#define _Inar_CodeTransformer_H_

using namespace std;

#include <string>
#include <iconv.h>

/*******************************************************************
****	����ת���ࣺ��Ա��������Ա����
********************************************************************/
class CCodeTransformer
{
public:
	//##construction
	CCodeTransformer();
	~CCodeTransformer();
	void Clear();
//	bool IsGb2312(string strraw);/*������*/
//	bool IsUtf8(string strraw);/*������*/

	wstring utf2wstr(string & strraw);/*utf-8ת��Ϊ���ַ���4�ֽڣ�*/
	string wstr2utf(wstring & wstr);/*���ַ�ת��Ϊutf-8*/
	string utf2gb(string & strraw);/*utf-8ת��Ϊgb2312*/
	string gb2utf(string & strgb);/*gb2312ת��Ϊutf-8*/
	string wstr2gb(wstring & wstr);/*���ַ�ת��Ϊgb2312*/
	wstring gb2wstr(string & gbbuf);/*gb2312ת��Ϊ���ַ�*/

private:
	int code_convert(char *from_charset,char *to_charset,char *inbuf,size_t inlen,char *outbuf,size_t outlen);/*iconvʵ�ֵı���ת��*/
};

#endif   /* _Inar_CodeTransformer_H_ */

