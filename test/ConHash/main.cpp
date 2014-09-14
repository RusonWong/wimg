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

	ConHashNode* node1 = new ConHashNode(randomKey());
	conHash.addNode(node1);
	conHash.addNode(new ConHashNode(randomKey()));
	conHash.addNode(new ConHashNode(randomKey()));
	conHash.addNode(new ConHashNode(randomKey()));

	char ch;
	while(cin>>ch)
	{
		if(ch == 'a')
		{
			string key = randomKey();
			ConHashNode* pNode = conHash.hash2Node(key);
			cout<<"node is:"<<pNode->getKey()<<endl;
		}
		else if(ch == 'd')
		{
			conHash.removeNode(node1);
		}
	}

}