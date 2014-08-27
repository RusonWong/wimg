OBJECTS	:= FTPClient.cpp FTProtocol.o WPB.pb.o

ftpclient:$(OBJECTS)
	g++ $(OBJECTS) -o ftpclient `pkg-config --cflags --libs protobuf` -I ../Common/ -I ../../

WPB.pb.o: ../Common/WPB.pb.h ../Common/WPB.pb.cc
	g++ ../Common/WPB.pb.cc -c `pkg-config --cflags --libs protobuf` -I ../Common/

FTProtocol.o: ../Common/FTProtocol.cpp ../Common/FTProtocol.h
	g++ ../Common/FTProtocol.cpp -c  -I ../Common/



clean:
	rm ftpclient *.o