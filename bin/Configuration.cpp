#include "MiniSearchEngineStd.h"
#include "Configuration.h"

Configuration::Configuration()
{
	ifstream conffile(CONFIG_FILE.c_str());
    if (!conffile.is_open())
    {
        cout << "can not open confile!" << endl;
    }
    
    string line;
	int i = 0;
	while (getline(conffile, line))
	{
		string::size_type posequal = line.find("=");
		if (posequal == string::npos)
		{
			continue;
		}
        
		if (line.find("RipePage_Lib") != string::npos)
		{
			m_RipepageFile.assign(line, posequal + 1, line.size() - posequal);
			continue;
		}
        
		if (line.find("Index_Lib") != string::npos)
		{
			m_IndexFile.assign(line, posequal + 1, line.size() - posequal);
			continue;
		}
        
		if (line.find("Inverted_Lib") != string::npos)
		{
			m_InvertedIndexFile.assign(line, posequal + 1, line.size() - posequal);
			continue;
		}
        
		if (line.find("Smlrty_Lib") != string::npos)
		{
			m_SmlrtyFile.assign(line, posequal + 1, line.size() - posequal);
			continue;
		}
        
		if (line.find("StopWord_File") != string::npos)
		{
			m_StopWordsFile.assign(line, posequal + 1, line.size() - posequal);
			continue;
		}
        
		if (line.find("DebugLog") != string::npos)
		{
			m_DebugLog.assign(line, posequal + 1, line.size() - posequal);
			continue;
		}
        
		if (line.find("Port") != string::npos)
		{
			m_SocketPort.assign(line, posequal + 1, line.size() - posequal);
			continue;
		}
        
		if (line.find("IP") != string::npos)
		{
			m_IPAddress.assign(line, posequal + 1, line.size() - posequal);
			continue;
		}
	}
    
    conffile.close();
}

Configuration::~Configuration()
{
    
}

string Configuration::getConfig(int option)
{
	switch (option)
	{
        case INDEX_FILE:
            return m_IndexFile;
            break;
            
        case RIPEPAGE_FILE:
            return m_RipepageFile;
            break;
            
        case STOPWORDS_FILE:
            return m_StopWordsFile;
            break;
            
        case INVERTEDINDEX_FILE:
            return m_InvertedIndexFile;
            break;
            
        case SMLRTY_FILE:
            return m_SmlrtyFile;
            break;
            
        case SOCKETPORT:
            return m_SocketPort;
            break;
            
        case IPADDRESS:
            return m_IPAddress;
            break;
            
        case DEBUG_LOG:
            return m_DebugLog;
            break;
	}
}