#ifndef MINI_SEARCH_ENGINE_STD_H
#define MINI_SEARCH_ENGINE_STD_H

#include <string>
using namespace std;

//tag string length
const int QueryOffset     = 14;//<query>
const int QueryOffsetE    = 16;//</query>
const int DocOffset       = 10;//<doc>
const int DocOffsetE      = 12;//</doc>
const int DocIDOffset     = 14;//<docid>
const int DocIDOffsetE    = 16;//</docid>
const int TitleOffset     = 14;//<title>
const int TitleOffsetE    = 16;//</title>
const int URLOffset       = 10;//<url>
const int URLOffsetE      = 12;//</url>
const int ContentOffset   = 18;//<content>
const int ContentOffsetE  = 20;//</content>

//file & directory path
const int INDEX_FILE         = 1;
const int RIPEPAGE_FILE      = 2;
const int STOPWORDS_FILE     = 3;
const int INVERTEDINDEX_FILE = 4;
const int SMLRTY_FILE        = 5;
const int SOCKETPORT         = 6;
const int IPADDRESS          = 7;
const int DEBUG_LOG          = 8;

//udp package type
const int QUERYPACK          = 1;
const int RESPONSEPACK       = 2;

//config file
const string CONFIG_FILE     = "../search.conf";

#endif