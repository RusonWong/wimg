CC	:= g++
CFLAGS	:= -levent -pthread `pkg-config --cflags --libs protobuf` -I ../common/
OBJECTS	:= main.cpp ThreadsMain.o EventQueue.o EventHandler.o WorkerThreads.o EntityManager.o WPB.pb.o FTProtocol.o WNodeManager.o

VPATH = ../

wmaster: $(OBJECTS)
	$(CC) $(OBJECTS) -o wmaster $(CFLAGS)

ThreadsMain.o:ThreadsMain.cpp ThreadsMain.h 
	$(CC) ThreadsMain.cpp -c

EventQueue.o: EventQueue.cpp EventQueue.h 
	$(CC) EventQueue.cpp -c

EventHandler.o: EventHandler.cpp EventHandler.h LibeventThread.h 
	$(CC) EventHandler.cpp -c -I ../common/

WorkerThreads.o: WorkerThreads.cpp WorkerThreads.h
	$(CC) WorkerThreads.cpp -c

EntityManager.o: EntityManager.cpp EntityManager.h
	$(CC) EntityManager.cpp -c

FTProtocol.o:../common/FTProtocol.cpp ../common/FTProtocol.h 
	g++ ../common/FTProtocol.cpp -c -I ../common/

WPB.pb.o: ../common/WPB.pb.h ../common/WPB.pb.cc
	g++ ../common/WPB.pb.cc -c `pkg-config --cflags --libs protobuf` -I ../common/

WNodeManager.o: WNodeManager.cpp WNodeManager.h
	g++ WNodeManager.cpp -c

clean:
	rm wmaster *.o
