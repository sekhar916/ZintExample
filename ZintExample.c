#include <stdio.h>
#include <zint.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define WIDTH 576
void show_image( unsigned char *, int , int  );

int main()
{
	int i,j;
	unsigned char *BMPBuffer;
        struct zint_symbol *my_symbol;my_symbol = ZBarcode_Create();
        if(my_symbol != NULL) 
        {
                printf("Symbol successfully created!\n");
		my_symbol->symbology = 58;
	//	my_symbol->scale = 2;
		ZBarcode_Encode(my_symbol, "www.google.com", 0);
        	ZBarcode_Print(my_symbol, 0);
		ZBarcode_Buffer(my_symbol, 0); 
		printf("height= %d and width=%d\n", my_symbol->bitmap_height, my_symbol->bitmap_width);
		printf("size %d\n", sizeof((my_symbol->bitmap)));	


		show_image(my_symbol->bitmap, my_symbol->bitmap_height, my_symbol->bitmap_width);
		
        }
	
	
        ZBarcode_Delete(my_symbol);
        return 0;
}



void show_image( unsigned char *image, int height, int width)
{
	

//	printf("Hai I am BMP\n");
	unsigned char BMPimage[WIDTH * height * 3 + 54];
	int FileId= 1, n=0;
	char filename[100];
  	int  i, j,tmp=0,k=54,fd, l; 
  	unsigned char *bmp_infoheader=BMPimage+14;
  	unsigned short int tmp_short;
	unsigned char pad[3] = {0,0,0};
	memset(BMPimage, 0x00, WIDTH * height * 3 + 54);
	if (extrabytes == 4)
   		extrabytes = 0;
	BMPimage[0]='B';
	BMPimage[1] = 'M';
	tmp = 14 + 40 + WIDTH * height  *3;
	memcpy((BMPimage+2), &tmp, 4);
	/* 0 */
	tmp = 0;
	memcpy((BMPimage+6), &tmp, 4);
	/* Offset value */
	tmp = 14 + 40;
	memcpy((BMPimage+10), &tmp, 4);

	/* 40 */
	tmp = 40;
	memcpy(bmp_infoheader, &tmp, 4);
	/* Width */
	tmp = WIDTH;
	memcpy(bmp_infoheader + 4, &tmp, 4);
	/* Height */
	tmp = height;
	memcpy(bmp_infoheader + 8, &tmp, 4);
	/* 1 */
	tmp_short = 1;   
	memcpy(bmp_infoheader + 12, &tmp_short, 2);
	/* bpp */
	tmp_short = 24;
	memcpy(bmp_infoheader + 14, &tmp_short, 2);
	/* 0 = nessuna compressione */
	tmp = 0;
	memcpy(bmp_infoheader + 16, &tmp, 4);
	memcpy(bmp_infoheader + 20, &tmp, 4);
	memcpy(bmp_infoheader + 24, &tmp, 4);
	memcpy(bmp_infoheader + 28, &tmp, 4);
	memcpy(bmp_infoheader + 32, &tmp, 4);
	memcpy(bmp_infoheader + 36, &tmp, 4);
	printf("1\n");
  	for ( i = 0; i < height * width; i++ )
  	{
    		{
			BMPimage[k++] = image[n];
		 	BMPimage[k++] = image[n+1];
		 	BMPimage[k++] = image[n+2];
			n = n + 3;
			if(n%(width*3) == 0)
			{
				for(l = 0; l < ((WIDTH) - width) ;l++)
				{
					BMPimage[k++] = 0x00 ^ 0xFF;
					BMPimage[k++] = 0x00 ^ 0xFF ;
					BMPimage[k++] = 0x00 ^ 0xFF;
				}
			}
    		}
  	}
	printf("2\n");
  	sprintf(filename,"rm -f Test%d.bmp",FileId);
  	system(filename);
  	sprintf(filename,"touch Test%d.bmp",FileId);
  	system(filename);
  	sprintf(filename,"Test%d.bmp",FileId);
  	fd = open(filename,O_RDWR);
  	if(fd>0)
  	{
  		write(fd,BMPimage,54);
		for(i = height-1;i >= 0 ;  i--)
		{
			write(fd,BMPimage+(i* WIDTH * 3)+54,WIDTH*3);	
			
		}
		close(fd);
  	}
  	else
  	{
		printf("File open failed\n");
  	}
 	 FileId++;
}


