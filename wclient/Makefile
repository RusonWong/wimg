
commoncpp = $(wildcard ../common/*.cpp)
commonobj = $(commoncpp:.cpp=.o)

curcpp = $(wildcard *.cpp)
curobj = $(curcpp:.cpp=.o)

CC := g++
CFLAGS	:= -std=gnu++11 `pkg-config --cflags --libs protobuf` `pkg-config --cflags --libs MagickWand` -I../common/
OBJECTS	:= $(curobj) WPB.pb.o $(commonobj) 

wclient: $(OBJECTS)
	$(CC) $(OBJECTS) -o wclient $(CFLAGS)

WPB.pb.o: ../common/WPB.pb.h ../common/WPB.pb.cc
	g++ ../common/WPB.pb.cc -c `pkg-config --cflags --libs protobuf` -I ../common/

$(curobj):%.o:%.cpp
	g++ -c $< -o $@ $(CFLAGS)

$(commonobj):%.o:%.cpp
	g++ -c $< -o $@

clean:
	rm wclient *.o
	cd ../common && rm *.o
	
