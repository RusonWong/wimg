#include "EventHandler.h"

#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "FTProtocol.h"
#include "LocalStorage.h"

int on_request_get(const int fd)
{
	char *buff;
	int rc = w_recv(fd, buff);
	
	if (rc == 0)
	{
		return 0;
	}
	LocalStorage* plocalStorage = LocalStorage::getInstance();
	std::string fileName(buff);

	char* buffptr;
	size_t len;
	if(plocalStorage->get_file(fileName, buffptr, len) == 0)
	{
		printf("can not find file %s\n", buff);
		return 0;
	}
	printf("find file %s, len %d\n",buff,len);
	int wc = w_send(fd, buffptr, len);
	free(buffptr);
}

//int LocalStorage::save_file(const char* buff, size_t file_size, std::string file_name)
//handle upload a image document request
int on_request_set(const int fd)
{	
	LocalStorage* plocalStorage = LocalStorage::getInstance();
	//get file type
	char* fileName;
	int rc = w_recv(fd, fileName);
	if (rc == -1)
	{
		printf("connection error");
		return -1;
	}

	char* content;
	rc = w_recv(fd, content);

	std::string filePath(fileName);
	plocalStorage->save_file(content, rc,filePath);

	int wc = w_send(fd, "done", 4);
	return 0;
}



int on_request_arrive(const int fd)
{
	//GET METHOD
	char* method;
	int rmc = w_recv(fd,method);
	printf("get mehtod length:%d\n",rmc);
	if (rmc == 0)
	{
		return 0;
	}

	if(method[0] == METHOD_GET)
	{
		printf("method: get \n");
		return on_request_get(fd);
	}
	else if(method[0] == METHOD_SET)
	{
		printf("method: set \n");
		return on_request_set(fd);
	}
	printf("method: not known \n");

	delete method;
	return 0;
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









