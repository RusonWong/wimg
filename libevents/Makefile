CC	:= g++
CFLAGS	:= -levent -pthread
OBJECTS	:= main.cpp EventQueue.o EventHandler.o WorkerThreads.o EntityManager.o

tpm: $(OBJECTS)
	$(CC) $(OBJECTS) -o tpm $(CFLAGS)

EventQueue.o: EventQueue.cpp EventQueue.h EntityManager.o
	$(CC) EventQueue.cpp -c

EventHandler.o: EventHandler.cpp EventHandler.h LibeventThread.h EntityManager.o
	$(CC) EventHandler.cpp -c

WorkerThreads.o: WorkerThreads.cpp WorkerThreads.h EntityManager.o
	$(CC) WorkerThreads.cpp -c

EntityManager.o: EntityManager.cpp EntityManager.h
	$(CC) EntityManager.cpp -c

clean:
	rm tpm *.o
