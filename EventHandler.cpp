#include "EventHandler.h"

#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "LocalStorage.h"

int on_request_arrive(const int fd)
{
	char buff[128];
	memset(buff,0,sizeof(buff));
	int rc = read(fd, buff, 128);
	
	if (rc == 0)
	{
		return 0;
	}
	LocalStorage localStorage;
	std::string fileName(buff);

	//int get_file(std::string key, char* &buffptr,size_t& len);
	char* buffptr;
	size_t len;
	if(localStorage.get_file(fileName, buffptr, len) == 0)
	{
		printf("can not find file %s\n", buff);
		return 0;
	}
	printf("find file %s, len %d\n",buff,len);
	int wc = write(fd, buffptr, len);
	return 1;
}

//real handler
void event_handler(const int fd,const short which,void *arg)
{
	conn* c = (conn*)arg;
	int handle_ret = on_request_arrive(fd);
	printf("connection closed\n");
	close(fd);
	event_del(&(c->event));

	if(conn_add_to_freelist(c))
			conn_free(c);
		
	return;
	/*
	char buf[3];
	memset(buf, 0, sizeof(buf));
	int rc=read(fd,buf,3);
	printf("data lenth is:%d\n",rc);
	if (rc == 0)
	{
		printf("connection closed\n");
		close(fd);
		event_del(&(c->event));

		if( conn_add_to_freelist(c))
			conn_free(c);
		
		return;
	}
	buf[rc] = '\n';
	printf("data received:%s\n", buf);
	*/
	//printf("current tid is:%d\n", (int)pthread_self());
}









