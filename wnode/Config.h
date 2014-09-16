#ifndef CONFIG_H
#define CONFIG_H


#include <iostream>
#include <string>

using namespace std;

class Config
{
public:
	string	localAddr;
	int	    port;

	string	masterAddr;
	int		masterPort;

	int 	threadsCount;

	string 	memAddr;
	int		memPort;

	string beansdbAddr;
	int		beansdbPort;

public:
	Config(){}
	~Config(){}

	void load(string configPath);

};



#endif