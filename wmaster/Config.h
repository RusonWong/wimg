#ifndef CONFIG_H
#define CONFIG_H


#include <iostream>
#include <string>

using namespace std;

class Config
{
public:
	int	    masterPort;

	int 	threadsCount;

	int 	use_single_thread;
public:
	Config(){}
	~Config(){}

	void load(string configPath);

};



#endif