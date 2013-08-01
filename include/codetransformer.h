/**************************************************************************
** 文件名:    codetransformer.h
** 版    权： Copyright (c) 2000-2001 智能计算研究中心 
** 创建人:    王景琦
** 日  期:    2007年10月20号 
** 描  述:    中文字符编码转换。 
** 版本:      V1.00
** 修改记录			
** 日  期        版本       修改人         修改摘要
**                
**************************************************************************/

#ifndef _Inar_CodeTransformer_H_
#define _Inar_CodeTransformer_H_

using namespace std;

#include <string>
#include <iconv.h>

/*******************************************************************
****	编码转换类：成员变量，成员函数
********************************************************************/
class CCodeTransformer
{
public:
	//##construction
	CCodeTransformer();
	~CCodeTransformer();
	void Clear();
//	bool IsGb2312(string strraw);/*待升级*/
//	bool IsUtf8(string strraw);/*待升级*/

	wstring utf2wstr(string & strraw);/*utf-8转化为宽字符（4字节）*/
	string wstr2utf(wstring & wstr);/*宽字符转化为utf-8*/
	string utf2gb(string & strraw);/*utf-8转化为gb2312*/
	string gb2utf(string & strgb);/*gb2312转化为utf-8*/
	string wstr2gb(wstring & wstr);/*宽字符转化为gb2312*/
	wstring gb2wstr(string & gbbuf);/*gb2312转化为宽字符*/

private:
	int code_convert(char *from_charset,char *to_charset,char *inbuf,size_t inlen,char *outbuf,size_t outlen);/*iconv实现的编码转化*/
};

#endif   /* _Inar_CodeTransformer_H_ */

