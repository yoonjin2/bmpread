#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<linux/fb.h>
#include<sys/mman.h>
#include<sys/ioctl.h>
#include "bmpread.h"
char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}
int main(int argc, char **argv)
{
	char  string[1000];
	sprintf(string, "convert %s -rotate 180 %s",argv[1],argv[1]);
	system(string);
	char ascii[]={'#','#','@','%','=','+','*',':','-','.',' '};
    FILE *infile,*outfile=fopen("RESULT.txt","wt");
    infile=fopen(argv[1],"rb");
    if(infile==NULL)return 1;
    BITMAPFILEH hf;
    BITMAPINFOH info;
    fread(&hf,sizeof(BITMAPFILEH),1,infile);
    fread(&info,sizeof(BITMAPINFOH),1,infile);
    unsigned char *img=malloc(info.bisizeimage);
    int height=info.biheight,width=info.biwidth;
    int padding=(PIXEL_ALIGN-((width*PIXEL_SIZE)%PIXEL_ALIGN))%PIXEL_ALIGN;
    fseek(infile,hf.bfoffbits,SEEK_SET);
    fread(img,info.bisizeimage,1,infile);
    int i,j;
	struct fb_var_screeninfo framebuffer_var_screeninfo;
	struct fb_fix_screeninfo framebuffer_fixed_screeninfo;
	int framebuffer_err=open("/dev/fb0",O_RDWR);
	if(framebuffer_err<0){
		perror("ERROR: cannot open framebuffer device\n");
	return 1;
	}
	framebuffer_var_screeninfo.bits_per_pixel=32;  
	if(ioctl(framebuffer_err, FBIOGET_VSCREENINFO, &framebuffer_var_screeninfo)) {
		perror("ERROR: cannot read variable screen information\n");
		return 1;
	}if(ioctl(framebuffer_err, FBIOGET_FSCREENINFO, &framebuffer_fixed_screeninfo)){
		perror("ERROR: cannot read fixed screen information\n");
		return 1;
	}
	int w=framebuffer_var_screeninfo.xres, h=framebuffer_var_screeninfo.yres, bpp=framebuffer_var_screeninfo.bits_per_pixel/8, xoffset=framebuffer_var_screeninfo.xoffset, yoffset=framebuffer_var_screeninfo.yoffset;
	long screensize=w*h*bpp;
	char *fbptr=(char *)mmap(0,screensize,PROT_READ|PROT_WRITE, MAP_SHARED, framebuffer_err, 0);
	if(fbptr==MAP_FAILED) {
		perror("ERROR:mmap\n");
		return 1;
	}
printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
for(i=height-1;i>=0;i--)
    {
        for(j=0;j<width;j++)
            {
		unsigned int pixel_offset=(i+yoffset)*framebuffer_fixed_screeninfo.line_length+(j+xoffset)*bpp;
                char c;
                int index=j*PIXEL_SIZE+i*(width*PIXEL_SIZE)+padding*i;
                RGB *pix=(RGB *)&img[index];
                unsigned char Red=pix->R,Blue=pix->B,Green=pix->G,gray=(Green+Red+Blue)/PIXEL_SIZE;
                c=ascii[gray*sizeof(ascii)/256];
                fprintf(outfile,"%c",c);
			fbptr[pixel_offset]=Blue;
			fbptr[pixel_offset+1]=Green;
			fbptr[pixel_offset+2]=Red;
			fbptr[pixel_offset+3]=gray;
	    }
            fputc('\n',outfile);
			
	
    }
munmap(fbptr,screensize);
close(framebuffer_err);
fclose(infile);
fclose(outfile);
system(string);
return 0;
}
