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

#define USING_PROTOBUFF 1


int get_local_file(std::string key, char* &buffptr,size_t& len)
{
    string file_path = "./files/" + key;
    ifstream ifile(file_path.c_str());
    if (ifile.fail())
    {
        std::cout<<("No file " + key + " found");
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
        printf("create file failed\n");
        return 0;
    }
    printf("create file successs\n");

    int size_writen = 0;
    while(size_writen != len)
    {
        ofile.write(content+size_writen, len - size_writen);
        size_writen += len;
    }

    ofile.close();
    return 1;
}




#ifdef USING_PROTOBUFF
//with protobuf version
#include "WPB.pb.h"
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

    //send method
    cLen = w_send(cClient, "1", 1);
    if((cLen < 0)||(cLen == 0))
    {
        printf("send() failure!\n");
        return;
    }
    
    ReqGet req;
    req.set_imageid(fileName);
    req.set_width(100);
    req.set_height(200);
    size_t reqbuffsize = req.ByteSize();
    char* reqbuff = new char[reqbuffsize];
    req.SerializeToArray(reqbuff, reqbuffsize);

    cLen = w_send(cClient, reqbuff, reqbuffsize);
    
    if((cLen < 0)||(cLen == 0))
    {
        printf("send() failure!\n");
        return;
    }

    char* cbuf;
    int rc = w_recv(cClient, cbuf);
    
    if(rc == 0)
    {
        printf("connection error, got size 0\n");
        return;
    }
    
    ReqResponse response;
    response.ParseFromArray(cbuf, rc);
    if(response.rspcode() == REQ_FAILED)
    {
        printf("ERROR GET IMAGE\n");
        return;
    }
    delete cbuf;

    char* content_buf;
    int content_len = w_recv(cClient, content_buf);
    
    if(rc == 0)
    {
        printf("connection error when recv img content\n");
        return;
    }

    string filePath = "./files/" + fileName;
    write_local_file(filePath, content_buf, content_len);
    
    delete content_buf;

    close(cClient);
    printf("done\n");
}

void do_send_file(string fileName)
{
    int cPort = DEFAULT_PORT;
    int cClient = 0;
    int cLen = 0;
    struct sockaddr_in cli;
    
    cli.sin_family = AF_INET;
    cli.sin_port = htons(cPort);
    cli.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    
    cClient = socket(AF_INET, SOCK_STREAM, 0);


    //get file content
    char* fileContent;
    size_t fileLen;
    if(!get_local_file(fileName, fileContent, fileLen))
    {
        printf("error open file\n");
        return;
    }

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


    cLen = w_send(cClient, fileContent, fileLen);
    delete fileContent;
    
    if((cLen < 0)||(cLen == 0))
    {
        printf("send() failure!\n");
        return;
    }

    char* rbuff;
    int rc = w_recv(cClient, rbuff);
    
    if(rc == 0)
    {
        printf("connection error, got size 0\n");
        return;
    }
    
    ReqResponse response;
    response.ParseFromArray(rbuff, rc);
    if(response.rspcode() == REQ_FAILED)
    {
        printf("ERROR GET IMAGE\n");
        return;
    }
    delete rbuff;

    close(cClient);
    printf("done\n");
}
#endif



#ifndef USING_PROTOBUFF
/*
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

    char* cbuf;
    int rc = w_recv(cClient, cbuf);
    
    if(rc == 1)
    {
        //file not find
        if(cbuf[0] == '0'){
            printf("file not found\n");
        }
    }
    else if(rc > 0)
    {
        string filePath = "./files/" + fileName;
        write_local_file(filePath, cbuf, rc);
    }

    delete cbuf;

    close(cClient);
    printf("done\n");
}*/

void do_send_file(string fileName)
{
    int cPort = DEFAULT_PORT;
    int cClient = 0;
    int cLen = 0;
    struct sockaddr_in cli;
    
    cli.sin_family = AF_INET;
    cli.sin_port = htons(cPort);
    cli.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    
    cClient = socket(AF_INET, SOCK_STREAM, 0);


    //get file content
    char* fileContent;
    size_t fileLen;
    if(!get_local_file(fileName, fileContent, fileLen))
    {
        printf("error open file\n");
        return;
    }

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
    //test write to local first
    //write_local_file(fileName + ".bak", fileContent, fileLen);

    cLen = w_send(cClient, fileContent, fileLen);
    if((cLen < 0)||(cLen == 0))
    {
        printf("send() failure!\n");
        return;
    }

    delete fileContent;

    /*
    char* pResponse;
    int rc = w_recv(cClient, pResponse);
    
    printf("%s\n",pResponse);

    delete pResponse;
    */

    close(cClient);
    printf("done\n");
}
#endif

int main(int argc, char** argv)
{
    string fileName;
    string method;
    cout<<"command:";
    while(cin>>method>>fileName)
    {
        if(method == "upload")
            do_send_file(fileName);
        else if(method == "get")
        {
            retrive_file(fileName);
        }
        cout<<"commond:";
    }
    return 0;
}
