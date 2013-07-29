# -*- coding:utf-8 -*-

# generate query.lib


import os
import re

ConfPath        = '../search.conf'
DataPath        = '../data'
RawDataKeyWord  = r'Raw_Data_Dir'
RawDataPath     = u''
QueryKeyWord    = r'Query_Lib'
QueryLibFile    = u''

#读取配置文件，设置工作目录和结果输出目录
try:
	with open(ConfPath, 'r') as ConfigureFile:
		for each_line in ConfigureFile:
			each_line = each_line.strip()
			if len(re.findall(RawDataKeyWord, each_line)) > 0:
				RawDataPath = str(each_line.split('=', 1)[1])
				continue
			if len(re.findall(QueryKeyWord, each_line)) > 0:
				QueryLibFile = str(each_line.split('=', 1)[1])
				break
except IOError as err0:
	print('Read ConfigureFile Error :' + str(err0))

QueryKeyList = os.listdir(RawDataPath)

try:
	with open(QueryLibFile, 'w') as outpotfile:
		for each_item in QueryKeyList:
			keyword = str(each_item.strip().split('-', 1)[1])
			print(keyword, file = outpotfile)
except IOError as err1:
	print('write QueryLib Error :' + str(err1))



