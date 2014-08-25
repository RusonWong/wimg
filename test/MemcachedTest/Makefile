

wcache:main.cpp MCConnector.o
	g++ -o wcache main.cpp MCConnector.o -lmemcached -std=c++0x -Wall

MCConnector.o:MCConnector.h MCConnector.cpp 
	g++ MCConnector.cpp -c -lmemcached -std=c++0x -Wall

clean:
	rm wcache *.o