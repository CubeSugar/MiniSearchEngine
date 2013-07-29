# -*- coding:utf-8 -*-
#test find text

import os
import sys

import re

try:
	with open('query.lib', 'r') as af:
		for each_line in af:
			pos = each_line.find('e')
			print('pos = ' + str(pos))
except IOError as err0:
	print("ioerror")