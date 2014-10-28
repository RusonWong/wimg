#include "ThreadsMain.h"
#include "FTProtocol.h"
#include "WPB.pb.h"
#include <string>
#include "Config.h"
#include "MCConnector.h"

using namespace std;

extern Config globalConfig;
extern MCConnector global_memcached_mcc;
extern MCConnector global_beansdb_mcc;

void init()
{
    globalConfig.load("./conf/conf.lua");
    cout<<globalConfig.localAddr<<"="<<globalConfig.port<<"="<<globalConfig.masterAddr<<"="<<globalConfig.masterPort<<endl;


    global_memcached_mcc.init(globalConfig.memAddr, globalConfig.memPort, true);
    //initial beansdb connector
    global_beansdb_mcc.init(globalConfig.beansdbAddr, globalConfig.beansdbPort, false);

}

int register_to_master()
{
    printf("register_to_master start\n");
    char hname[128];
    struct hostent *hent;
    int i;

    gethostname(hname, sizeof(hname));
    hent = gethostbyname(hname);

   // printf("hostname: %s/naddress list: ", hent->h_name);
    
    char* ipstr = inet_ntoa(*(struct in_addr*)(hent->h_addr_list[0]));
    string hostaddr(ipstr);
    
    int cLen = 0;
    struct sockaddr_in cli;
    
    cli.sin_family = AF_INET;
    cli.sin_port = htons(globalConfig.masterPort);
    cli.sin_addr.s_addr = inet_addr(globalConfig.masterAddr.c_str());
    
    const int sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock < 0)
    {
        printf("socket() failure!\n");
        return 0; 
    }
    
    if(connect(sock, (struct sockaddr*)&cli, sizeof(cli)) < 0)
    {
        printf("connect() failure!\n");
        return 0;
    }

    //send method
    cLen = w_send(sock, "3", 1);
    if((cLen < 0)||(cLen == 0))
    {
        printf("send() failure!\n");
        return 0;
    }

    //send body
    NodeInfo req;
    req.set_nodeaddr(globalConfig.localAddr);
    req.set_nodeport(globalConfig.port);

    w_send_pb(sock, &req);

   	close(sock);
    printf("register_to_master done\n");
   	return 1;
}

int unregister_from_master()
{
    printf("unregister_from_master start\n");
    char hname[128];
    struct hostent *hent;
    int i;

    gethostname(hname, sizeof(hname));
    hent = gethostbyname(hname);

   // printf("hostname: %s/naddress list: ", hent->h_name);
    
    char* ipstr = inet_ntoa(*(struct in_addr*)(hent->h_addr_list[0]));
    string hostaddr(ipstr);
    
    int cLen = 0;
    struct sockaddr_in cli;
    
    cli.sin_family = AF_INET;
    cli.sin_port = htons(globalConfig.masterPort);
    cli.sin_addr.s_addr = inet_addr(globalConfig.masterAddr.c_str());
    
    const int sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock < 0)
    {
        printf("socket() failure!\n");
        return 0; 
    }
    
    if(connect(sock, (struct sockaddr*)&cli, sizeof(cli)) < 0)
    {
        printf("connect() failure!\n");
        return 0;
    }

    //send method
    cLen = w_send(sock, "4", 1);
    if((cLen < 0)||(cLen == 0))
    {
        printf("send() failure!\n");
        return 0;
    }

    //send body
    NodeInfo req;
    req.set_nodeaddr(globalConfig.localAddr);
    req.set_nodeport(globalConfig.port);

    w_send_pb(sock, &req);

    close(sock);
    printf("unregister_from_master done\n");
    return 1;
}

int main(int argc, char **argv)
{
    init();
    register_to_master();
    start_server(globalConfig.threadsCount);
    unregister_from_master();
    printf("wnode exit\n");
}
