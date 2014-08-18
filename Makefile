CC := g++
OBJECTS := main.cpp LocalStorage.o

main: $(OBJECTS)
	$(CC) $(OBJECTS) -o main
	
LocalStorage.o: LocalStorage.h LocalStorage.cpp StorageBase.h
	$(CC) LocalStorage.cpp -c


clean:
	rm main *.o