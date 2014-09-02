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
public:
	Config(){}
	~Config(){}

	void load(string configPath);

};



#endif