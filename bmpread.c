#include<stdio.h>
#include<stdlib.h>
#include "bmpread.h"
int main(int argc, char **argv)
{
    char ascii[]={'#','#','@','%','=','+','*',':','-','.',' '};
    FILE *infile,*outfile=fopen("RESULT.txt","wt");
    infile=fopen(argv[1],"rb");
    if(infile==NULL)return;
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
    for(i=height-1;i>=0;i--)
    {
        for(j=0;j<width;j++)
            {
                char c;
                int index=j*PIXEL_SIZE+i*(width*PIXEL_SIZE)+padding*i;
                RGB *pix=(RGB *)&img[index];
                unsigned char Red=pix->R,Blue=pix->B,Green=pix->G,gray=(Green+Red+Blue)/PIXEL_SIZE;
                c=ascii[gray*sizeof(ascii)/256];
                fprintf(outfile,"%c",c);
                if(Green>Red && Green>Blue && Green-Blue>10)
                    printf(GREEN"%c"RESET,c );
                else if(Red>Blue && Red>Green  && Green+Blue<=125 && Red>=125)
                    printf(RED"%c"RESET,c);
                else if(Green>Blue && Red>Blue && abs(Green-Red)<=50)
                    printf(YELLOW"%c"RESET,c);
                else if(Green>Red)
                    printf(CYAN"%c"RESET,c);
                else if(Blue>Green)
                {
                    if(Blue>Red)
                        printf(BLUE"%c"RESET,c);
                    else if(Red>=Blue && abs(Blue-Red)<=50)
                        printf(MAGENTA"%c"RESET,c);
                }
                else
                    printf(RESET"%c"RESET,c);

            }
            putc('\n',stdout);
            fputc('\n',outfile);
    }
fclose(infile);
return 0;
}
