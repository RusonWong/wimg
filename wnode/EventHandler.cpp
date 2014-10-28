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
#include "Config.h"
#include "ImageUtil.h"
#include "md5.h"
#include "common_utils.h"
#include "MCConnector.h"

using namespace std;

#define USING_PROTOBUFF 1

//without protobuf
#ifndef USING_PROTOBUFF
#endif


extern Config globalConfig;
extern MCConnector global_memcached_mcc;
extern MCConnector global_beansdb_mcc;


//with protobuff version
#ifdef USING_PROTOBUFF
#include "WPB.pb.h"


//get image that is proccessed
int get_proccessed_file(string temp_key, char* &retbuff, size_t &ret_len,  MCConnector* mc, MCConnector* bc)
{
	
	int got_file = 0;
	if( globalConfig.use_memcached)
	{
		got_file = mc->cache_get((char*)temp_key.c_str(), temp_key.length(), retbuff, ret_len);
	}
	if(got_file == 0){
		//benasdb
		if( globalConfig.storage_mode == 2)
		{
			int c_set_ret = bc->cache_get((char*)temp_key.c_str(), temp_key.length(), retbuff, ret_len);
			if( c_set_ret == 0)
			{
				cout<<"can not find file "<<temp_key<<" from beansdb\n";
				return 0;
			}
			else
			{
				cout<<"find file "<<temp_key<<" from beansdb\n";
			}
			
		}
		//local
		else if(globalConfig.storage_mode == 1)
		{
			LocalStorage* ps = LocalStorage::getInstance();
			int  ret = ps->get_file(temp_key, retbuff, ret_len);
			if( ret == 0)
			{
				cout<<"can not find file "<<temp_key<<" from LocalStorage\n";
				return 0;
			}
			else
			{
				cout<<"find file "<<temp_key<<" from LocalStorage\n";
			}
		}
	}
	else
	{
		cout<<"hit cache of "<<temp_key<<endl;
	}

	return 1;
}


int save_proccessed_file(string temp_key, char* filecontent, size_t content_len, MCConnector* mc, MCConnector* bc)
{
	int cache_set_rt;
	if(globalConfig.use_memcached == 1)
	{
		cache_set_rt = mc->cache_set((char*)temp_key.c_str(), temp_key.length(), filecontent, content_len);
		if( cache_set_rt )
		{
			cout<<"cache of "<<temp_key<<" set success\n";
		}
		else
		{
			cout<<"cache of "<<temp_key<<" set failed\n";
		}
	}
	
	if( globalConfig.storage_mode == 2)
	{
		cache_set_rt = bc->cache_set((char*)temp_key.c_str(), temp_key.length(), filecontent, content_len);
		if( cache_set_rt )
		{
			cout<<"save "<<temp_key<<" to beansdb success\n";
		}
		else
		{
			cout<<"save "<<temp_key<<" to beansdb failed\n";
		}
	}
	else if(globalConfig.storage_mode == 1){
		LocalStorage* plocalStorage = LocalStorage::getInstance();
		int ret = plocalStorage->save_file(filecontent, content_len, temp_key);
		if(ret == 1)
		{
			cout<<"save "<<temp_key<<" to local success\n";
		}
		else
		{
			cout<<"save "<<temp_key<<" to local failed\n";
		}
	}

	return 1;
}


int on_request_get(const int fd, MCConnector* memcached_connector, MCConnector* beansdb_connector)
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

	std::string fileName(buff,imageid_len);

	char* buffptr = NULL;
	size_t len = 0;
	//////////////////////try get proccessed file//////////////////////

	int temp_file_got = 0;
	if( globalConfig.save_new == 1 && req.width() != -1)
	{
		string temp_key = fileName + ":" + witoa(req.width()) + ":" + witoa(req.height());
		temp_file_got = get_proccessed_file(temp_key, buffptr, len, memcached_connector, beansdb_connector);

		if(temp_file_got == 1)
		{
			response.set_rspcode(REQ_SUCCESS);
			w_send_pb(fd, &response);

			//send image buff
			int wc = w_send(fd, buffptr, len);
			return 1;
		}
	}

	////////////////////get file and resize start/////////////////////
	
	
	int got_file = 0;

	if( globalConfig.use_memcached == 1)
	{
		got_file = memcached_connector->cache_get(buff, imageid_len, buffptr, len);
	}

	if(got_file == 0){
		//benasdb
		if( globalConfig.storage_mode == 2)
		{
			int c_set_ret = beansdb_connector->cache_get(buff, imageid_len, buffptr, len);
			if( c_set_ret == 0)
			{
				cout<<"can not find file "<<fileName<<"from beansdb\n";
				response.set_rspcode(REQ_FAILED);
				response.set_errcode(ERR_FILE_NOT_FOUND);
				w_send_pb(fd, &response);
				return 0;
			}
			
		}
		//local
		else if(globalConfig.storage_mode == 1)
		{
			LocalStorage* ps = LocalStorage::getInstance();
			int  ret = ps->get_file(fileName, buffptr, len);
			if( ret == 0)
			{
				cout<<"can not find file "<<fileName<<" from LocalStorage\n";
				response.set_rspcode(REQ_FAILED);
				response.set_errcode(ERR_FILE_NOT_FOUND);
				w_send_pb(fd, &response);
				return 0;
			}
		}

		//set cache
		if(globalConfig.use_memcached == 1)
		{
			int cache_set_rt = memcached_connector->cache_set(buff, imageid_len, buffptr, len);
			if(cache_set_rt)
			{
				cout<<"set cache of "<<fileName<<" done\n";
			}
		}

	}
	else{
		//printf("hit cache of %s\n", buff);
		cout<<"hit cache of "<<fileName<<endl;
	}
	//printf("find file %s, len %d\n",buff,len);
	cout<<"get content of "<<fileName<<",len is "<<len<<endl;

	char* new_img_buff = buffptr;
	size_t new_img_len = len;

	if( req.width() != -1)
	{
		//proccess image
		IMG_PROCCESS_CONFIG ipConf;
		ipConf.out_height = req.height();
		ipConf.out_width = req.width();
		ipConf.keep_proportion = req.keep_proportion();

		int p_ret = resize_image(buffptr,len,new_img_buff,new_img_len,&ipConf);

		if(p_ret == 0)
		{
			new_img_len = len;
			new_img_buff = buffptr;
		}
		else
		{
			if(globalConfig.save_new == 1)
			{
				string temp_key = fileName + ":" + witoa(req.width()) + ":" + witoa(req.height());
				int s_ret = save_proccessed_file(temp_key, new_img_buff, new_img_len, memcached_connector, beansdb_connector);
				if(s_ret == 1)
				{
					cout<<"save "<<temp_key<<" success"<<endl;
				}
				else
				{
					cout<<"save "<<temp_key<<" failed"<<endl;
				}
			}
		}
	}

	response.set_rspcode(REQ_SUCCESS);
	w_send_pb(fd, &response);

	//send image buff
	int wc = w_send(fd, new_img_buff, new_img_len);
	//clean mem
	if(buffptr != new_img_buff)
		delete new_img_buff;
	
	delete buffptr;
	return 1;
}

/*
    int cache_get(char* key, size_t key_len, char* &value, size_t &value_len);
    int cache_set(char* key, size_t key_len, char* value, size_t value_len);
*/
//int LocalStorage::save_file(const char* buff, size_t file_size, std::string file_name)
//handle upload a image document request
int on_request_set(const int fd, MCConnector* memcached_connector, MCConnector* beandb_connector)
{	
	ReqResponse response;
	

	//get req body
	char* req_buff;
	size_t rb_len = w_recv(fd, req_buff);
	if (!rb_len > 0)
	{
		//printf("connection error");
		cerr<<"connection error\n";
		return -1;
	}

	ReqSet reqSet;
	reqSet.ParseFromArray(req_buff, rb_len);

	std::string filePath = reqSet.imagename();

	char* content;
	size_t rc = w_recv(fd, content);

	if(rc <=0)
	{
		cerr<<"connection error";
		delete req_buff;
		return -1;
	}


	int origin_width;
	int origin_height;

	int ret = get_img_size(content,rc,origin_width, origin_height);

	//gen md5 key
	string new_name = MD5(content, rc).toString();
	cout<<"new name is "<<new_name<<endl;

	//compression image and save as the primary
	IMG_PROCCESS_CONFIG ipConf;
	ipConf.out_height = std::min(1024,origin_height);
	ipConf.out_width = std::min(1024,origin_height);
	ipConf.keep_proportion = true;

	char* new_img_buff;
	size_t new_img_len;
	int p_ret = resize_image(content,rc,new_img_buff,new_img_len,&ipConf, true);

	if(p_ret == 0)
	{
		new_img_buff = content;
		new_img_len = rc;
	}

	/////////save proccessed image to cache and storage////////////

	int cache_set_rt;
	if(globalConfig.use_memcached == 1)
	{
		cache_set_rt = memcached_connector->cache_set((char*)new_name.c_str(), new_name.length(), new_img_buff, new_img_len);
		if( cache_set_rt )
		{
			cout<<"cache of "<<filePath<<" set success\n";
		}
		else
		{
			cout<<"cache of "<<filePath<<" set failed\n";
		}
	}
	
	if( globalConfig.storage_mode == 2)
	{
		cache_set_rt =  beandb_connector->cache_set((char*)new_name.c_str(), new_name.length(), new_img_buff, new_img_len);
		if( cache_set_rt )
		{
			cout<<"save "<<filePath<<" to beansdb success\n";
		}
		else
		{
			cout<<"save "<<filePath<<" to beansdb failed\n";
		}
	}
	else if(globalConfig.storage_mode == 1){
		LocalStorage* plocalStorage = LocalStorage::getInstance();
		int ret = plocalStorage->save_file(new_img_buff, new_img_len, new_name);
		if(ret == 1)
		{
			cout<<"save "<<filePath<<" to local success\n";
		}

	}

	///////////save origin image to storage/////////////
	string origin_image_name = new_name + ".origin";
	origin_image_name = MD5(origin_image_name).toString();
	cout<<"origin name is "<<origin_image_name<<endl;

	if( globalConfig.storage_mode == 2)
	{
		cache_set_rt = beandb_connector->cache_set((char*)origin_image_name.c_str(), origin_image_name.length(), content, rc);
		if( cache_set_rt )
		{
			cout<<"save origin "<<filePath<<" to beansdb success\n";
		}
		else
		{
			cout<<"save origin "<<filePath<<" to beansdb failed\n";
		}
	}
	else if( globalConfig.storage_mode == 1)
	{
		LocalStorage* plocalStorage = LocalStorage::getInstance();
		plocalStorage->save_file(content, rc, origin_image_name);
	}

	///sned response/////
	response.set_rspcode(REQ_SUCCESS);
	response.set_newname(new_name);

	w_send_pb(fd, &response);

	delete req_buff;
	delete content;
	if(p_ret == 1)
	{
		delete new_img_buff;
	}
	return 0;
}
#endif

int on_request_arrive(const int fd, MCConnector* memcached_connector, MCConnector* beansdb_connector)
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
		return on_request_get(fd, memcached_connector, beansdb_connector);
	}
	else if(method[0] == METHOD_SET)
	{
		printf("method: set \n");
		return on_request_set(fd,  memcached_connector, beansdb_connector);
	}
	printf("method: not known \n");

	delete method;
	return 0;
}

//real handler
void event_handler(const int fd,const short which,void *arg)
{
	conn* c = (conn*)arg;
	MCConnector* m_connector = &(((LIBEVENT_THREAD*)c->thread_param)->mcc);
	MCConnector* b_connector = &(((LIBEVENT_THREAD*)c->thread_param)->bdbc);
	int handle_ret = on_request_arrive(fd, m_connector, b_connector);
	printf("connection closed\n");
	close(fd);
	event_del(&(c->event));

	if(conn_add_to_freelist(c))
			conn_free(c);
		
	return;
}


void single_thread_event_handler(const int fd, const short which)
{
	cout<<"single_thread_event_handler called"<<endl;
	int handle_ret = on_request_arrive(fd,&global_memcached_mcc, &global_beansdb_mcc);
	close(fd);
}







