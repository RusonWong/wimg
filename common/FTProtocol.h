#ifndef FILE_TRANSFER_PROTOCOL
#define FILE_TRANSFER_PROTOCOL
#include <stddef.h>

#include "WPB.pb.h"

#define METHOD_GET '1'
#define METHOD_SET '2'
#define METHOD_ADD_NODE '3'

#define MAX_LEN_LEN 10

typedef ::google::protobuf::Message PB_MESSSAGE;

//send
int w_send(int fd, const char* buff, size_t len);

//recv
int w_recv(const int fd, char* &buff);


//send

int w_send_pb(int fd, PB_MESSSAGE* obj);

//test
void say_hello();

#endif