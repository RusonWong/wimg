
#include<unistd.h> //getopt
#include<stdlib.h> //atoi
#include<event.h> //libevent
#include<stdio.h>
#include<pthread.h>
#include<string.h> //strerror
#include<errno.h>
#include<fcntl.h> //open

#include <assert.h>

#include"WorkerThreads.h"
#include "EntityManager.h"


#define LISTEN_PORT 9999
#define LISTEN_BACKLOG 32
#define MAX_LINE    256

//Globally Settings
struct Settings
{
	int num_threads;	
};
struct Settings settings;

//Globally Values
#define DATA_BUFFER_SIZE 2048
static struct event_base *main_base;					//main thread dispatch event_base
static int last_thread=-1;
WorkerThreads *workerThreads;

//Globally Functions
void readCommand(Settings settings){}

void thread_init(int nthreads)
{	
	workerThreads=new WorkerThreads(nthreads);

	workerThreads->initiate();
}

void dispatch_conn_new(int sfd)
{
	printf("dispatch_conn_new called\n");	
	EQ_ITEM *item=eqi_new();						
	int tid=(last_thread+1)%settings.num_threads;
	LIBEVENT_THREAD *thread=workerThreads->threads+tid;
	
	last_thread=tid;
	item->sfd=sfd;											//connected fd
	item->event_flags=EV_READ | EV_PERSIST;
	
	eq_push(thread->new_conn_queue,item);					//push conn to working thread
	int wc=write(thread->notify_send_fd," ",1);				//write 1 byte to notify thread
}

void base_event_handler(const int fd, const short which,void* arg)
{
	printf("base_event_handler called\n");
	//char buf[128];
	//int rc=read(fd,buf,sizeof(buf));
	//printf("%d\n",rc);
	//buf[rc]='\0';
	//printf("%s\n",buf);
	printf("listen fd is:%d\n",fd);
	struct sockaddr_in sin;
    socklen_t slen = sizeof(struct sockaddr);
    int sfd = accept(fd, (struct sockaddr *)&sin, &slen);
    printf("accept fd is %d\n", sfd);


	//int testfd=open("./testfile.txt",O_RDWR);
	//int pipefds[2];
	//pipe(pipefds);
	dispatch_conn_new(sfd);						//这里使用pipe来模拟memcached中外部连接后带来的通信fd，注意要想在libevent上监听fd，则不能使用regular file的fd，libevent不支持
}

int main(int argc, char **argv)
{
//	readCommand(settings);						//set threads counts
	int c;

	settings.num_threads=3;
	while(-1!=(c=getopt(argc,argv,"t:")))		//从命令行读取workerThread数
	{
		switch (c)
		{
		case 't':
			settings.num_threads=atoi(optarg);
			break;
		}
	}

	int ret;
    evutil_socket_t listener;
    listener = socket(AF_INET, SOCK_STREAM, 0);
    assert(listener > 0);
    evutil_make_listen_socket_reuseable(listener);

    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(LISTEN_PORT);

    if (bind(listener, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("bind");
        return 1;
    }

    if (listen(listener, LISTEN_BACKLOG) < 0) {
        perror("listen");
        return 1;
    }

    printf ("Listening...\n");

    evutil_make_socket_nonblocking(listener);
	
	main_base=event_init();						//主线程的监听外部连接（这里监听标准输入），memcached则借助自定义的协议，接收来自Unix域/tcp/udp的客户端请求。
	struct event inputEvent;
	event_set(&inputEvent,listener,EV_READ|EV_PERSIST,base_event_handler,NULL);	//一旦有事件触发，则委托给base_event_handler处理
	event_base_set(main_base,&inputEvent);
	event_add(&inputEvent,0);
	

	conn_init();

	thread_init(settings.num_threads);				//WorkerThread初始化，详细见workerThreads->initiate();

	event_base_loop(main_base,0);					//开始监听主线程的注册事件
}
