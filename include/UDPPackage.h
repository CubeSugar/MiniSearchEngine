#include <string>
#include <list>
#include <iostream>

#include "Document.h"

using namespace std;
//udp package
//package Header
struct PACKAGE
{
	int PackType;
	string QueryWord;
	int PartCnt;
	int PartID;
	list<DocAbstract> Result;
};