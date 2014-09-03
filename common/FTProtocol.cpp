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
	//printf("in w_send \n");
	//char cLenBuff[10] = {'\0'};

	char bufftemp[10] = {'\0'};
	int llen = sprintf(bufftemp, "%d", len);

	int wc = write(fd, bufftemp, 10);
	if(wc <= 0)
	{
		return 0;
	}

	wc = send(fd, content, len, MSG_WAITALL);
	printf("actual sent size %d\n", wc);
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

	rc = recv(fd, content, content_len, MSG_WAITALL);
	printf("actual got total: %d\n",rc);
	return rc;
}


int w_send_pb(int fd, PB_MESSSAGE* obj)
{
	size_t pb_len = obj->ByteSize();
	printf("in send_pb, pb len is:%d\n", pb_len);
	char* buff = new char[pb_len];
	obj->SerializeToArray(buff, pb_len);
	int ret = w_send(fd, buff, pb_len);
	delete buff;

	return ret;
}

void say_hello()
{
	printf("say hello");
}