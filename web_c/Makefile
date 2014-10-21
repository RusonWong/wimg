
commoncpp = $(wildcard ../common/*.cpp)
commonobj = $(commoncpp:.cpp=.o)

curcpp = $(wildcard *.cpp)
curobj = $(curcpp:.cpp=.o)

luacpp = $(wildcard ../lua/*.c)
luaobj = $(luacpp:.c=.o)

wclientcpp = $(wildcard wclient/*.cpp)
wclientobj = $(wclientcpp:.cpp=.o)

CC := g++
CFLAGS	:= -std=c++0x `pkg-config --cflags --libs protobuf` `pkg-config --cflags --libs MagickWand` -I../common/ -I../lua/ -Iwclient/ -levhtp \
	-levent -rdynamic /usr/local/lib/libevent.so \
	/usr/local/lib/libevent_pthreads.so /usr/local/lib/libevent_openssl.so \
	/usr/local/lib/libssl.so /usr/local/lib/libcrypto.so -lpthread \
	-ldl -lrt -Wl,-rpath,/usr/local/lib
OBJECTS	:= $(curobj) WPB.pb.o $(commonobj)  $(luaobj) $(wclientobj)

main: $(OBJECTS)
	$(CC) $(OBJECTS) -o web_main $(CFLAGS)

WPB.pb.o: ../common/WPB.pb.h ../common/WPB.pb.cc
	g++ ../common/WPB.pb.cc -c `pkg-config --cflags --libs protobuf` -I ../common/

$(curobj):%.o:%.cpp
	g++ -c $< -o $@ $(CFLAGS)

$(commonobj):%.o:%.cpp
	g++ -c $< -o $@

$(luaobj):%.o:%.c
	g++ -c $< -o $@

$(wclientobj):%.o:%.cpp
	g++ -c $< -o $@ -std=c++0x `pkg-config --cflags --libs protobuf` -I../common/ -I../lua/

clean:
	rm web_main *.o
	cd ../common && rm *.o
