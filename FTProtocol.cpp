#include "FTProtocol.h"
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


//send
int w_send(int fd,const char* content, size_t len)
{
	//send len first
	printf("in w_send \n");

	char bufftemp[MAX_LEN_LEN];
	int llen = sprintf(bufftemp, "%d", len);

	printf("cclen is %d, bufftemp is %s \n",llen,bufftemp);

	//memcpy(cLenBuff + (10 - llen), bufftemp, llen);
	printf("buff is \"%s\"",bufftemp);

	int wc = write(fd, bufftemp, 10);
	if(wc <= 0)
	{
		return 0;
	}

	//send content
	wc = write(fd,content,len);
	if(wc <= 0)
	{
		return 0;
	}
}

//recv
int w_recv(const int fd, char* &content)
{
	//get content size
	char content_len_buff[10];
	int rc = read( fd, content_len_buff, 10);
	if(rc != 10)
	{
		printf("error when read content size\n");
		return 0;
	}
	int content_len = atoi(content_len_buff);
	printf("content len will be:%d\n", content_len);

	content = new char[content_len];
	rc = read(fd, content, content_len);
	if(rc ==0)
	{
		printf("error when read content size\n");
		return 0;
	}
	return rc;
}


void say_hello()
{
	printf("say hello");
}