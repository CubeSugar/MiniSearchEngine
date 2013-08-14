#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Configuration
{
public:
	string m_IndexFile;
	string m_RipepageFile;
	string m_StopWordsFile;
	string m_InvertedIndexFile;
	string m_SmlrtyFile;
	string m_SocketPort;
	string m_IPAddress;
	string m_DebugLog;
    
public:
	Configuration();
	Configuration(ifstream &conffile);
	~Configuration();
    
	string getConfig(int name);
};