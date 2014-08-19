#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H
#include <pthread.h>

#define ITEMS_PER_ALLOC 64

/*
enum conn_states
{
	conn_listening,
	conn_new_cmd,
	conn_waiting,
	conn_read,
	conn_parse_cmd,
	conn_write,
	conn_nread,
	conn_swallow,
	conn_closing,
	conn_mwrite,
	conn_max_state
};

enum network_transport
{
	local_transport,
	tcp_transport,
	udp_transport
};
*/

typedef struct event_queue_item EQ_ITEM;
struct event_queue_item
{
	int sfd;
	//enum conn_states init_state;
	int event_flags;
	int read_buffer_size;
	EQ_ITEM *next;
};



struct event_queue
{
	EQ_ITEM *head;
	EQ_ITEM *tail;
	pthread_mutex_t lock;
	pthread_cond_t cond;
};

EQ_ITEM *eq_pop(event_queue *eq);
void eqi_free(EQ_ITEM *item);
void eq_init(event_queue *eq);
EQ_ITEM  *eqi_new(void);
void eq_push(event_queue *eq,EQ_ITEM *item);

#endif
