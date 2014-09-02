
commoncpp = $(wildcard ../common/*.cpp)
commonobj = $(commoncpp:.cpp=.o)

curcpp = $(wildcard *.cpp)
curobj = $(curcpp:.cpp=.o)

luacpp = $(wildcard ../lua/*.c)
luaobj = $(luacpp:.c=.o)

CC := g++
CFLAGS	:= -std=c++0x `pkg-config --cflags --libs protobuf` `pkg-config --cflags --libs MagickWand` -I../common/ -I../lua/
OBJECTS	:= $(curobj) WPB.pb.o $(commonobj)  $(luaobj)

wclient: $(OBJECTS)
	$(CC) $(OBJECTS) -o wclient $(CFLAGS)

WPB.pb.o: ../common/WPB.pb.h ../common/WPB.pb.cc
	g++ ../common/WPB.pb.cc -c `pkg-config --cflags --libs protobuf` -I ../common/

$(curobj):%.o:%.cpp
	g++ -c $< -o $@ $(CFLAGS)

$(commonobj):%.o:%.cpp
	g++ -c $< -o $@

$(luaobj):%.o:%.c
	g++ -c $< -o $@

clean:
	rm wclient *.o
	cd ../common && rm *.o
	
