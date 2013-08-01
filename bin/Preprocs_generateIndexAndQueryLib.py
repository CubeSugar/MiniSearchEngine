# -*- coding:utf-8 -*-

#generate Query_Lib & Index_Lib 

#多字节多字节的Unicode编码方式定义了一个“字节顺序标记(Byte Order Mark)”,
#它是一个特殊的非打印字符, 你可以把它包含在文档的开头来指示你所使用的字节顺序。
#对于UTF‐16,字节顺序标记是U+FEFF。
#如果收到一个以字节FF FE 开头的UTF‐16编码的文档,你就能确定它的字节顺序是单向的(one way)的了;
#如果它以FE FF开头,则可以确定字节顺序反向了。

import os
import sys
import re

def generateIndexAndQueryLib():
	if (str(os.getcwd()).split('/')[-1] != 'bin'):
		os.chdir('./bin/')
	
	ConfPath        = '../search.conf'
	DataPath        = '../data'
	QueryKeyWord    = r'Query_Lib'
	QueryLibFile    = u''
	RipePageKeyWord = r'RipePage_Lib'
	RipePageFile    = u''
	IndexKeyWord    = r'Index_Lib'
	IndexLibFile    = u''
	CodeKeyWord     = r'CodeStyle'
	CodeStyle       = u''

	#读取配置文件，设置工作目录和结果输出目录
	try:
		with open(ConfPath, 'r') as ConfigureFile:
			for each_line in ConfigureFile:
				each_line = each_line.strip()
				if len(re.findall(CodeKeyWord, each_line)) > 0:
					CodeStyle = str(each_line.split('=', 1)[1])
					continue
				if len(re.findall(RipePageKeyWord, each_line)) > 0:
					RipePageFile = str(each_line.split('=', 1)[1])
					continue
				if len(re.findall(QueryKeyWord, each_line)) > 0:
					QueryLibFile = str(each_line.split('=', 1)[1])
					continue
				if len(re.findall(IndexKeyWord, each_line)) > 0:
					IndexLibFile = str(each_line.split('=', 1)[1])
					break
				
	except IOError as RCErr:
		print('Read ConfigureFile Error : ' + str(RCErr))


	ByteCounter  = 2 			#字节顺序标记	初值2为utf－16 字节顺序标记符位置	
	QueryTag     = u'<query>'	#查询标签
	QueryKeyList = []			#查询关键词集合
	OffsetList   = []			#偏移量集合

	#读取查询词 & 读取offset
	try:
		with open(RipePageFile, 'r', encoding = CodeStyle) as RPFile:
			for each_line in RPFile:

				pos = each_line.find(QueryTag)		#查找标签
				if pos > -1:
					key = str(each_line.strip().split('>', 1)[1])
					QueryKeyList.append(key)
					pos = each_line.find(QueryTag[-1])	#查找字符串末尾字符的位置，需要对字符串进行切片
					OffsetList.append(ByteCounter + pos * 2 + len(key) * 2 + 2)

				ByteCounter = ByteCounter + len(each_line) * 2
			
			#test
			for i in range(len(OffsetList)):
				RPFile.seek(OffsetList[i])
				#读取时注意空白符：\n \t
				print(RPFile.read(25))
	except IOError as RRErr:
		print("Read RipePageFile Error : " + str(RRErr))

	#输出Query_Lib
	try:
		with open(QueryLibFile, 'w', encoding = CodeStyle) as QFile:
			for each_item in QueryKeyList:
				print(each_item, file = QFile)
	except IOError as WQErr:
		print('Write QueryLibFile Error :' + str(WQErr))

	#输出Index_Lib
	try:
		with open(IndexLibFile, 'w', encoding = CodeStyle) as IFile:
			for i in range(len(QueryKeyList)):
				print(QueryKeyList[i] + '\t' + str(OffsetList[i]), file = IFile)
	except IOError as WIErr:
		print('Write IndexLibFile Error : ' + str(WIErr))


if __name__ == '__main__':
	generateIndexAndQueryLib()


'''
ConfPath        = '../search.conf'
DataPath        = '../data'
QueryKeyWord    = r'Query_Lib'
QueryLibFile    = u''
RipePageKeyWord = r'RipePage_Lib'
RipePageFile    = u''
IndexKeyWord    = r'Index_Lib'
IndexLibFile    = u''
CodeKeyWord     = r'CodeStyle'
CodeStyle       = u''

#读取配置文件，设置工作目录和结果输出目录
try:
	with open(ConfPath, 'r') as ConfigureFile:
		for each_line in ConfigureFile:
			each_line = each_line.strip()
			if len(re.findall(CodeKeyWord, each_line)) > 0:
				CodeStyle = str(each_line.split('=', 1)[1])
				continue
			if len(re.findall(RipePageKeyWord, each_line)) > 0:
				RipePageFile = str(each_line.split('=', 1)[1])
				continue
			if len(re.findall(QueryKeyWord, each_line)) > 0:
				QueryLibFile = str(each_line.split('=', 1)[1])
				continue
			if len(re.findall(IndexKeyWord, each_line)) > 0:
				IndexLibFile = str(each_line.split('=', 1)[1])
				break
			
except IOError as RCErr:
	print('Read ConfigureFile Error : ' + str(RCErr))


ByteCounter  = 2 			#字节顺序标记	初值2为utf－16 字节顺序标记符位置	
QueryTag     = u'<query>'	#查询标签
QueryKeyList = []			#查询关键词集合
OffsetList   = []			#偏移量集合

#读取查询词 & 读取offset
try:
	with open(RipePageFile, 'r', encoding = CodeStyle) as RPFile:
		for each_line in RPFile:

			pos = each_line.find(QueryTag)		#查找标签
			if pos > -1:
				key = str(each_line.strip().split('>', 1)[1])
				QueryKeyList.append(key)
				pos = each_line.find(QueryTag[-1])	#查找字符串末尾字符的位置，需要对字符串进行切片
				OffsetList.append(ByteCounter + pos * 2 + len(key) * 2 + 2)

			ByteCounter = ByteCounter + len(each_line) * 2
		
		#test
		for i in range(len(OffsetList)):
			RPFile.seek(OffsetList[i])
			#读取时注意空白符：\n \t
			print(RPFile.read(25))
except IOError as RRErr:
	print("Read RipePageFile Error : " + str(RRErr))

#输出Query_Lib
try:
	with open(QueryLibFile, 'w', encoding = CodeStyle) as QFile:
		for each_item in QueryKeyList:
			print(each_item, file = QFile)
except IOError as WQErr:
	print('Write QueryLibFile Error :' + str(WQErr))

#输出Index_Lib
try:
	with open(IndexLibFile, 'w', encoding = CodeStyle) as IFile:
		for i in range(len(QueryKeyList)):
			print(QueryKeyList[i] + '\t' + str(OffsetList[i]), file = IFile)
except IOError as WIErr:
	print('Write IndexLibFile Error : ' + str(WIErr))
'''

