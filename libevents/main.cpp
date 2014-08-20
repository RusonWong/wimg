
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
	dispatch_conn_new(sfd);						//����ʹ��pipe��ģ��memcached���ⲿ���Ӻ������ͨ��fd��ע��Ҫ����libevent�ϼ���fd������ʹ��regular file��fd��libevent��֧��
}

int main(int argc, char **argv)
{
//	readCommand(settings);						//set threads counts
	int c;

	settings.num_threads=3;
	while(-1!=(c=getopt(argc,argv,"t:")))		//�������ж�ȡworkerThread��
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
	
	main_base=event_init();						//���̵߳ļ����ⲿ���ӣ����������׼���룩��memcached������Զ����Э�飬��������Unix��/tcp/udp�Ŀͻ�������
	struct event inputEvent;
	event_set(&inputEvent,listener,EV_READ|EV_PERSIST,base_event_handler,NULL);	//һ�����¼���������ί�и�base_event_handler����
	event_base_set(main_base,&inputEvent);
	event_add(&inputEvent,0);
	

	conn_init();

	thread_init(settings.num_threads);				//WorkerThread��ʼ������ϸ��workerThreads->initiate();

	event_base_loop(main_base,0);					//��ʼ�������̵߳�ע���¼�
}
