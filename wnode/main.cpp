#include "ThreadsMain.h"
#include "FTProtocol.h"
#include "WPB.pb.h"
#include <string>


#define MASTER_ADDR "127.0.0.1"
#define MASTER_PORT 8888


using namespace std;


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
    cli.sin_port = htons(MASTER_PORT);
    cli.sin_addr.s_addr = inet_addr(MASTER_ADDR);
    
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
    req.set_nodeaddr(hostaddr);
    req.set_nodeport(9999);

    w_send_pb(sock, &req);

   	close(sock);
    printf("register_to_master done\n");
   	return 1;
}

int main(int argc, char **argv)
{
  register_to_master();
	start_server(10);
	
}
