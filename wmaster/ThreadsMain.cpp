#include "ThreadsMain.h"

#include <stdlib.h> //atoi
#include <event.h> //libevent
#include <stdio.h>
#include <pthread.h>
#include <string.h> //strerror
#include <errno.h>
#include <fcntl.h> //open
#include "Config.h"
#include <assert.h>

#include "EventHandler.h"


extern Config globalConfig;

#define LISTEN_BACKLOG 32


static struct event_base *main_base;
static int last_thread = -1;
static int total_threads = 1;
WorkerThreads *workerThreads;
static pthread_mutex_t thread_lock=PTHREAD_MUTEX_INITIALIZER;

void thread_init(int nthreads);
void base_event_handler(const int fd, const short which,void* arg);
void dispatch_conn_new(int sfd);

void thread_init(int nthreads)
{	
	workerThreads=new WorkerThreads(nthreads);
	workerThreads->initiate();
}

void dispatch_conn_new(int sfd)
{
	printf("dispatch_conn_new called\n");	
	
	//pthread_mutex_lock(&thread_lock);
	EQ_ITEM *item=eqi_new();						
	int tid=(last_thread+1)%total_threads;
	LIBEVENT_THREAD *thread=workerThreads->threads+tid;
	
	last_thread=tid;
	item->sfd=sfd;											//connected fd
	item->event_flags=EV_READ | EV_PERSIST;
	//pthread_mutex_unlock(&thread_lock);

	eq_push(thread->new_conn_queue,item);					//push conn to working thread
	int wc=write(thread->notify_send_fd," ",1);				//write 1 byte to notify thread
}

void base_event_handler(const int fd, const short which,void* arg)
{
	printf("base_event_handler called\n");
	printf("listen fd is:%d\n",fd);
	struct sockaddr_in sin;
    socklen_t slen = sizeof(struct sockaddr);
    int sfd = accept(fd, (struct sockaddr *)&sin, &slen);
    printf("accept fd is %d\n", sfd);
	

    if(globalConfig.use_single_thread == 1)
		single_thread_event_handler(sfd, which);
	else
		dispatch_conn_new(sfd);
}

int start_server(int nThreads)
{
	total_threads = nThreads;

	int ret;
    evutil_socket_t listener;
    listener = socket(AF_INET, SOCK_STREAM, 0);
    assert(listener > 0);
    evutil_make_listen_socket_reuseable(listener);

    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(globalConfig.masterPort);

    if (bind(listener, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("bind");
        return 1;
    }

    if (listen(listener, LISTEN_BACKLOG) < 0) {
        perror("listen");
        return 1;
    }

    printf ("Listening on port %d\n", globalConfig.masterPort);

    evutil_make_socket_nonblocking(listener);
	
	main_base = event_init();						
	struct event inputEvent;
	event_set(&inputEvent,listener,EV_READ|EV_PERSIST,base_event_handler,NULL);	
	event_base_set(main_base,&inputEvent);
	event_add(&inputEvent,0);
	
	conn_init();

	thread_init(total_threads);

	event_base_loop(main_base,0);
}

