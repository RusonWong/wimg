#ifndef CON_HASH_H
#define CON_HASH_H


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ConHashNode
{
protected:
	vector<void*> vNodeList;

public:
	string key;

	ConHashNode(string _key){
		key = _key;
	};

	ConHashNode(){};
	~ConHashNode(){};
	string getKey()
	{
		return key;
	}

	void setKey(string _key)
	{
		key = _key;
	}

	void addVirtualNode(void* vNode)
	{
		vNodeList.push_back(vNode);
	}

	int getVNodeCount()
	{
		return vNodeList.size();
	}

};


class CVirtualNode
{
private:
	ConHashNode* pNode;
	string key;
	int hashValue;

public:
	CVirtualNode(){};
	~CVirtualNode(){};

	void setKey(string _key)
	{
		key = _key;
	}

	string getKey()
	{
		return key;
	}

	ConHashNode* getActualNode()
	{
		return this->pNode;
	}

	void setActualNode(ConHashNode* node)
	{
		this->pNode = node;
	}

	void setHashValue(int _value)
	{
		this->hashValue = _value;
	}

	int getHashValue()
	{
		return this->hashValue;
	}
};


class ConHash
{
private:
	vector<CVirtualNode*> vNodeList;
	void addVirtualNode(CVirtualNode* vNode);
	int hash(string _key);

public:
	ConHash(){};
	~ConHash(){};

	//add value set
	int addNode(ConHashNode* node, int  vNodeCount = 3);
	ConHashNode* hash2Node(string key);
	int removeNode(ConHashNode* node);
};


#endif