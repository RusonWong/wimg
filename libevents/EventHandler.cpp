#include "EventHandler.h"

#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//real handler
void event_handler(const int fd,const short which,void *arg)
{
	conn* c = (conn*)arg;

	char buf[3];
	memset(buf, 0, sizeof(buf));
	int rc=read(fd,buf,3);
	printf("data lenth is:%d\n",rc);
	if (rc == 0)
	{
		printf("connection closed\n");
		close(fd);
		event_del(&(c->event));
		return;
	}
	buf[rc] = '\n';
	printf("data received:%s\n", buf);
	printf("current tid is:%d\n", (int)pthread_self());
}


//handle socket event
void handle_connection(const int sfd, struct event_base* base)
{
	conn *c=conn_from_freelist();
	if(NULL==c)
	{
		if(!(c=(conn*)calloc(1,sizeof(conn))))
		{
			fprintf(stderr,"calloc()\n");
			return;
		}
	}
	c->sfd = sfd;

	event_set(&(c->event),sfd,EV_READ|EV_PERSIST,event_handler,(void*)c);
	event_base_set(base,&c->event);

	if(event_add(&c->event,0)==-1)
	{
		if( conn_add_to_freelist(c))
			conn_free(c);
		perror("event_add");
		return;
	}
}






