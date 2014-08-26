#include "EventHandler.h"

#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "FTProtocol.h"
#include "LocalStorage.h"
#include "LibeventThread.h"
#include <iostream>

#include "ImageUtil.h"
#include "md5.h"

using namespace std;

#define USING_PROTOBUFF 1

//without protobuf
#ifndef USING_PROTOBUFF
#endif

//with protobuff version
#ifdef USING_PROTOBUFF
#include "WPB.pb.h"

int on_request_get(const int fd, conn* c)
{
	//get request
	char *reqContent;
	int rc = w_recv(fd, reqContent);
	
	ReqGet req;
	ReqResponse response;
	if (rc == 0)
	{
		return 0;
	}
	if(!req.ParseFromArray(reqContent, rc))
	{
		//printf("error when parse get req\n");
		cerr<<"error when parse get request\n";
		response.set_rspcode(REQ_FAILED);
		response.set_errcode(ERR_INVALID_PARAMS);
		w_send_pb(fd, &response);
		return 0;
	}

	size_t imageid_len = req.imageid().length();
	char* buff = (char*)req.imageid().c_str();

	char* buffptr = NULL;
	size_t len = 0;
	
	std::string fileName(buff,imageid_len);
	
	int cache_rt = ((LIBEVENT_THREAD*)c->thread_param)->mcc.cache_get(buff, imageid_len, buffptr, len);
	if(cache_rt == 0){
		LocalStorage* plocalStorage = LocalStorage::getInstance();
		

		if(plocalStorage->get_file(fileName, buffptr, len) == 0)
		{
			//printf("can not find file %s\n", fileName);
			cout<<"can not find file "<<fileName<<"\n";
			response.set_rspcode(REQ_FAILED);
			response.set_errcode(ERR_FILE_NOT_FOUND);
			w_send_pb(fd, &response);
			return 0;
		}

		//set cache
		int cache_set_rt = ((LIBEVENT_THREAD*)c->thread_param)->mcc.cache_set(buff, imageid_len, buffptr, len);
		if(cache_set_rt)
		{
			//printf("set cache of %s done\n",buff);
			cout<<"set cache of "<<fileName<<" done\n";
		}
	}
	else{
		//printf("hit cache of %s\n", buff);
		cout<<"hit cache of "<<fileName<<endl;
	}
	//printf("find file %s, len %d\n",buff,len);
	cout<<"get content of "<<fileName<<",len is "<<len<<endl;

	//proccess image
	IMG_PROCCESS_CONFIG ipConf;
	ipConf.out_height = req.height();
	ipConf.out_width = req.width();

	char* new_img_buff;
	size_t new_img_len;
	int p_ret = resize_image(buffptr,len,new_img_buff,new_img_len,&ipConf);
	//TODO  handle error

	response.set_rspcode(REQ_SUCCESS);
	w_send_pb(fd, &response);

	//send image buff
	int wc = w_send(fd, new_img_buff, new_img_len);
	//clean mem
	delete new_img_buff;
	delete buffptr;
	//delete buff;
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
	ReqResponse response;
	LocalStorage* plocalStorage = LocalStorage::getInstance();
	//get file type
	char* fileName;
	size_t fn_len = w_recv(fd, fileName);
	if (!fn_len > 0)
	{
		//printf("connection error");
		cerr<<"connection error\n";
		return -1;
	}

	std::string filePath(fileName,fn_len);

	char* content;
	size_t rc = w_recv(fd, content);

	if(rc <=0)
	{
		cerr<<"connection error";
		delete fileName;
		return -1;
	}

	//gen md5 key
	string new_name = MD5(content, rc).toString();
	cout<<"new name is "<<new_name<<endl;

	//save to cache
	int cache_set_rt = ((LIBEVENT_THREAD*)c->thread_param)->mcc.cache_set((char*)new_name.c_str(), new_name.length(), content, rc);
	if( cache_set_rt )
	{
		//printf("cache of %s set done\n", filePath);
		cout<<"cache of "<<filePath<<" set success\n";
	}
	else
	{
		cout<<"cache of "<<filePath<<" set failed\n";
	}
	

	plocalStorage->save_file(content, rc,new_name);

	response.set_rspcode(REQ_SUCCESS);
	response.set_newname(new_name);

	w_send_pb(fd, &response);

	return 0;
}
#endif

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









