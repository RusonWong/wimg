CC	:= g++
CFLAGS	:= -levent -pthread
OBJECTS	:= main.cpp ThreadsMain.o EventQueue.o EventHandler.o WorkerThreads.o EntityManager.o

VPATH = ../

tpm: $(OBJECTS)
	$(CC) $(OBJECTS) -o wnode_server $(CFLAGS)

ThreadsMain.o:ThreadsMain.cpp ThreadsMain.h 
	$(CC) ThreadsMain.cpp -c

EventQueue.o: EventQueue.cpp EventQueue.h 
	$(CC) EventQueue.cpp -c

EventHandler.o: EventHandler.cpp EventHandler.h LibeventThread.h 
	$(CC) EventHandler.cpp -c

WorkerThreads.o: WorkerThreads.cpp WorkerThreads.h
	$(CC) WorkerThreads.cpp -c

EntityManager.o: EntityManager.cpp EntityManager.h
	$(CC) EntityManager.cpp -c

clean:
	rm wnode_server *.o
