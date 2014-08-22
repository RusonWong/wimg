OBJECTS	:= FTPClient.cpp FTProtocol.o

ftpclient:$(OBJECTS)
	g++ $(OBJECTS) -o ftpclient

FTProtocol.o:FTProtocol.cpp FTProtocol.h
	g++ FTProtocol.cpp -c

clean:
	rm ftpclient *.o