luacpp = $(wildcard ../lua/*.c)
luaobj = $(luacpp:.c=.o)

commoncpp = $(wildcard ../common/*.cpp)
commonobj = $(commoncpp:.cpp=.o)

curcpp = $(wildcard *.cpp)
curobj = $(curcpp:.cpp=.o)

CC := g++
CFLAGS	:= -levent -pthread -lmemcached -std=c++0x `pkg-config --cflags --libs protobuf` `pkg-config --cflags --libs MagickWand` -I../common/ -I../lua/
OBJECTS	:= $(curobj) WPB.pb.o $(luaobj) $(commonobj) 

wnode_server: $(OBJECTS)
	$(CC) $(OBJECTS) -o wnode_server $(CFLAGS)

WPB.pb.o: ../common/WPB.pb.h ../common/WPB.pb.cc
	g++ ../common/WPB.pb.cc -c `pkg-config --cflags --libs protobuf` -I ../common/

$(curobj):%.o:%.cpp
	g++ -c $< -o $@ $(CFLAGS)

$(luaobj):%.o:%.c
	g++ -c $< -o $@

$(commonobj):%.o:%.cpp
	g++ -c $< -o $@

clean:
	rm wnode_server *.o
	cd ../common && rm *.o
	cd ../lua    && rm *.o
	
