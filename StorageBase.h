#ifndef STORAGEBASE_H
#define STORAGEBASE_H

#include<string.h>
#include<iostream>


class StorageClient
{
public:
	virtual int save_file(const char* buff, size_t file_size, std::string name) = 0;
	virtual int get_file(std::string key, char* &buffptr,size_t len) = 0;
};

#endif
