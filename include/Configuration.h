#include <iostream>
#include <fstream>


using namespace std;

class Configuration
{
public:
	Configuration();
	Configuration(ifstream &conffile);
	~Configuration();

	string getConfig(int name);
}