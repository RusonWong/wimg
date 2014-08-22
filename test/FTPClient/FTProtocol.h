#ifndef FILE_TRANSFER_PROTOCOL
#define FILE_TRANSFER_PROTOCOL
#include <stddef.h>


#define METHOD_GET '1'
#define METHOD_SET '2'


//send
int w_send(int fd, const char* buff, size_t len);

//recv
int w_recv(const int fd, char* &buff);

//test
void say_hello();

#endif