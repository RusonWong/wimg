#ifndef LIBEVENT_THREAD_T
#define LIBEVENT_THREAD_T
#include "EventQueue.h"
#include <event.h>
#include "MCConnector.h"


struct LIBEVENT_THREAD
{
	pthread_t thread_id;

	struct event_base *base;
	struct event notify_event;
	
	int notify_receive_fd;
	int notify_send_fd;
	
	event_queue *new_conn_queue;

	MCConnector mcc;
	MCConnector bdbc;
};

#endif
