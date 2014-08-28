CC	:= g++
CFLAGS	:= -levent -pthread -lmemcached -std=gnu++11 `pkg-config --cflags --libs protobuf` `pkg-config --cflags --libs MagickWand` -I ../common/ 
OBJECTS	:= main.cpp ThreadsMain.o EventQueue.o EventHandler.o \
 WorkerThreads.o EntityManager.o LocalStorage.o \
 FTProtocol.o MCConnector.o ImageUtil.o WPB.pb.o md5.o

wnode_server: $(OBJECTS)
	$(CC) $(OBJECTS) -o wnode_server $(CFLAGS)

ThreadsMain.o:ThreadsMain.cpp ThreadsMain.h 
	$(CC) ThreadsMain.cpp -c -std=gnu++11

EventQueue.o: EventQueue.cpp EventQueue.h 
	$(CC) EventQueue.cpp -c

EventHandler.o: EventHandler.cpp EventHandler.h LibeventThread.h  FTProtocol.o ImageUtil.o md5.o
	$(CC) EventHandler.cpp -c -std=gnu++11 -I ../common/

WorkerThreads.o: WorkerThreads.cpp WorkerThreads.h
	$(CC) WorkerThreads.cpp -c -std=gnu++11

EntityManager.o: EntityManager.cpp EntityManager.h
	$(CC) EntityManager.cpp -c

LocalStorage.o: LocalStorage.h LocalStorage.cpp StorageBase.h Logger.h
	$(CC) LocalStorage.cpp -c

FTProtocol.o:../common/FTProtocol.cpp ../common/FTProtocol.h 
	g++ ../common/FTProtocol.cpp -c -I ../common/

MCConnector.o:MCConnector.cpp MCConnector.h
	g++ MCConnector.cpp -c -lmemcached -std=gnu++11

WPB.pb.o: ../common/WPB.pb.h ../common/WPB.pb.cc
	g++ ../common/WPB.pb.cc -c `pkg-config --cflags --libs protobuf` -I ../common/

ImageUtil.o:ImageUtil.h ImageUtil.cpp
	g++ ImageUtil.cpp -c `pkg-config --cflags --libs MagickWand`

md5.o:../common/md5.cpp ../common/md5.h
	g++ ../common/md5.cpp -c -I ../common/

clean:
	rm wnode_server *.o
