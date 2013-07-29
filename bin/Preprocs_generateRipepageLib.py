# -*- coding:utf-8 -*-

import os
import re
import fnmatch
import codecs
from Preprocs_getFileInfo import getFileInfo

ConfPath        = '../search.conf'
DataPath        = '../data'
RawDataKeyWord  = r'Raw_Data_Dir'
RawDataPath     = u''
RipePageKeyWord = r'RipePage_Lib'
RipePageFile    = u''

#读取配置文件，设置工作目录和结果输出目录
try:
	with open(ConfPath, 'r') as ConfigureFile:
		for each_line in ConfigureFile:
			each_line = each_line.strip()
			if len(re.findall(RawDataKeyWord, each_line)) > 0:
				RawDataPath = str(each_line.split('=', 1)[1])
				continue
			if len(re.findall(RipePageKeyWord, each_line)) > 0:
				RipePageFile = str(each_line.split('=', 1)[1])
				break
except IOError as err0:
	print('Read ConfigureFile Error :' + str(err0))

#cd data dir
os.chdir(DataPath)

#define tag string
QUERYS      = u'<query>'
QUERYE      = u'</query>\n'
DOCS        = u'\t<doc>'
DOCE        = u'\t</doc>\n'
DOCIDS      = u'\t\t<docid>'
DOCIDE      = u'</docid>\n'
DOCURLS     = u'\t\t<url>'
DOCURLE     = u'</url>\n'
DOCTITLES   = u'\t\t<title>'
DOCTITLEE   = u'</title>\n'
DOCCONTENTS = u'\t\t<content>'
DOCCONTENTE = u'</content>\n'

#stroe current work dir
RootPath = os.getcwd()

#get dir list
DirList = os.listdir(RawDataPath)

try:
	with codecs.open(RipePageFile, 'w', 'utf-8') as outpotfile:
		#print(u"<?xml version='1.0' encoding='utf-8'?>", file = outpotfile)
		print('begin')
		for each_finder in DirList:
			if re.search('-', each_finder):
				#split query key word
				querykey = each_finder.strip().split('-', 1)[1]
			else:
				continue

			#<query>
			print((QUERYS + querykey), file = outpotfile)

			#back to current work dir
			os.chdir(RootPath)

			#get sub dir path
			subpath = os.path.join(RawDataPath, each_finder)

			#get file list
			FileList = os.listdir(subpath)

			#cd sub dir
			os.chdir(subpath)
			for each_file in FileList:
				#filtering .txt file
				if fnmatch.fnmatch(each_file, '*.txt'):
					#get file info
					FileInfo = getFileInfo(each_file)
					#<doc>
					print(DOCS, file = outpotfile)
					#<dcoid></docid>
					print(DOCIDS + FileInfo[0] + DOCIDE, file = outpotfile)
					#<url></url>
					print(DOCURLS + u'https://www.google.com' + DOCURLE, file = outpotfile)
					#<title></title>
					print(DOCTITLES + FileInfo[1] + DOCTITLEE, file = outpotfile)
					#<content></content>
					print(DOCCONTENTS + FileInfo[2] + DOCCONTENTE, file = outpotfile)
					#</doc>
					print(DOCE, file = outpotfile)
			#</query>
			print(QUERYE, file = outpotfile)
except IOError as err:
	print('open RipePageFile error :' + str(err))
	

