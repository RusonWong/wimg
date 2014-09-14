#include "WNodeManager.h"
#include "common_utils.h"


WNode::WNode(string addr, int port)
{
	string key = addr + ":" + witoa(port);
	this->key = key;
	this->nodeIP = addr;
	this->nodePort = port;
}


WNodeManager* WNodeManager::p_nodemanager_instance = NULL;

WNodeManager::WNodeManager()
{

}

/*
int WNodeManager::addNode(WNode new_node)
{	
	cout<<"current node count:"<<runningNodes.size()<<endl;
	this->runningNodes.push_back(new_node);
	cout<<"current node count:"<<runningNodes.size()<<endl;
}

int WNodeManager::removeNode(WNode node)
{
	cout<<"removing node "<<node.nodeIP<<":"<<node.nodePort<<endl;
	std::vector<WNode>::iterator iter= runningNodes.begin();
	for(;iter != runningNodes.end(); iter++)
	{
		if(iter->nodeIP == node.nodeIP && iter->nodePort == node.nodePort)
		{
			cout<<"find and removing\n";
			runningNodes.erase(iter);
			return 1;
		}
	}
	cout<<"can not find the node";
	return 0;
}
*/

int WNodeManager::addNode(WNode* new_node)
{	
	cout<<"current node count:"<<runningNodes.size()<<endl;
	this->runningNodes.push_back(new_node);
	cout<<"current node count:"<<runningNodes.size()<<endl;

	this->conHash.addNode(new_node);
}

int WNodeManager::removeNode(string key)
{
	//first find the Wnode
	WNode* pNode = findNode(key);
	if(!pNode)
	{
		return 0;
	}
	this->conHash.removeNode(pNode);

	//remove from list
	std::vector<WNode*>::iterator iter= runningNodes.begin();
	while(iter != runningNodes.end())
	{
		if((*iter)->key == key)
		{
			iter = runningNodes.erase(iter);
		}
		else
		{
			iter ++;
		}
	}
	delete pNode;
	return 1;
}

int WNodeManager::removeNode(string addr, int port)
{
	string key = addr + ":" + witoa(port);
	return removeNode(key);
}


///using consistent hash to dispatch requst
//key: md5 of some image
WNode WNodeManager::dispatchRequest(string key)
{
	//TODO, here just using a normal hash
	int nodeCount = this->runningNodes.size();
	int rkey = (int)key[0];
	int p = rkey%nodeCount;

	return *runningNodes[p];
}

WNode* WNodeManager::findNode(string key)
{
	std::vector<WNode*>::iterator iter= runningNodes.begin();
	for(;iter != runningNodes.end(); iter++)
	{
		if((*iter)->key == key)
		{
			cout<<"find the node\n";
			return (WNode*)(*iter);
		}
	}
	cout<<"can not find the node";
	return NULL;
}