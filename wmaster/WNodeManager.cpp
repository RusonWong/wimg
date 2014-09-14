#include "WNodeManager.h"


WNodeManager* WNodeManager::p_nodemanager_instance = NULL;


WNodeManager::WNodeManager()
{

}

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


///using consistent hash to dispatch requst
//key: md5 of some image
WNode WNodeManager::dispatchRequest(string key)
{
	//TODO, here just using a normal hash
	int nodeCount = this->runningNodes.size();
	int rkey = (int)key[0];
	int p = rkey%nodeCount;

	return runningNodes[p];
}