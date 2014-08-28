#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct WNode
{
	string 	nodeName;
	string	nodeIP;
	int 	nodePort;
	//other params
};


class WNodeManager
{
private:
	WNodeManager();
	vector<WNode> runningNodes;
	static WNodeManager* p_nodemanager_instance;
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

	int addNode(WNode new_node);
	int removeNode(WNode node);

	WNode dispatchRequest(string key);
};