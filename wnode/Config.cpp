#include "Config.h"

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

Config globalConfig;

void Config::load(string configPath)
{
	lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    if (luaL_loadfile(L, configPath.c_str()) || lua_pcall(L, 0, 0, 0))
    {
        lua_close(L);
        return;
    }

    lua_getglobal(L, "local_addr");
    if(lua_isstring(L, -1))
        this->localAddr = (string)lua_tostring(L, -1);
    lua_pop(L, 1);

    lua_getglobal(L, "port");
    if(lua_isnumber(L, -1))
       	this->port = (int)lua_tonumber(L, -1);
    lua_pop(L, 1);

    lua_getglobal(L, "master_addr");
    if(lua_isstring(L, -1))
        this->masterAddr = (string)lua_tostring(L, -1);
    lua_pop(L, 1);

    lua_getglobal(L, "master_port");
    if(lua_isnumber(L, -1))
       this->masterPort = (int)lua_tonumber(L, -1);
    lua_pop(L, 1);

    lua_getglobal(L, "threads_count");
    if(lua_isnumber(L, -1))
       this->threadsCount = (int)lua_tonumber(L, -1);
    lua_pop(L, 1);

    lua_getglobal(L, "memcached_addr");
    if(lua_isstring(L, -1))
        this->memAddr = (string)lua_tostring(L, -1);
    lua_pop(L, 1);

    lua_getglobal(L, "memcached_port");
    if(lua_isnumber(L, -1))
       this->memPort = (int)lua_tonumber(L, -1);
    lua_pop(L, 1);

    lua_close(L);
}