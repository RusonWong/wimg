#include <iostream>
#include <fstream>
#include "LocalStorage.h"
using namespace std;


int LocalStorage::save_file(const char* buff, size_t file_size, std::string file_name)
{
	string filePath = "./local_files/"+file_name;
	ofstream output(filePath.c_str());

	output.write(buff, file_size);
	output.close();
	return 1;
}
int LocalStorage::get_file(std::string key, char* &buffptr,size_t len)
{
	return 1;
}