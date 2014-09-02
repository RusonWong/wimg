#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CNode
{
private:
	vector<void*> vNodeList;

public:
	CNode(){};
	~CNode(){};
	virtual string getKey();

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
	CNode* pNode;
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

	CNode* getActualNode()
	{
		return this->pNode;
	}

	void setActualNode(CNode* node);
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

	int hash(string key);
public:
	ConsistentHash(){};
	~ConsistentHash();

	//add value set
	int addNode(CNode* node, int  vNodeCount = -1);
	CNode* hash2Node(string key);
};