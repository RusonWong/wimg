#include "ConHash.h"



//add virtual node
void ConHash::addVirtualNode(CVirtualNode* vNode)
{
	//calculate hash value
	int value = hash(vNode->getKey());
	vNode.setHashValue(value);

	//insert into  vNodeList
	int count = vNodeList.size();
	int pos = 0;
	for(; pos < count; pos++)
	{
		CVirtualNode n = vNodeList[pos];
		if(n->getHashValue() > value)
			break;
	}
	//insert
	vNodeList.insert(vNodeList.begin() + pos, vNode);

	//this->vNodeList.push_back(vNode);
}


//add value set
int ConHash::addNode(CNode* node, int  vNodeCount = -1)
{
	//create virtual nodes and add them to CNode and VNodeList 
	string nodeKey = node.getKey();
	for(int i = 0; i < vNodeCount; i++)
	{
		CVirtualNode* vNode = new CVirtualNode();

		//set new key
		string new_key = nodeKey + "#" + itoa(i);
		vNode.setKey(new_key);

		vNode.setActualNode(node);
		//add vnode to node
		node->addVirtualNode((void*)vNode);
		//add to vNodeList
		this->addVirtualNode(vNode);
	}
}


//find the node to proccess the req key
CNode* ConHash::hash2Node(string key)
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

int ConHash::hash(string key)
{
	return (int)key[0];
}