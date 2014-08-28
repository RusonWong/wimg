#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <event.h>

#define ITEMS_PER_ALLOC 64


/////////////event_queue_item//////////////////////
typedef struct event_queue_item EQ_ITEM;
struct event_queue_item
{
	int sfd;
	//enum conn_states init_state;
	int event_flags;
	int read_buffer_size;
	EQ_ITEM *next;
};

//functions
void eqi_free(EQ_ITEM *item);
EQ_ITEM  *eqi_new(void);



///////////////conn//////////////
typedef struct conn conn;
struct conn
{
	int sfd;
	struct event event;
};

void conn_init();
conn *conn_from_freelist();
bool conn_add_to_freelist(conn *c);
void conn_free(conn *c);

#endif


