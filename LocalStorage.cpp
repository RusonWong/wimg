#include <iostream>
#include <fstream>
#include "LocalStorage.h"
#include "Logger.h"


#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

LocalStorage* LocalStorage::instance = NULL;
LocalStorage::LocalStorage()
{
	this->root_path = "./local_files/";
}

int LocalStorage::save_file(const char* buff, size_t file_size, std::string file_name)
{
	string filePath = this->root_path + file_name;
	ofstream ofile;
	ofile.open(filePath.c_str(), ios::binary);
	if(ofile.fail())
	{
		log("create file failed");
		return 0;
	}
	log("create file successs");
	ofile.write(buff, file_size);
	ofile.close();
	return 1;
}

int LocalStorage::get_file(std::string key, char* &buffptr,size_t& len)
{
	string file_path = this->root_path + key;
	ifstream ifile(file_path.c_str());
	if (ifile.fail())
	{
		log("No file " + key + " found");
		return 0;
	}
	else{

		ifile.seekg(0,ios::end);
		long fSize = (long)ifile.tellg();
		len = (size_t)fSize;
		cout<<"file lenth is:"<<fSize<<endl;
		buffptr = new char[fSize];
		ifile.seekg(0,ios::beg);
		ifile.read(buffptr, fSize);
	}

	ifile.close();
	return 1;
}