
main:main.cpp
	g++ -o main main.cpp `pkg-config --cflags --libs MagickWand` 

ImageUtil.o:ImageUtil.h ImageUtil.cpp
	g++ ImageUtil.cpp -c `pkg-config --cflags --libs MagickWand`


clean:
	rm main resize.jpg