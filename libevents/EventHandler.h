#ifndef CONN
#define CONN
#include <event.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct conn conn;
struct conn
{
	int sfd;
	struct event event;
};
void conn_init(void);

conn *conn_from_freelist();
bool conn_add_to_freelist(conn *c);
void conn_free(conn *c);
//real handler
void event_handler(const int fd,const short which,void *arg);
//handle socket event
void handle_connection(const int sfd, struct event_base* base);
#endif
