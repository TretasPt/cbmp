#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#pragma pack(push, 1) // Ensure no padding
struct Color
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

// Define the BMP header structures

// BMP file header (14 bytes)
struct BMPHeader
{
    uint16_t bfType;      // File type, must be 'BM'
    uint32_t bfSize;      // Size of the BMP file
    uint16_t bfReserved1; // Reserved, should be 0
    uint16_t bfReserved2; // Reserved, should be 0
    uint32_t bfOffBits;   // Offset to the start of pixel data
};

// BMP info header (40 bytes)
struct BMPInfoHeader
{
    uint32_t biSize;         // Size of the info header
    int32_t biWidth;         // Width of the image
    int32_t biHeight;        // Height of the image
    uint16_t biPlanes;       // Number of planes, must be 1
    uint16_t biBitCount;     // Bits per pixel (24 for RGB) //1, 4, 8, 15, 24, 32, or 64
    uint32_t biCompression;  // Compression method (0 = none)
    uint32_t biSizeImage;    // Size of the image data
    int32_t biXPelsPerMeter; // X pixels per meter (0 for default)
    int32_t biYPelsPerMeter; // Y pixels per meter (0 for default)
    uint32_t biClrUsed;      // Number of colors used (0 for default)
    uint32_t biClrImportant; // Number of important colors (0 for default)
};

#pragma pack(pop)

int randRange(int min, int max)
{
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int distance(int x1, int y1, int x2, int y2){
    return sqrt(pow(x2-x1,2) + pow(y2-y1,2));
}

// Function to write BMP image
void createBMP(const char *filename, int width, int height)
{
    // Create the BMP file
    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        perror("Unable to create BMP file");
        return;
    }

    // Prepare headers
    struct BMPHeader bmpHeader = {0};
    struct BMPInfoHeader bmpInfoHeader = {0};

    int imageByteCount = width * height * sizeof(struct Color);

    bmpHeader.bfType = 0x4D42;                                                                     // "BM" in ASCII
    bmpHeader.bfSize = sizeof(struct BMPHeader) + sizeof(struct BMPInfoHeader) + (imageByteCount); // Total file size
    bmpHeader.bfOffBits = sizeof(struct BMPHeader) + sizeof(struct BMPInfoHeader);                 // Data offset

    bmpInfoHeader.biSize = sizeof(struct BMPInfoHeader);
    bmpInfoHeader.biWidth = width;
    bmpInfoHeader.biHeight = height;
    bmpInfoHeader.biPlanes = 1;
    bmpInfoHeader.biBitCount = 24;              // 24 bits for RGB
    bmpInfoHeader.biCompression = 0;            // No compression
    bmpInfoHeader.biSizeImage = imageByteCount; // Image data size
    // bmpInfoHeader.biXPelsPerMeter = 2835; // 72 DPI
    // bmpInfoHeader.biYPelsPerMeter = 2835; // 72 DPI
    bmpInfoHeader.biXPelsPerMeter = 0; // 0 = no data
    bmpInfoHeader.biYPelsPerMeter = 0; // 0 = no data

    // Write headers to file
    fwrite(&bmpHeader, sizeof(struct BMPHeader), 1, file);
    fwrite(&bmpInfoHeader, sizeof(struct BMPInfoHeader), 1, file);

    // Prepare pixel data (RGB)
    struct Color *pixelData = (struct Color *)malloc(imageByteCount);
    if (!pixelData)
    {
        perror("Unable to allocate memory for pixel data");
        fclose(file);
        return;
    }

    // for (int i = 0; i < width * height; i++)
    // {
    //     pixelData[i].red = randRange(0, 255);
    //     pixelData[i].green = randRange(0, 255);
    //     pixelData[i].blue = randRange(0, 255);
    // }
    int crx, cry,cgx,cgy,cbx,cby;
    crx = randRange(0,255);
    cry = randRange(0,255);
    cgx = randRange(0,255);
    cgy = randRange(0,255);
    cbx = randRange(0,255);
    cby = randRange(0,255);
    printf("%d,%d\n%d,%d\n%d,%d\n",crx, cry,cgx,cgy,cbx,cby);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            pixelData[width * y + x].red = fmax(0,255-(distance(x,y,0,0)));
            pixelData[width * y + x].green = fmax(0,255-(distance(x,y,0,height)));
            pixelData[width * y + x].blue = fmax(0,255-(distance(x,y,width,height/2)));
            // pixelData[width * y + x].red = 255-(distance(x,y,0,0)%255);
            // pixelData[width * y + x].green = 255-(distance(x,y,0,height)%255);
            // pixelData[width * y + x].blue = 255-(distance(x,y,width,height/2)%255);
            // pixelData[width * y + x].red = (x < 70 && y < 60) ? 255 : 0;
            // pixelData[width * y + x].green = (x < 70 && y > 40) ? 255 : 0;
            // pixelData[width * y + x].blue = (x > 50) ? 255 : 0;
            // pixelData[width * y + x].red = randRange(0, 255);
            // pixelData[width * y + x].green = randRange(0, 255);
            // pixelData[width * y + x].blue = randRange(0, 255);
        }
    }

    // Write pixel data to the file
    fwrite(pixelData, 1, imageByteCount, file);

    // Clean up and close the file
    free(pixelData);
    fclose(file);
}

int main()
{
    int width = 500;                        // Image width
    int height = 500;                       // Image height
    // printf("Color size %d\n", sizeof(Color));
    printf("Color size %d\n", sizeof(struct Color));

    // Create a BMP file with the specified dimensions and color
    createBMP("output/output.bmp", width, height);

    printf("BMP image created successfully!\n");

    // for (int i = 0; i < 100; i++)
    // {
    //     printf("%d\n",randRange(0,5));
    // }

    return 0;
}
