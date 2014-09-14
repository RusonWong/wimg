#include "ConHash.h"
#include "md5.h"


//add virtual node
void ConHash::addVirtualNode(CVirtualNode* vNode)
{
	//calculate hash value
	int value = hash(vNode->getKey());
	vNode->setHashValue(value);

	//insert into  vNodeList
	int count = vNodeList.size();
	int pos = 0;
	for(; pos < count; pos++)
	{
		CVirtualNode* n = vNodeList[pos];
		if(n->getHashValue() > value)
			break;
	}
	//insert
	vNodeList.insert(vNodeList.begin() + pos, vNode);

	//this->vNodeList.push_back(vNode);
	for(int i = 0; i < vNodeList.size(); i++)
	{
		cout<<"["<<vNodeList[i]->getHashValue()<<"] ";
	}
	cout<<endl;
}


//add value set
int ConHash::addNode(ConHashNode* node, int  vNodeCount)
{
	//create virtual nodes and add them to ConHashNode and VNodeList 
	string nodeKey = node->getKey();
	for(int i = 0; i < vNodeCount; i++)
	{
		CVirtualNode* vNode = new CVirtualNode();

		//set new key
		string new_key = nodeKey + "#" + (char)(48 + i);
		vNode->setKey(new_key);

		vNode->setActualNode(node);
		//add vnode to node
		node->addVirtualNode((void*)vNode);
		//add to vNodeList
		this->addVirtualNode(vNode);
	}
}


//find the node to proccess the req key
ConHashNode* ConHash::hash2Node(string key)
{
	//calculate hash value
	int v = hash(key);

	//find the virtual node
	int min = vNodeList[0]->getHashValue();
	int max = vNodeList[vNodeList.size() - 1]->getHashValue();

	int pos = 0;
	if(v > max || v < min)
	{
		pos = 0;
	}
	else
	{
		//binary search the virtual node
		int left = 0;
		int right = vNodeList.size();
		int mid;

		while(right - left > 1)
		{
			mid = (left + right)/2;
			if(v < vNodeList[mid]->getHashValue())
			{
				right = mid;
			}else
			{
				left = mid;
			}
		}
		pos = right;
	}

	return vNodeList[pos]->getActualNode();
}

int ConHash::removeNode(ConHashNode* node)
{
	vector<CVirtualNode*>::iterator iter = vNodeList.begin();
	while(iter != vNodeList.end())
	{
		if((*iter)->getActualNode() == node)
		{
			//find virtual node
			printf("find virtual node and erase it\n");
			iter = vNodeList.erase(iter);
		}
		else
		{
			iter ++;
		}
	}
	return 1;
}

int ConHash::hash(string key)
{
	key = MD5(key).toString();
	cout<<"md5 key:" << key<<endl;

	//return (int)key[0];
	int ret = 0;

	for(int i = 0; i < 5; i++)
	{
		cout<<"char:"<<key[i]<<",int:"<<(int)key[i]<<endl;
		ret += ret *10 + (int)key[i];
	}
	return ret;
}