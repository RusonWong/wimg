#ifndef IMAGE_UTIL
#define IMAGE_UTIL


#include <stdio.h>
#include <stdlib.h>


struct IMG_PROCCESS_CONFIG
{
	int out_width;
	int out_height;
	bool keep_proportion;
};


int  resize_image(char* in_buff, size_t in_len, char* &out_buff, size_t &out_len, IMG_PROCCESS_CONFIG *config, bool remove_exif = false);



#endif
