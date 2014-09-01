#include <iostream>
#include "ConHash.h"
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;


string randomKey()
{
	int key_len = rand()%20 + 10;
	char* key = new char[key_len];

	for(int i=0; i < key_len; i++)
	{
		key[i] = (char)(48 + (rand()%10));
	}

	string key_str(key, key_len);
	cout<<"random key:"<<key_str<<endl;
	return key_str;
}

int main()
{
	time_t t;
	srand((unsigned)time(&t)); // 初始化随机数发生器

	ConHash conHash;
	conHash.addNode(new CNode(randomKey()));
	conHash.addNode(new CNode(randomKey()));
	conHash.addNode(new CNode(randomKey()));
	conHash.addNode(new CNode(randomKey()));

	char ch;
	while(cin>>ch)
	{
		string key = randomKey();
		CNode* pNode = conHash.hash2Node(key);
		cout<<"node is:"<<pNode->getKey()<<endl;
	}

}