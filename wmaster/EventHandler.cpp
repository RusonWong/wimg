#include "EventHandler.h"

#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "WNodeManager.h"
#include "FTProtocol.h"
#include <arpa/inet.h>

#include "WPB.pb.h"

using namespace std;


void on_req_set(const int fd)
{
	//get req body
	char* req_buff;
	size_t rb_len = w_recv(fd, req_buff);
	if (!rb_len > 0)
	{
		cerr<<"connection error\n";
		return;
	}

	ReqSet reqSet;
	if(!reqSet.ParseFromArray(req_buff, rb_len))
	{
		cerr<<"error when parse get request\n";
		return;
	}

	WNode node = WNodeManager::getInstance()->dispatchRequest(reqSet.md5());

	NodeInfo ninfo;
	ninfo.set_nodeaddr(node.nodeIP);
	ninfo.set_nodeport(node.nodePort);

	int sl = w_send_pb(fd, &ninfo);

	delete req_buff;
}

void on_req_get(const int fd)
{

}


void on_req_node_add(const int fd)
{
	WNodeManager* nodeManager = WNodeManager::getInstance();

	char* req_buff;
	size_t req_len;
	int cl = w_recv(fd,req_buff);

	if(cl > 0)
	{
		NodeInfo req;
		if(!req.ParseFromArray(req_buff, cl))
		{
			cerr<<"error when parse get request\n";
			//response.set_rspcode(REQ_FAILED);
			//response.set_errcode(ERR_INVALID_PARAMS);
			//w_send_pb(fd, &response);
			return;
		}

		cout<<"client addr is "<<req.nodeaddr()<<",port is "<<req.nodeport()<<endl;
		
		WNode* node = new WNode(req.nodeaddr(), req.nodeport());
		//node->nodeName = "";
		//node->nodeIP = req.nodeaddr();
		//node->nodePort = req.nodeport();

		nodeManager->addNode(node);
		cout<<"node add ok"<<endl;
	}
	else
	{
		cout<<"can not get node addr\n";
	}
 }

 void on_req_node_remove(const int fd)
 {
 	WNodeManager* nodeManager = WNodeManager::getInstance();

	char* req_buff;
	size_t req_len;
	int cl = w_recv(fd,req_buff);

	if(cl > 0)
	{
		NodeInfo req;
		if(!req.ParseFromArray(req_buff, cl))
		{
			cerr<<"error when parse get request\n";
			//response.set_rspcode(REQ_FAILED);
			//response.set_errcode(ERR_INVALID_PARAMS);
			//w_send_pb(fd, &response);
			return;
		}

		cout<<"client addr is "<<req.nodeaddr()<<",port is "<<req.nodeport()<<endl;
		
		nodeManager->removeNode(req.nodeaddr(), req.nodeport());
		cout<<"node remove ok"<<endl;
	}
	else
	{
		cout<<"can not get node info\n";
	}
 }




int on_request_arrive(const int fd, conn* c)
{
	//GET METHOD
	char* method;
	int rmc = w_recv(fd,method);
	if (rmc == 0)
	{
		return 0;
	}

	if(method[0] == METHOD_GET)
	{
		cout<<"method: get \n";
		on_req_get(fd);
	}
	else if(method[0] == METHOD_SET)
	{
		cout<<("method: set \n");
		on_req_set(fd);
	}
	else if(method[0] == METHOD_ADD_NODE)
	{
		cout<<"method: add node\n";
		on_req_node_add(fd);
	}
	else if(method[0] == METHOD_REMOVE_NODE)
	{
		cout<<"method: remove node\n";
		on_req_node_remove(fd);
	}
	else
	{
		cout<<("method: not known \n");
	}
	delete method;
	return 0;
}

//real handler
void event_handler(const int fd,const short which,void *arg)
{
	conn* c = (conn*)arg;
	int handle_ret = on_request_arrive(fd, c);
	cout<<("connection closed\n");
	close(fd);
	event_del(&(c->event));

	if(conn_add_to_freelist(c))
			conn_free(c);
		
	return;
}


void single_thread_event_handler(const int fd, const short which)
{
	int handle_ret = on_request_arrive(fd,NULL);
	close(fd);
}








