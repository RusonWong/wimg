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

using namespace std;

#define DEFAULT_PORT 9999
#define SERVER_ADDR "127.0.0.1"
#define THREAD_COUNT 1

void retrive_file(string fileName)
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
   
    cLen = send(cClient, fileName.c_str(), strlen(fileName.c_str()),0);
    if((cLen < 0)||(cLen == 0))
    {
        printf("send() failure!\n");
        return;
    }

    int rc = recv(cClient, cbuf, sizeof(cbuf),0);
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
        
    
        while(rc > 0){
    	    ofile.write(cbuf, rc);
            rc = recv(cClient, cbuf, sizeof(cbuf),0);
        }

        ofile.close();
    }
    close(cClient);
    printf("done\n");
}

int main(int argc, char** argv)
{
    string fileName;
    cout<<"input file name:";
    while(cin>>fileName)
    {
        retrive_file(fileName);
        cout<<"input file name:";
    }
    return 0;
}
