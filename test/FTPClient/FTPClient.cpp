#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <fstream>

#include "FTProtocol.h"

using namespace std;

#define DEFAULT_PORT 9999
#define SERVER_ADDR "127.0.0.1"
#define THREAD_COUNT 1

void retrive_file(string fileName)
{

    //say_hello();
    int cPort = DEFAULT_PORT;
    int cLen = 0;
    struct sockaddr_in cli;
    
    cli.sin_family = AF_INET;
    cli.sin_port = htons(cPort);
    cli.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    
    const int cClient = socket(AF_INET, SOCK_STREAM, 0);

    if(cClient < 0)
    {
        printf("socket() failure!\n");
        return; 
    }
    
    if(connect(cClient, (struct sockaddr*)&cli, sizeof(cli)) < 0)
    {
        printf("connect() failure!\n");
        return;
    }

    cLen = w_send(cClient, "1", 1);
    if((cLen < 0)||(cLen == 0))
    {
        printf("send() failure!\n");
        return;
    }

    cLen = w_send(cClient, fileName.c_str(), strlen(fileName.c_str()));
    if((cLen < 0)||(cLen == 0))
    {
        printf("send() failure!\n");
        return;
    }

    char* cbuf = NULL;
    int rc = w_recv(cClient, cbuf);
    std::string filePath(fileName);
    std::ofstream ofile;
    if(rc > 0)
    {
        ofile.open(filePath.c_str(), std::ios::binary);
        if(ofile.fail())
        {
            printf("create file failed");
            return;
        }
        printf("create file successs");

    	ofile.write(cbuf, rc);
        ofile.close();
    }
    close(cClient);
    printf("done\n");
}


int get_file(std::string key, char* &buffptr,size_t& len)
{
    string file_path = key;
    ifstream ifile(file_path.c_str());
    if (ifile.fail())
    {
        std::cout<<("No file " + key + " found");
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

void do_send_file(string fileName)
{
    int cPort = DEFAULT_PORT;
    int cClient = 0;
    int cLen = 0;
    struct sockaddr_in cli;
    char cbuf[4096] = {0};
    
    memset(cbuf, 0, sizeof(cbuf));
    
    cli.sin_family = AF_INET;
    cli.sin_port = htons(cPort);
    cli.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    
    cClient = socket(AF_INET, SOCK_STREAM, 0);

    if(cClient < 0)
    {
        printf("socket() failure!\n");
        return; 
    }
    
    if(connect(cClient, (struct sockaddr*)&cli, sizeof(cli)) < 0)
    {
        printf("connect() failure!\n");
        return;
    }
    //send method
    cLen = w_send(cClient, "2", 1);
    if((cLen < 0)||(cLen == 0))
    {
        printf("send() failure!\n");
        return;
    }

    //send filename
    cLen = w_send(cClient, fileName.c_str(), strlen(fileName.c_str()));
    if((cLen < 0)||(cLen == 0))
    {
        printf("send() failure!\n");
        return;
    }

    //send content


    cLen = w_send(cClient, "123456789", 9);
    if((cLen < 0)||(cLen == 0))
    {
        printf("send() failure!\n");
        return;
    }


    char* pResponse;
    int rc = w_recv(cClient, pResponse);
    
    printf("%s\n",pResponse);

    delete pResponse;

    close(cClient);
    printf("done\n");
}

int main(int argc, char** argv)
{
    string fileName;
    cout<<"input file name:";
    while(cin>>fileName)
    {
        do_send_file(fileName);
        cout<<"input file name:";
    }
    return 0;
}
