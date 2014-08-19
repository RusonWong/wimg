CC	:= g++
CFLAGS	:= -levent -pthread
OBJECTS	:= main.cpp EventQueue.o EventHandler.o WorkerThreads.o

tpm: $(OBJECTS)
	$(CC) $(OBJECTS) -o tpm $(CFLAGS)
EventQueue.o: EventQueue.cpp EventQueue.h
	$(CC) EventQueue.cpp -c
EventHandler.o: EventHandler.cpp EventHandler.h LibeventThread.h
	$(CC) EventHandler.cpp -c
WorkerThreads.o: WorkerThreads.cpp WorkerThreads.h
	$(CC) WorkerThreads.cpp -c

clean:
	rm tpm *.o
