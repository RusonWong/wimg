
#include "EventQueue.h"
#include<stdlib.h>
#include<stdio.h>


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

void eq_init(event_queue *eq)
{
	pthread_mutex_init(&eq->lock,NULL);
	pthread_cond_init(&eq->cond,NULL);
	eq->head=NULL;
	eq->tail=NULL;
}

EQ_ITEM *eq_pop(event_queue *eq)
{
	EQ_ITEM *item;
	pthread_mutex_lock(&eq->lock);
	item=eq->head;
	if(NULL!=item)
	{
		eq->head=item->next;
		if(NULL==eq->head)
			eq->tail=NULL;
	}
	pthread_mutex_unlock(&eq->lock);
	return item;
}

void eq_push(event_queue *eq,EQ_ITEM *item)
{
	item->next=NULL;
	pthread_mutex_lock(&eq->lock);
	if(NULL==eq->tail)
	{
		eq->head=item;
	}
	else
		eq->tail->next=item;
	eq->tail=item;
	pthread_cond_signal(&eq->cond);
	pthread_mutex_unlock(&eq->lock);

}
