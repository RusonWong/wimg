#include "ImageUtil.h"
#include <algorithm>
#include <string>
#include <wand/MagickWand.h>

using namespace std;

int  resize_image(char* in_buff, size_t in_len, char* &out_buff, size_t &out_len, IMG_PROCCESS_CONFIG *config, bool remove_exif)
{
	MagickWand *m_wand = NULL;
	
	int width,height;
	
	m_wand = NewMagickWand();
	// Read the image - all you need to do is change "logo:" to some other
	// filename to have this resize and, if necessary, convert a different file
	MagickReadImageBlob(m_wand,in_buff, in_len);
	
	string img_format(MagickGetImageFormat(m_wand));

	if( img_format != "JPEG")
	{
		//if image is not jpeg file, do  convert
		MagickSetImageFormat(m_wand, "JPEG");
	}


	// Get the image's width and height
	bool keep_proportion = config->keep_proportion;

	width = config->out_width;
	height = config->out_height;

	if(keep_proportion)
	{
		int origin_width = MagickGetImageWidth(m_wand);
		int origin_height = MagickGetImageHeight(m_wand);

		if( origin_width < width && origin_height < height)
		{
			return 0;
		}

		float w_scale = ((float)width)/origin_width;
		float h_scale = ((float)height)/origin_height;

		float scale = std::min(w_scale, h_scale);

		width = scale * origin_width;
		height = scale * origin_height;
	}

	MagickResizeImage(m_wand,width,height,LanczosFilter,1);
	
	// Set the compression quality to 95 (high quality = low compression)
	MagickSetImageCompressionQuality(m_wand,75);
	
	if(remove_exif)
	{
		MagickStripImage(m_wand);
	}

	/* Write the new image */
	size_t out_img_size;
	out_buff =(char*) MagickGetImageBlob(m_wand, &out_img_size);
	out_len = out_img_size;
	
	/* Clean up */
	if(m_wand)m_wand = DestroyMagickWand(m_wand);

	return 1;
}
