#include <windows.h>
#include <wingdi.h>

// BITMAPINFOHEADER

struct BMP_Header
{
    unsigned char Signature[2];// = {'B', 'M'};// = {0x42 0x4D}
    unsigned char FileSize[4];
    unsigned char reserved[4];
    unsigned char DataOffset[4];
};


struct BMP{
    struct BMP_Header header;
    struct emp {
        int car2;
    };
};

// #include <stdio.h>

int main() {
    // unsigned char byteArray[5] = {0x01, 0x02, 0x03, 0x04, 0x05};
    
    // for (int i = 0; i < 5; i++) {
    //     printf("byteArray[%d] = %02X\n", i, byteArray[i]);
    // }
    RGBQUAD a [9];
    a[0].rgbBlue = 0xff;
    a[1].rgbGreen = 0xff;
    a[2].rgbRed = 0xff;
    a[1].rgbGreen = 0xff;
    HBITMAP b = CreateBitmap(3,3,3,3,a);
    return 0;
}
