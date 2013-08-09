# -*- coding:utf-8 -*-

#	return file ID, title and content

import os
import codecs
import re

def getFileInfo(filename):
	FileInfo     = []					#return list
	FileID       = ''					#file id
	Title        = 'No Title'			#file title
	ContentStr   = 'No Content'			#file content
	TitleBegin   = False				#flag of title pos
	ContentBegin = False				#flay of title pos

	#generate file id
	(pre, post) = filename.strip().split('-', 1)
	PreID       = re.search('\d+', pre).group()
	PostID      = re.search('\d+', post).group()
	FileID      = '{:04d}{:04d}'.format(int(PreID), int(PostID))

	#get file title and content
	try:
		with codecs.open(filename, 'r', 'gb18030') as FileName: #file code = gb18030
			for each_line in FileName:
				#each_line = each_line.strip()
				
				#file title end
				if len(re.findall('【', each_line)) > 0:
					TitleBegin = False

				#get file title
				if TitleBegin:	
					#delete space char by ''join(s.split())
					Title = Title + ''.join(each_line.strip().split())
					
				elif len(re.findall(r'【\s*标\s*题\s*】', each_line)) > 0: 
					#file title begin
					TitleBegin = True
					Title = str(each_line.strip().split('】', 1)[1])
					continue

				#get file content
				if ContentBegin:
					#test file content end
					if len(re.findall('【', each_line)) > 0:
						ContentBegin = False
						break

					#trim each_line
					#new_content_line = u''.join(each_line.split())

					#replace the & < > " ' with xml escape code
					#new_content_line = re.sub('&', u'&amp;', new_content_line)
					#new_content_line = re.sub('<', u'&lt;', new_content_line)
					#new_content_line = re.sub('>', u'&gt;', new_content_line)
					#new_content_line = re.sub('\"', u'&quot;', new_content_line)
					#new_content_line = re.sub("\'", u'&apos;', new_content_line)

					new_content_line = re.sub('\s', u' ', each_line)
					#get file content
					ContentStr = ContentStr + new_content_line
					
				elif len(re.findall(r'【\s*正\s*文\s*】', each_line)) > 0: 
					#file content begin
					ContentBegin = True
					ContentStr = ''
		
	except IOError as RRDErr:
		#print("Read Raw Data file Error : " + str(RRDErr))
		pass
	except UnicodeDecodeError as UDErr:
		#print('-------UnicodeDecodeError--------')
		#print(filename)
		#print('UnicodeDecodeError : ' + str(UDErr))
		pass

	FileInfo.append(FileID)
	FileInfo.append(Title)
	FileInfo.append(ContentStr)
	return FileInfo