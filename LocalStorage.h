#ifndef LOCALSTORAGE_H
#define LOCALSTORAGE_H

#include<string.h>
#include<iostream>
#include "StorageBase.h"

class LocalStorage: public StorageBase
{
private:
	std::string root_path;

	static LocalStorage* instance;
	LocalStorage();
public:
	static LocalStorage* getInstance()
	{
		if(NULL == instance)
		{
			instance = new LocalStorage();
		}
		return instance;
	}
	int save_file(const char* buff, size_t file_size, std::string name);
	int get_file(std::string key, char* &buffptr,size_t& len);
};
#endif