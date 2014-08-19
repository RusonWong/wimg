#include "EventHandler.h"
#include <unistd.h>
#include <pthread.h>


static pthread_mutex_t conn_lock=PTHREAD_MUTEX_INITIALIZER;
static int freecurr;
static int freetotal;



static conn **freeconns;

void conn_init(void) {
	freetotal = 200;
	freecurr = 0;
	if ((freeconns =(conn**)calloc(freetotal, sizeof(conn *))) == NULL) {
		fprintf(stderr, "Failed to allocate connection structures\n");
	}
	return;
}


//real handler
void event_handler(const int fd,const short which,void *arg)
{
	char buf[3];
	int rc=read(fd,buf,3);
	printf("data lenth is:%d\n",rc);
	//buf[rc] = '\n';
	printf("data received:%s", buf);
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

conn *conn_from_freelist()
{
	conn *c;
	pthread_mutex_lock(&conn_lock);

	if(freecurr>0)
		c=freeconns[--freecurr];
	else
		c=NULL;

	pthread_mutex_unlock(&conn_lock);
}

bool conn_add_to_freelist(conn *c) 
{
	bool ret = true;
	pthread_mutex_lock(&conn_lock);

	if (freecurr < freetotal) 
	{
		freeconns[freecurr++] = c;
		ret = false;
	}
	else 
	{
		//try to enlarge free connections array 
		size_t newsize = freetotal * 2;
		conn **new_freeconns = (conn**)realloc(freeconns, sizeof(conn *) * newsize);
		if (new_freeconns) 
		{				
			freetotal = newsize;
			freeconns = new_freeconns;
			freeconns[freecurr++] = c;		
			ret = false;
		}
	}

	pthread_mutex_unlock(&conn_lock);
	return ret;
}

void conn_free(conn *c) {
	if (c) 
	{
		free(c);	
	}
}


