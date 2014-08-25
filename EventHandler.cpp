#include "EventHandler.h"

#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "FTProtocol.h"
#include "LocalStorage.h"
#include "LibeventThread.h"
//#include "MCConnector.h"

int on_request_get(const int fd, conn* c)
{
	char *buff;
	int rc = w_recv(fd, buff);
	
	if (rc == 0)
	{
		return 0;
	}
	char* buffptr = NULL;
	size_t len = 0;
	
	int cache_rt = ((LIBEVENT_THREAD*)c->thread_param)->mcc.cache_get(buff, rc, buffptr, len);
	if(cache_rt == 0){
		LocalStorage* plocalStorage = LocalStorage::getInstance();
		std::string fileName(buff);

		if(plocalStorage->get_file(fileName, buffptr, len) == 0)
		{
			printf("can not find file %s\n", buff);
			w_send(fd, "0", 1);

			delete buff;
			return 0;
		}

		//set cache
		int cache_set_rt = ((LIBEVENT_THREAD*)c->thread_param)->mcc.cache_set(buff, rc, buffptr, len);
		if(cache_set_rt)
		{
			printf("set cache of %s done\n",buff);
		}
	}
	else{
		printf("hit cache of %s\n", buff);
	}
	printf("find file %s, len %d\n",buff,len);
	int wc = w_send(fd, buffptr, len);
	//clean mem
	delete buffptr;
	delete buff;
	return 1;
}

/*
    int cache_get(char* key, size_t key_len, char* &value, size_t &value_len);
    int cache_set(char* key, size_t key_len, char* value, size_t value_len);
*/

//int LocalStorage::save_file(const char* buff, size_t file_size, std::string file_name)
//handle upload a image document request
int on_request_set(const int fd, conn* c)
{	
	LocalStorage* plocalStorage = LocalStorage::getInstance();
	//get file type
	char* fileName;
	size_t fn_len = w_recv(fd, fileName);
	if (!fn_len > 0)
	{
		printf("connection error");
		return -1;
	}

	char* content;
	size_t rc = w_recv(fd, content);

	//save to cache
	((LIBEVENT_THREAD*)c->thread_param)->mcc.cache_set(fileName, fn_len, content, rc);
	printf("cache of %s set done\n", fileName);

	std::string filePath(fileName);
	plocalStorage->save_file(content, rc,filePath);
	return 0;
}

int on_request_arrive(const int fd, conn* c)
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
		return on_request_get(fd, c);
	}
	else if(method[0] == METHOD_SET)
	{
		printf("method: set \n");
		return on_request_set(fd, c);
	}
	printf("method: not known \n");

	delete method;
	return 0;
}

//real handler
void event_handler(const int fd,const short which,void *arg)
{
	conn* c = (conn*)arg;
	int handle_ret = on_request_arrive(fd, c);
	printf("connection closed\n");
	close(fd);
	event_del(&(c->event));

	if(conn_add_to_freelist(c))
			conn_free(c);
		
	return;
}









