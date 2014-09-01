
main: main.cpp ConHash.o md5.o
	g++ main.cpp ConHash.o md5.o -o main


ConHash.o: ConHash.h ConHash.cpp md5.o
	g++ ConHash.cpp -c -I ../../common/

md5.o: ../../common/md5.h ../../common/md5.cpp
	g++ ../../common/md5.cpp -c -I ../../common/