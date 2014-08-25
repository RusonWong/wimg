OBJECTS	:= FTPClient.cpp FTProtocol.o WPB.pb.o

ftpclient:$(OBJECTS)
	g++ $(OBJECTS) -o ftpclient `pkg-config --cflags --libs protobuf` -I ../../PB/ -I ../../

WPB.pb.o: ../../PB/WPB.pb.h ../../PB/WPB.pb.cc
	g++ ../../PB/WPB.pb.cc -c `pkg-config --cflags --libs protobuf` -I ../../PB/

FTProtocol.o: ../../FTProtocol.cpp ../../FTProtocol.h
	g++ ../../FTProtocol.cpp -c -I ../../ -I ../../PB/



clean:
	rm ftpclient *.o