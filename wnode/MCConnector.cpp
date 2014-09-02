#include "MCConnector.h"


#include <iostream>
#include <string>

using namespace std;

int MCConnector::init(string addr, int port)
{
    memcached_server_st *server;
    memcached_return rc;

    memc = memcached_create(NULL);
    server = memcached_server_list_append(NULL,addr.c_str(),port,&rc);
    rc=memcached_server_push(memc,server);
    memcached_server_list_free(server);

    if(rc == MEMCACHED_SUCCESS)
    {
        cout<<"connect memcached server ok\n";
        return 1;
    }
    else
    {
        cout<<"connect memcached server failed\n";
        return 0;
    }
}



int MCConnector::cache_get(char* key, size_t key_len, char* &value, size_t &value_len)
{
    size_t value_length_temp;
    uint32_t  flags;
    memcached_return rc;

    char* result = memcached_get(memc, key, key_len, &value_length_temp, &flags,&rc);

    if(rc == MEMCACHED_SUCCESS)
    {
        value_len = value_length_temp;
        value = result;
        return 1;
    }

    return 0;
}


int MCConnector::cache_set(char* key, size_t key_len, char* value, size_t value_len)
{
    cout<<"cache set begin\n";
    mc_ret rc = memcached_set(memc, key , key_len, value, value_len,EXPIRE_TIME,0);
    if(rc == MEMCACHED_SUCCESS)
    {
        cout<<"cache set OK\n";
        return 1;
    }
    cout<<"cache set failed\n";
    return 0;
}

//check cache exsit
int MCConnector::cache_exsit(char* key, size_t key_len)
{
    return false;
}