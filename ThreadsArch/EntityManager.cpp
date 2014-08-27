#include "EntityManager.h"
#include <pthread.h>
#include <stdlib.h>

///////////////////////////event_queue_item////////////////
static pthread_mutex_t eqi_freelist_lock=PTHREAD_MUTEX_INITIALIZER;

static EQ_ITEM *eqi_freelist;
void eqi_free(EQ_ITEM *item)
{
	pthread_mutex_lock(&eqi_freelist_lock);
	item->next=eqi_freelist;
	eqi_freelist=item;
	pthread_mutex_unlock(&eqi_freelist_lock);
}

EQ_ITEM *eqi_new(void)
{
	EQ_ITEM *item=NULL;
	pthread_mutex_lock(&eqi_freelist_lock);
	if(eqi_freelist)
	{
		item=eqi_freelist;
		eqi_freelist=item->next;
	}
	pthread_mutex_unlock(&eqi_freelist_lock);

	if(NULL==item)
	{
		int i;
		item =(EQ_ITEM*) malloc(sizeof(EQ_ITEM)*ITEMS_PER_ALLOC);
		if(NULL ==item)
			return NULL;

		for(i=2;i<ITEMS_PER_ALLOC;i++)
			item[i-1].next=&item[i];
	
		pthread_mutex_lock(&eqi_freelist_lock);
		item[ITEMS_PER_ALLOC-1].next=eqi_freelist;
		eqi_freelist=&item[1];
		pthread_mutex_unlock(&eqi_freelist_lock);
	}
	return item;
}

///////////////////////////////conn//////////////////////////////////////////

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

void conn_free(conn *c) 
{
	if (c) 
	{
		free(c);	
	}
}