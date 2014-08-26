#include "ImageUtil.h"
#include <wand/MagickWand.h>

int  resize_image(char* in_buff, size_t in_len, char* &out_buff, size_t &out_len, PROCCESS_CONFIG *config)
{
	MagickWand *m_wand = NULL;
	
	int width,height;
	
	MagickWandGenesis();
	
	m_wand = NewMagickWand();
	// Read the image - all you need to do is change "logo:" to some other
	// filename to have this resize and, if necessary, convert a different file
	MagickReadImageBlob(m_wand,in_buff, in_len);
	
	// Get the image's width and height
	width = config->out_width;
	height = config->out_height;
	
	// Resize the image using the Lanczos filter
	// The blur factor is a "double", where > 1 is blurry, < 1 is sharp
	// I haven't figured out how you would change the blur parameter of MagickResizeImage
	// on the command line so I have set it to its default of one.
	MagickResizeImage(m_wand,width,height,LanczosFilter,1);
	
	// Set the compression quality to 95 (high quality = low compression)
	MagickSetImageCompressionQuality(m_wand,50);
	
	/* Write the new image */

	size_t out_img_size;
	out_buff =(char*) MagickGetImageBlob(m_wand, &out_img_size);
	out_len = out_img_size;
	
	/* Clean up */
	if(m_wand)m_wand = DestroyMagickWand(m_wand);
	
	MagickWandTerminus();
}