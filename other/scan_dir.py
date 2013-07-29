'''
	P2 Project
	scan RawData dir
'''

import os
import sys

'''
v1.0
def getDirList(path, level = 0, indent = True):
	if indent:
		for tab in range(level):
			print('\t', end = '')
	DirList = os.listdir(path)
	for each_file in DirList:
		if os.path.isdir(each_file):
			getDirList(each_file, level + 1)
		else:
			print(each_file)
'''

'''
v1.1
print dir tree
'''
def getDirList(path, level = 0, indent = True):
	DirList = os.listdir(path)
	for each_file in DirList:
		if indent:
			for tab in range(level):
				print(' ', end = '')
		print(path + '/' + each_file)
		subpath = os.path.join(path, each_file)
		if os.path.isdir(subpath):
			getDirList(subpath, level + 1)

'''
	define function
	print file name to a txt
'''
def storeFileName(path):
	DirList = os.listdir(path)
	for each_file in DirList:	
		subpath = os.path.join(path, each_file)
		if os.path.isdir(subpath):
			storeFileName(subpath)
		else:
			try:
				with open('result.txt', 'a') as ResultFile:
					print(each_file, file = ResultFile)
			except IOError as err:
				print('IOError :' + str(err))

def storeDirPath(path):
	DirList = os.listdir(path)
	#oldPath = path
	storePath = []

	for each_file in DirList:
		subpath = os.path.join(path, each_file)
		if os.path.isdir(subpath):
			#oldPath = subpath
			storeDirPath(subpath)
		else:
			print(os.path.dirname(subpath))


'''
	try:
		with open('dp.txt', 'w') as dp:
			for each_item in storePath:
				print(each_item, file = dp)

	except IOError as err:
		print('IOError : ' + str(err))
'''
#print(os.getcwd())

#os.chdir('../Documents/ProgrammingExercise/Project/P2')
rootpath = './RawData'
testpath = './Test'

#getDirList(testpath)
#storeFileName(testpath)
storeDirPath(rootpath)


