#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H
#include <pthread.h>
#include "EntityManager.h"

struct event_queue
{
	EQ_ITEM *head;
	EQ_ITEM *tail;
	pthread_mutex_t lock;
	pthread_cond_t cond;
};

EQ_ITEM *eq_pop(event_queue *eq);
void eq_init(event_queue *eq);
void eq_push(event_queue *eq,EQ_ITEM *item);

#endif
