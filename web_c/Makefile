web_main:web_main.cpp util.o
	g++ web_main.cpp util.o \
	-o web_main -levhtp \
	-levent -rdynamic /usr/local/lib/libevent.so \
	/usr/local/lib/libevent_pthreads.so /usr/local/lib/libevent_openssl.so \
	/usr/local/lib/libssl.so /usr/local/lib/libcrypto.so -lpthread \
	-ldl -lrt -Wl,-rpath,/usr/local/lib

util.o: util.cpp util.h
	g++ util.cpp -c
