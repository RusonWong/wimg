all:
	cd wnode && make
	cd wmaster && make
	cd wclient && make

clean:
	cd wnode && make clean
	cd wmaster && make clean
	cd wclient && make clean