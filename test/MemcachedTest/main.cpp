#include <iostream>
#include <string>
#include "MCConnector.h"

using namespace std;


 int main(int argc,char *argv[])
 {  
    MCConnector mcc;
    mcc.init();

    int set_rt = mcc.cache_set("name", 4, "wangchun", 8);
    cout<<"set result:"<< set_rt<<endl;
    char* v;
    size_t v_len;
    int get_rt = mcc.cache_get("name",(size_t)4,v,v_len);
    cout<<"get rt is:"<<get_rt<<endl;
    cout<<v<<endl;
    return 0;
}