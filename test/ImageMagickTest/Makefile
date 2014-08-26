
main:main.cpp ImageUtil.o
	g++ -o main main.cpp `pkg-config --cflags --libs MagickWand`

ImageUtil.o:ImageUtil.h ImageUtil.cpp
	g++ ImageUtil.cpp -c `pkg-config --cflags --libs MagickWand`