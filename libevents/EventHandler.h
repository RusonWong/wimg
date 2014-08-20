#ifndef CONN
#define CONN
#include "event.h"
#include "EntityManager.h"

//real handler
void event_handler(const int fd,const short which,void *arg);
//handle socket event
void handle_connection(const int sfd, struct event_base* base);
#endif
