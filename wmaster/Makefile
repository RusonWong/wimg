luacpp = $(wildcard ../lua/*.c)
luaobj = $(luacpp:.c=.o)

commoncpp = $(wildcard ../common/*.cpp)
commonobj = $(commoncpp:.cpp=.o)

curcpp = $(wildcard *.cpp)
curobj = $(curcpp:.cpp=.o)

CC := g++
CFLAGS	:= -levent -pthread -lmemcached -std=c++0x `pkg-config --cflags --libs protobuf` `pkg-config --cflags --libs MagickWand` -I../common/ -I../lua/
OBJECTS	:= $(curobj) WPB.pb.o $(luaobj) $(commonobj) 

wmaster: $(OBJECTS)
	$(CC) $(OBJECTS) -o wmaster $(CFLAGS)

WPB.pb.o: ../common/WPB.pb.h ../common/WPB.pb.cc
	g++ ../common/WPB.pb.cc -c `pkg-config --cflags --libs protobuf` -I ../common/

$(curobj):%.o:%.cpp
	g++ -c $< -o $@ $(CFLAGS)

$(luaobj):%.o:%.c
	g++ -c $< -o $@

$(commonobj):%.o:%.cpp
	g++ -c $< -o $@

clean:
	rm wmaster *.o
	cd ../common && rm *.o
	cd ../lua    && rm *.o
	
