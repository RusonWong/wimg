OBJECTS	:= wclient.cpp FTProtocol.o WPB.pb.o md5.o

wclient:$(OBJECTS)
	g++ $(OBJECTS) -o wclient `pkg-config --cflags --libs protobuf` -I ../common/ -I ../../

WPB.pb.o: ../common/WPB.pb.h ../common/WPB.pb.cc
	g++ ../common/WPB.pb.cc -c `pkg-config --cflags --libs protobuf` -I ../common/

FTProtocol.o: ../common/FTProtocol.cpp ../common/FTProtocol.h
	g++ ../common/FTProtocol.cpp -c  -I ../common/ -I ../common/

md5.o:../common/md5.cpp ../common/md5.h
	g++ ../common/md5.cpp -c -I ../common/

clean:
	rm wclient *.o