#ifndef WDFSCONNECT_H
#define WDFSCONNECT_H

#include "StorageBase.h"


class WDFSConnector:
{
public:
	WDFSConnector();
	~WDFSConnector();

	int save_file(const char* buff, size_t file_size, std::string name);
	int get_file(std::string key, char* &buffptr,size_t len);
};
#endif	