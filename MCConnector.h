#ifndef MC_CONNECTOR_H
#define MC_CONNECTOR_H

#include <libmemcached/memcached.h>

typedef memcached_return mc_ret;
#define EXPIRE_TIME 60*60*48 //2 DAYS


class MCConnector
{
private:
	memcached_st *memc;

public:
	MCConnector(){};
	~MCConnector(){
		if(memc)
		{
			delete memc;
		}
	};

	int init();


	int cache_get(char* key, size_t key_len, char* &value, size_t &value_len);
	int cache_set(char* key, size_t key_len, char* value, size_t value_len);
};


#endif