#pragma pack(push, 1);
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"
#define PIXEL_SIZE 3
#define PIXEL_ALIGN 4
typedef struct BITMAP_HEADER
{
    unsigned short bftype;
    unsigned int bfsize;
    unsigned short bfreserved0;
    unsigned short bfreserved1;
    unsigned int bfoffbits;
} BITMAPFILEH;
typedef struct BITMAP_INFO_HEADER
{
    unsigned int bisize;
    int biwidth;
    int biheight;
    unsigned short biplanes;
    unsigned short bibitcount;
    unsigned int bicompression;
    unsigned int bisizeimage;
    int bixpelspermetre;
    int biypelspermetre;
    unsigned int biclrused;
    unsigned int biclrimportant;
} BITMAPINFOH;
typedef struct RGBQUAD
{
    unsigned char B;
    unsigned char G;
    unsigned char R;
} RGB;
#pragma pack (pop);
