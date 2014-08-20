#include "WorkerThreads.h"
#include "EntityManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


/*
	WorkerThreads::WorkerThreads(int threadCount=1):nthreads(threadCount),threads(NULL)
	{
		init_count=0;
		pthread_mutex_init(&init_lock,NULL);
		pthread_cond_init(&init_cond,NULL);
	}
*/

void WorkerThreads::initiate()
{
	int i;

	threads=(LIBEVENT_THREAD*)calloc(nthreads,sizeof(LIBEVENT_THREAD));		//LIBEVENT_THREAD,加入libevent元素的thread结构 “数组”
	if(!threads)
	{
		perror("can't allocate thread des");
		exit(1);
	}

	for(i=0;i<nthreads;i++)													//设置thread和thread中的libevent所需属性
	{
		int fds[2];
		if(pipe(fds))														//thread和主线程的通信pipe
		{
			perror("can't create notify pipe");
			exit(1);
		}

		threads[i].notify_receive_fd=fds[0];
		threads[i].notify_send_fd=fds[1];

		setup_event_thread(&threads[i]);									//设置thread和thread中的libevent所需属性
	}

	for(i=0;i<nthreads;i++)
	{
		create_worker(worker_libevent,&threads[i]);							//启动thread
	}

	pthread_mutex_lock(&init_lock);
	while( init_count < nthreads)
	{
		pthread_cond_wait(&init_cond,&init_lock);
	}
	pthread_mutex_unlock(&init_lock);

	printf("threads start working\n");
}

void WorkerThreads::setup_event_thread(LIBEVENT_THREAD *me)
{
	me->base=event_init();//every thread has its own event_base
		
	if(!me->base)
	{
		fprintf(stderr,"can't allocate event base\n");
		exit(1);
	}

	event_set(&me->notify_event,me->notify_receive_fd,						//设置 监听事件 和 处理函数
		EV_READ|EV_PERSIST, thread_libevent_process,me);	
	event_base_set(me->base,&me->notify_event);

	if(event_add(&me->notify_event,0)==-1)
	{
		fprintf(stderr,"can't monitor libevent notify pipe\n");
		exit(1);
	}

	//why initiate conn_queue here?
	me->new_conn_queue=(event_queue*)malloc(sizeof(struct event_queue));		//内部的conn_queue
	if(me->new_conn_queue==NULL)
	{
		perror("Failed to allocate memory for connection queue");
		exit(EXIT_FAILURE);
	}

	eq_init(me->new_conn_queue);
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

void thread_libevent_process(int fd,short which,void *arg)					//处理函数，即当主线程通知workerThread时，主线程会插入一个item到某个thread的queue中，queue是一个工具类
																				//workerThread将item pop出来并封装为conn，封装期间就建立了和item所指向的对象的联系，也使用libevent完成
{
	printf("thread_libevent_process called\n");
	LIBEVENT_THREAD *me=(LIBEVENT_THREAD*)arg;
	EQ_ITEM *item;

	char buf[1];

	if(read(fd,buf,1)!=1)
			fprintf(stderr,"can't read from libevent pipe\n");

	item=eq_pop(me->new_conn_queue);
	printf("item fd is:%d\n",item->sfd);
	if(NULL != item)
	{
		handle_connection(item->sfd, me->base);
		eqi_free(item);
	}
}
	
void WorkerThreads::create_worker(void *(*func)(void*),void *arg)
{
	pthread_t thread;
	pthread_attr_t attr;
	int ret;

	pthread_attr_init(&attr);

	if((ret=pthread_create(&thread,&attr,func,arg))!=0)				
	{
		fprintf(stderr,"can't create thread: %s\n",strerror(ret));
		exit(1);
	}
}
	
void* worker_libevent(void *arg)
{
	LIBEVENT_THREAD *me = (LIBEVENT_THREAD*)arg;
	pthread_mutex_lock(&init_lock);
	init_count++;
	pthread_cond_signal(&init_cond);
	pthread_mutex_unlock(&init_lock);
	printf("thread %d is working\n",(int)pthread_self() );
	event_base_loop(me->base,0);
	return NULL;
}

	

	


