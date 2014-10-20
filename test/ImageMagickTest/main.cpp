#include <iostream>
#include <math.h>
#include <wand/MagickWand.h>
#include <string>
#include <fstream>

using namespace std;


int get_local_file(std::string file_path, char* &buffptr,size_t& len)
{
    ifstream ifile(file_path.c_str());
    if (ifile.fail())
    {
        std::cout<<("No file " + file_path + " found");
        return 0;
    }
    else{

        ifile.seekg(0,ios::end);
        long fSize = (long)ifile.tellg();
        ifile.seekg(0,ios::beg);

        len = (size_t)fSize;

        cout<<"file lenth is:"<<fSize<<endl;
        buffptr = new char[fSize];
        int size_read = 0;
        while(size_read != fSize)
        {   
            ifile.read(buffptr + size_read, fSize - size_read);
            size_read += fSize;
        }
        return 1;
    }

    ifile.close();
    return 1;
}

int write_local_file(std::string filePath, char* content, size_t len)
{
    std::ofstream ofile;
   
    ofile.open(filePath.c_str(), std::ios::binary);
    if(ofile.fail())
    {
        printf("create file failed\n");
        return 0;
    }
    printf("create file successs\n");

    int size_writen = 0;
    while(size_writen != len)
    {
        ofile.write(content+size_writen, len - size_writen);
        size_writen += len;
    }

    ofile.close();
    return 1;
}



void test_wand(void)
{
	MagickWand *m_wand = NULL;
	
	int width,height;
	
	MagickWandGenesis();
	
	m_wand = NewMagickWand();
	// Read the image - all you need to do is change "logo:" to some other
	// filename to have this resize and, if necessary, convert a different file
	char* in_buff;
	size_t in_len;
	get_local_file("2.jpg",in_buff,in_len);

	MagickReadImageBlob(m_wand,in_buff, in_len);
	
	// Get the image's width and height
	width = MagickGetImageWidth(m_wand);
	height = MagickGetImageHeight(m_wand);
	
	// Cut them in half but make sure they don't underflow
	if((width /= 2) < 1)width = 1;
	if((height /= 2) < 1)height = 1;
	
	// Resize the image using the Lanczos filter
	// The blur factor is a "double", where > 1 is blurry, < 1 is sharp
	// I haven't figured out how you would change the blur parameter of MagickResizeImage
	// on the command line so I have set it to its default of one.
	printf("%d\n", 1);
	MagickResizeImage(m_wand,width,height,LanczosFilter,1);
	printf("%d\n", 2);
	// Set the compression quality to 95 (high quality = low compression)
	MagickSetImageCompressionQuality(m_wand,50);
	printf("%d\n", 3);
	/* Write the new image */
	bool  ret = MagickWriteImage(m_wand,"resize.jpg");
	if(ret)
	{
		cout<<"write to local success\n";
	}
	else
	{
		cout<<"write to local failed\n";
		//ThrowWandException(m_wand);
	}
	/*
	char* out_buff;
	size_t out_img_size;

	out_buff =(char*) MagickGetImageBlob(m_wand, &out_img_size);
	cout<<"new size is:"<<out_img_size<<endl;
	write_local_file("output.jpg", out_buff, out_img_size);
	*/

	printf("%d\n", 4);
	/* Clean up */
	if(m_wand)m_wand = DestroyMagickWand(m_wand);
	printf("%d\n", 5);
	MagickWandTerminus();
	printf("%d\n", 6);
}


int main()
{
	test_wand();
}