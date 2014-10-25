#include "util.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>


int get_local_file(std::string file_path, char* &buffptr,size_t& len)
{
    ifstream ifile(file_path.c_str());
    if (ifile.fail())
    {
        std::cout<<("Error open " + file_path + "\n");
        return 0;
    }
    else{

        ifile.seekg(0,ios::end);
        long fSize = (long)ifile.tellg();
        ifile.seekg(0,ios::beg);

        len = (size_t)fSize;

        cout<<"file lenth is:"<<fSize<<endl;
        buffptr = new char[fSize];
        int size_read = 0;
        while(size_read != fSize)
        {   
            ifile.read(buffptr + size_read, fSize - size_read);
            size_read += fSize;
        }
        return 1;
    }

    ifile.close();
    return 1;
}

int write_local_file(std::string filePath, char* content, size_t len)
{
    std::ofstream ofile;
   
    ofile.open(filePath.c_str(), std::ios::binary);
    if(ofile.fail())
    {
        cout<<("create file failed\n");
        return 0;
    }
    cout<<("create file successs\n");

    int size_writen = 0;
    while(size_writen != len)
    {
        ofile.write(content+size_writen, len - size_writen);
        size_writen += len;
    }

    ofile.close();
    return 1;
}


void printStr(char* str, int begin, int len)
{
	char* temp = (char*)malloc(len+1);

	snprintf(temp, len + 1, "%s", str + begin);
	temp[len+1] = '\0';
	cout<<temp<<endl;
}
