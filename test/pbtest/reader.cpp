#include <iostream>
#include <string>
#include <fstream>
#include "GetReq.pb.h"

using namespace std;


int main()
{
	GetReqMessage msg;

	fstream input("./log", ios::in|ios::binary);

	if(!msg.ParseFromIstream(&input))
	{
		cerr << "Failed to write log\n";
		return 0;
	}
	else
	{
		cout<<msg.imgid()<<endl;
		cout<<msg.width()<<endl;
		cout<<msg.height()<<endl;
	}

	return 1;
}