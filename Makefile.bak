CC := g++
OBJECTS := main.cpp LocalStorage.o

main: $(OBJECTS)
	$(CC) $(OBJECTS) -o main
	
LocalStorage.o: LocalStorage.h LocalStorage.cpp StorageBase.h Logger.h
	$(CC) LocalStorage.cpp -c


clean:
	rm main *.o