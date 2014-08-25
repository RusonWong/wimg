#include <iostream>
#include <string>
#include <libmemcached/memcached.h>

using namespace std;


 int main(int argc,char *argv[])
 {  
    memcached_st *memc;
    memcached_return rc;
    memcached_server_st *server;
    time_t expiration;
    uint32_t  flags;
 
    memc = memcached_create(NULL);
    server = memcached_server_list_append(NULL,"localhost",11211,&rc);
    rc=memcached_server_push(memc,server);
    if(rc == MEMCACHED_SUCCESS)
    {
    	cout<<"connect server ok\n";
    }
    else
    {
    	cout<<"connect server failed\n";
    }
    memcached_server_list_free(server);
 
    string key = "key";
    string value = "value";
    size_t value_length = value.length();
    size_t key_length = key.length();
    cout<<"value_length:"<<value_length<<",key len:"<<key_length<<endl;
 
 
    //Save data
    rc=memcached_set(memc,key.c_str(),key.length(),value.c_str(),value.length(),0,0);
    if(rc==MEMCACHED_SUCCESS)
    {
        cout<<"Save data:"<<value<<" sucessful!"<<endl;
    }
 
     //Get data
    char* result = memcached_get(memc,key.c_str(),key_length,&value_length,&flags,&rc);
    if(rc == MEMCACHED_SUCCESS)
    {
        cout<<"Get value:"<<result<<" sucessful!"<<endl;
    }
    else if(rc == MEMCACHED_NOTFOUND)
    {
    	cout<<"get value failed, key not found\n";
    }
 
    //Delete data
    rc=memcached_delete(memc,key.c_str(),key_length,0);
    if(rc==MEMCACHED_SUCCESS)
    {
        cout<<"Delete key:"<<key<<" sucessful!"<<endl;
    }
 
    //free
    memcached_free(memc);
    return 0;
}