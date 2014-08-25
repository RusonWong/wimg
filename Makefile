CC	:= g++
CFLAGS	:= -levent -pthread -lmemcached -std=gnu++11 `pkg-config --cflags --libs protobuf` -I ./PB/
OBJECTS	:= main.cpp ThreadsMain.o EventQueue.o EventHandler.o \
 WorkerThreads.o EntityManager.o LocalStorage.o \
 FTProtocol.o MCConnector.o WPB.pb.o

wnode_server: $(OBJECTS)
	$(CC) $(OBJECTS) -o wnode_server $(CFLAGS)

ThreadsMain.o:ThreadsMain.cpp ThreadsMain.h 
	$(CC) ThreadsMain.cpp -c -std=gnu++11

EventQueue.o: EventQueue.cpp EventQueue.h 
	$(CC) EventQueue.cpp -c

EventHandler.o: EventHandler.cpp EventHandler.h LibeventThread.h  FTProtocol.o
	$(CC) EventHandler.cpp -c -std=gnu++11 -I ./PB/

WorkerThreads.o: WorkerThreads.cpp WorkerThreads.h
	$(CC) WorkerThreads.cpp -c -std=gnu++11

EntityManager.o: EntityManager.cpp EntityManager.h
	$(CC) EntityManager.cpp -c

LocalStorage.o: LocalStorage.h LocalStorage.cpp StorageBase.h Logger.h
	$(CC) LocalStorage.cpp -c

FTProtocol.o:FTProtocol.cpp FTProtocol.h 
	g++ FTProtocol.cpp -c -I ./PB/

MCConnector.o:MCConnector.cpp MCConnector.h
	g++ MCConnector.cpp -c -lmemcached -std=gnu++11

WPB.pb.o: ./PB/WPB.pb.h ./PB/WPB.pb.cc
	g++ ./PB/WPB.pb.cc -c `pkg-config --cflags --libs protobuf` -I ./PB/

clean:
	rm wnode_server *.o
