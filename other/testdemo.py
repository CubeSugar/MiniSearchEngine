# -*- coding:utf-8 -*-
#test find text
#多字节多字节的Unicode编码方式定义了一个“字节顺序标记(Byte Order Mark)”,
#它是一个特殊的非打印字符, 你可以把它包含在文档的开头来指示你所使用的字节顺序。
#对于UTF‐16,字节顺序标记是U+FEFF。
#如果收到一个以字节FF FE 开头的UTF‐16编码的文档,你就能确定它的字节顺序是单向的(one way)的了;
#如果它以FE FF开头,则可以确定字节顺序反向了。
import os
import sys

import re

counter = 2#字节顺序标记

try:
	with open('query.lib', 'r', encoding = 'utf-16') as af: #, encoding = 'utf-16 LE with BOM'
		for each_line in af:
			print('len = ' + str(len(each_line)))
			pos = each_line.find('History'[-1]) #查找字符串末尾字符的位置，需要对字符串进行切片
			if pos > -1:
				print('pos = ' + str(pos * 2 + counter))
			counter = counter + len(each_line) * 2
			print("counter = " + str(counter))
		#af.seek(7)
		#print(af.read(3))
		af.seek(54)#字节的位置
		print(af.read(1))#读取字符的个数
			
except IOError as err0:
	print("ioerror")
