#ifndef WCHACHE_H
#define WCHACHE_H

#include <iostream>
#include <string>
using namespace std;

class WCache
{
public:
	int get(string key,char* &buff,size_t &len);
	int set(string key,char* buff,size_t len);
};

#endif

