#include <openssl/md5.h>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <stdlib.h>
using namespace std;


int main()
{
        FILE *fd=fopen("hello.txt","r");
        MD5_CTX c;
        unsigned char md5[17]={0};
        if(fd == NULL)
        {
                cout << "open failed" << endl;
                return -1;
        }
        int len;
        unsigned char *pData = (unsigned char*)malloc(1024*1024*1024);
        if(!pData)
        {
                cout << "malloc failed" << endl;
                return -1;
        }
        MD5_Init(&c);
        while( 0 != (len = fread(pData, 1, 1024*1024*1024, fd) ) )
        {
                MD5_Update(&c, pData, len);
        }
        MD5_Final(md5,&c);
        for(int i = 0; i < 16; i++)
                cout << hex << setw(2) << setfill('0') << (int)md5[i];
        cout << endl;
        fclose(fd);
        free(pData);
        return 0;
}