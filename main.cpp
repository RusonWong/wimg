#include "LocalStorage.h"


int main()
{
	const char* buff = "fwofjlsfjoweflasjfwoefslfdjwfoweofjwejflsfwjoflsdfjwofjlsjdfe";
	LocalStorage storage;
	storage.save_file(buff,strlen(buff),"hello.txt");
	return 1;
}