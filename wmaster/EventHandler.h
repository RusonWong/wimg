#ifndef CONN
#define CONN
#include "event.h"
#include "EntityManager.h"

//real handler
void event_handler(const int fd,const short which,void *arg);
void single_thread_event_handler(const int fd, const short which);
#endif
