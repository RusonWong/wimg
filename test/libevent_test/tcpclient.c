#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define DEFAULT_PORT 9999
#define SERVER_ADDR "127.0.0.1"
#define THREAD_COUNT 1

void test()
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
    
    //cLen = recv(cClient, cbuf, sizeof(cbuf),0);
//send parameter
    //char* imgId = "1"
    //sLen = send(cClient, imgId,     
    int count = 1;
    while(count){  
	    char* buff = "hello";
	    cLen = send(cClient, buff, 5,0);
	    if((cLen < 0)||(cLen == 0))
	    {
		  printf("send() failure!\n");
		return;
	    }
	    cLen = recv(cClient, cbuf, sizeof(cbuf),0);
	    if((cLen < 0)||(cLen == 0))
	    {
		  printf("recv() failure!\n");
		return;
	    }
	    //printf("recv() Data From Server: [%s]\n", cbuf);
		count--;
    }
    close(cClient);
    printf("done\n");
}

void* do_test(void* arg){
	test();
	return (void*)0;
}

int main(int argc, char** argv)
{
    int threadCount = THREAD_COUNT;
    while(threadCount)
	{	
		printf("thread start\n");
		pthread_t tid;
		int err;
		err = pthread_create(&tid,NULL,do_test,NULL);
		if(err!=0)
		{
			printf("error creating thread");
		}
		threadCount--;
	}
    while(1){}    
    return 0;
}
