#ifndef WNODEMANAGER_H
#define WNODEMANAGER_H

#include <iostream>
#include <string>
#include <vector>

#include "ConHash.h"

using namespace std;

class WNode: public ConHashNode
{
public:
	string 	nodeName;
	string	nodeIP;
	int 	nodePort;


	WNode(string addr, int port);
};


class WNodeManager
{
private:
	WNodeManager();
	static WNodeManager* p_nodemanager_instance;
	//using common hash
	vector<WNode*> runningNodes;
	//using consistent hash
	ConHash conHash;


	WNode* findNode(string key);
public:
	~WNodeManager()
	{
		if(p_nodemanager_instance)
		{
			delete p_nodemanager_instance;
		}
	}

	static WNodeManager* getInstance()
	{
		if(!p_nodemanager_instance)
		{
			p_nodemanager_instance = new WNodeManager();
		}

		return p_nodemanager_instance;
	}

	int addNode(WNode* new_node);
	int removeNode(string key);
	int removeNode(string addr, int port);

	WNode dispatchRequest(string key);
};

#endif