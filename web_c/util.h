#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>

using namespace std;

int get_local_file(std::string key, char* &buffptr,size_t& len);  
int write_local_file(std::string filePath, char* content, size_t len);

void printStr(char* str, int begin, int end);

#endif