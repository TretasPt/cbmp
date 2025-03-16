#include "cbmp.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

// Declarations

#define ARG_SUCCESS 1
#define ARG_ERROR -1
#define ARG_NEUTRAL 0

int randRange(int, int);
int distance(int, int, int, int);

int parameterLoop(int argc, char const *argv[]);
int handleParameter(int *pI, int argc, char const *argv[]);

int main(int argc, char const *argv[])
{
    // int width = 500;  // Image width
    // int height = 500; // Image height

    // // Create a BMP file with the specified dimensions and color
    // createBMP("output/output.bmp", width, height);

    // printf("BMP image created successfully.\n");
    int success = parameterLoop(argc, argv);
    switch (success)
    {
    case ARG_ERROR:
        printf("Code finished execution early with errors.");
        break;
    case ARG_SUCCESS:
        printf("Code finished execution early with no errors.");
        break;
    case ARG_NEUTRAL:
        printf("Code finished execution with no errors.");
        break;

    default:
        printf("Code finished execution with unknown success status %d.", success);
        break;
    }
    return 0;
}

// b
int randRange(int min, int max)
{
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

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

    int imageByteCount = width * height * sizeof(union Color24);

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
    union Color24 *pixelData = (union Color24 *)malloc(imageByteCount);
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
    int crx, cry, cgx, cgy, cbx, cby;
    crx = randRange(0, 255);
    cry = randRange(0, 255);
    cgx = randRange(0, 255);
    cgy = randRange(0, 255);
    cbx = randRange(0, 255);
    cby = randRange(0, 255);
    printf("%d,%d\n%d,%d\n%d,%d\n", crx, cry, cgx, cgy, cbx, cby);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            pixelData[width * y + x].red = fmax(0, 255 - (distance(x, y, 0, 0)));
            pixelData[width * y + x].green = fmax(0, 255 - (distance(x, y, 0, height)));
            pixelData[width * y + x].blue = fmax(0, 255 - (distance(x, y, width, height / 2)));
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

int handleParameter(int *pI, int argc, char const *argv[])
{
    if (argc <= 1)
    {
        printf("Some help function will be called and will print some info.\n");
        return ARG_ERROR;
    }
    if (*pI >= argc)
    {
        return ARG_ERROR;
    }

    char *currentCommand = argv[*pI];
    // printf("i=%d\n",*pI);
    // printf("%d: %s\n", *pI, currentCommand);

    if (strcmp(currentCommand, "-h") == 0 || strcmp(currentCommand, "--help") == 0)
    {
        printf("Some help function will be called and will print some info.\n");
        (*pI)++;
        return ARG_SUCCESS;
    }
    else if (strcmp(currentCommand, "-if") == 0)
    {
        if (*pI + 1 >= argc)
        {
            printf("Not enough arguments passed. After the flag \"%s\" an input file or directory was expected.\n", currentCommand);
            // (*pI)++;
            return ARG_ERROR;
        }
        // TODO get all the infiles
        char *infiles = argv[++(*pI)];
        printf("infiles set to: %s\n", infiles);
        (*pI)++;
        return ARG_NEUTRAL;
    }
    else
    {
        printf("Unrecognized parameter: %s\nExiting...\n", currentCommand);
        // (*pI)++;
        return ARG_ERROR;
    }

    (*pI)++;
    return ARG_ERROR; // Should never happen. Only here to catch errors
};

int parameterLoop(int argc, char const *argv[])
{

    // printf("There are %d arguments.\n", argc - 1);
    int i = 1;
    int *pI = &i;
    int loopStatus = ARG_NEUTRAL;
    // for (i = 0; i < argc; i++)
    do
    {
        loopStatus = handleParameter(pI, argc, argv);
    } while (i < argc && loopStatus == ARG_NEUTRAL);

    return loopStatus;
}
