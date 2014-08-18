#ifndef LOCALSTORAGE_H
#define LOCALSTORAGE_H

#include<string.h>
#include<iostream>
#include "StorageBase.h"

class LocalStorage
{
public:
	int save_file(const char* buff, size_t file_size, std::string name);
	int get_file(std::string key, char* &buffptr,size_t len);
};
#endif