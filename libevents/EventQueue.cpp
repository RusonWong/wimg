
#include "EventQueue.h"
#include<stdlib.h>
#include<stdio.h>

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
