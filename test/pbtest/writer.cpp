#include <iostream>
#include <string>
#include <fstream>
#include "GetReq.pb.h"

using namespace std;


int main()
{
	GetReqMessage msg;
	msg.set_imgid("1.jpg");
	msg.set_width(100);
	msg.set_height(200);


	fstream output("./log", ios::out|ios::trunc |ios::binary);

	if(!msg.SerializeToOstream(&output))
	{
		cerr << "Failed to write log\n";
		return 0;
	}

	return 1;
}