#include "ThreadsMain.h"
#include "Config.h"

extern Config globalConfig;

void init_config()
{
	globalConfig.load("./conf/conf.lua");
}

int main(int argc, char **argv)
{
	init_config();
	start_server(globalConfig.threadsCount);
}
