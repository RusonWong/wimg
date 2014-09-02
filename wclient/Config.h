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

public:
	Config(){}
	~Config(){}

	void load(string configPath);

};



#endif