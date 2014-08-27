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

		if( conn_add_to_freelist(c))
			conn_free(c);
		
		return;
	}
	buf[rc] = '\n';
	printf("data received:%s\n", buf);
	printf("current tid is:%d\n", (int)pthread_self());
}









