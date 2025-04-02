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

int parameterLoop(int argc, char const *argv[], struct CBMPSettings *settings);
int handleParameter(int *pI, int argc, char const *argv[], struct CBMPSettings *settings);
int getStringCount(int argc, char const *argv[], int index);
void createBMPFile(FILE *outFile, int width, int height, char *data);

int main(int argc, char const *argv[])
{
    // int width = 500;  // Image width
    // int height = 500; // Image height

    // // Create a BMP file with the specified dimensions and color
    // createBMP("output/output.bmp", width, height);

    // printf("BMP image created successfully.\n");
    struct CBMPSettings settings = {0};
    int success = parameterLoop(argc, argv, &settings);
    switch (success)
    {
    case ARG_ERROR:
        printf("Code finished execution early with errors.\n");
        break;
    case ARG_SUCCESS:
        printf("Code finished execution early with no errors.\n");
        break;
    case ARG_NEUTRAL:
        printf("Code finished execution with no errors.\n");
        break;

    default:
        printf("Code finished execution with unknown success status %d.\n", success);
        break;
    }

    printSettings(&settings);

    if (success == ARG_NEUTRAL)
    {
        printf("All parameters read. Advancing.\n");
        createBMP2(&settings);
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

void createBMP2(struct CBMPSettings *settings)
{
    char *outFileName;
    if (settings->outfilesCount < 1)
    {
        outFileName = "output.BMP";
    }
    else
    {
        outFileName = settings->outfiles[0];
    }
    printf("OutFile will be %s\n", outFileName);
    FILE **localInFiles = malloc(settings->infilesCount * sizeof(FILE *));
    for (int i = 0; i < settings->infilesCount; i++)
    {

        localInFiles[i] = fopen(settings->infiles[i], "rb");
        fseek(localInFiles[i], 0, SEEK_END);
        int fileLength = ftell(localInFiles[i]);
        rewind(localInFiles[i]);

        char *buffer = (char *)malloc(sizeof(char) * fileLength);
        fread(buffer, sizeof(char), fileLength, localInFiles[i]);
        fclose(localInFiles[i]);

        for (int j = 0; j < fileLength; j++)
        {
            printf("%c", buffer[j]);
        }
        printf("\n");
        for (int j = 0; j < fileLength; j++)
        {
            printf("%X", buffer[j]);
        }
        printf("\n");

        // FILE *copy = fopen("test.out.txt", "wb");
        // fwrite(buffer, sizeof(char), fileLength, copy);
        // fclose(copy);
        FILE * copy = fopen("test.out.bmp", "wb");
        // fileLength = fileLength/3;// 3
        createBMPFile(copy,ceil(sqrt(fileLength)),ceil(sqrt(fileLength)),buffer);
        fclose(copy);
    }
}

void createBMPFile(FILE *outFile, int width, int height, char *data)
{

    // Prepare headers
    struct BMPHeader bmpHeader = {0};
    struct BMPInfoHeader bmpInfoHeader = {0};

    // int imageByteCount = width * height * sizeof(union Color24);
    int imageByteCount = width * height;

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
    fwrite(&bmpHeader, sizeof(struct BMPHeader), 1, outFile);
    fwrite(&bmpInfoHeader, sizeof(struct BMPInfoHeader), 1, outFile);

    // Write pixel data to the file
    fwrite(data, 1, imageByteCount, outFile);

    // Clean up and close the file
}

int handleParameter(int *pI, int argc, char const *argv[], struct CBMPSettings *settings)
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
        if (settings->infiles != NULL)
        {
            free(settings->infiles);
            settings->infiles = NULL;
        }
        settings->infilesCount = getStringCount(argc, argv, *pI) - (*pI + 1);
        // printf("There are %d files.\n", settings->infilesCount);
        settings->infiles = (char **)malloc(settings->infilesCount * sizeof(char *));
        if (settings->infiles == NULL)
        {
            printf("malloc failed to alocate space for the infiles");
            return ARG_ERROR;
        }
        for (int i = 0; i < settings->infilesCount; i++)
        {
            settings->infiles[i] = argv[*pI + i + 1];
        }

        (*pI) += settings->infilesCount + 1;

        return ARG_NEUTRAL;
    }
    else if (strcmp(currentCommand, "-if2") == 0)
    {
        if (*pI + 1 >= argc)
        {
            printf("Not enough arguments passed. After the flag \"%s\" an input file or directory was expected.\n", currentCommand);
            // (*pI)++;
            return ARG_ERROR;
        }
        if (settings->infiles2 != NULL)
        {
            free(settings->infiles2);
            settings->infiles2 = NULL;
        }
        settings->infiles2Count = getStringCount(argc, argv, *pI) - (*pI + 1);
        // printf("There are %d files.\n", settings->infiles2Count);
        settings->infiles2 = (char **)malloc(settings->infiles2Count * sizeof(char *));
        if (settings->infiles2 == NULL)
        {
            printf("malloc failed to alocate space for the infiles2");
            return ARG_ERROR;
        }
        for (int i = 0; i < settings->infiles2Count; i++)
        {
            settings->infiles2[i] = argv[*pI + i + 1];
        }

        (*pI) += settings->infiles2Count + 1;

        return ARG_NEUTRAL;
    }
    else if (strcmp(currentCommand, "-of") == 0)
    {
        if (*pI + 1 >= argc)
        {
            printf("Not enough arguments passed. After the flag \"%s\" an input file or directory was expected.\n", currentCommand);
            // (*pI)++;
            return ARG_ERROR;
        }
        if (settings->outfiles != NULL)
        {
            free(settings->outfiles);
            settings->outfiles = NULL;
        }
        settings->outfilesCount = getStringCount(argc, argv, *pI) - (*pI + 1);
        // printf("There are %d files.\n", settings->outfilesCount);
        settings->outfiles = (char **)malloc(settings->outfilesCount * sizeof(char *));
        if (settings->outfiles == NULL)
        {
            printf("malloc failed to alocate space for the outfiles");
            return ARG_ERROR;
        }
        for (int i = 0; i < settings->outfilesCount; i++)
        {
            settings->outfiles[i] = argv[*pI + i + 1];
        }

        (*pI) += settings->outfilesCount + 1;

        return ARG_NEUTRAL;
    }
    else if (strcmp(currentCommand, "-r") == 0 || strcmp(currentCommand, "--recover") == 0 ||
             strcmp(currentCommand, "--reverse") == 0 || strcmp(currentCommand, "--decode") == 0)
    {
        // printf("Decoding mode selected.\n");
        settings->reverse = 1;
        (*pI)++;
        return ARG_NEUTRAL;
    }
    else if (strcmp(currentCommand, "-e") == 0)
    {
        if (*pI + 1 >= argc)
        {
            printf("Not enough arguments passed. After the flag \"%s\" encoding was expected.\n", currentCommand);
            return ARG_ERROR;
        }
        // TODO get all the infiles
        char *encoding = argv[++(*pI)];
        printf("Selected endoding is %s.\n", encoding);
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

int parameterLoop(int argc, char const *argv[], struct CBMPSettings *settings)
{

    // printf("There are %d arguments.\n", argc - 1);
    int i = 1;
    int *pI = &i;
    int loopStatus = ARG_NEUTRAL;
    // for (i = 0; i < argc; i++)
    do
    {
        loopStatus = handleParameter(pI, argc, argv, settings);
    } while (i < argc && loopStatus == ARG_NEUTRAL);

    return loopStatus;
}

int getStringCount(int argc, char const *argv[], int index)
{
    index++;
    while (index < argc)
    {
        if (strncmp("-", argv[index], 1) == 0)
            break;
        index++;
    }
    return index;
}

void printSettings(struct CBMPSettings *settings)
{
    printf("Settings:\n\tInFiles[%d]: ", settings->infilesCount);
    for (int i = 0; i < settings->infilesCount; i++)
    {
        if (settings->infiles && settings->infiles[i])
            printf("%s; ", settings->infiles[i]);
        else
            printf("error? ");
    }

    printf("\n\tInFiles2[%d]: ", settings->infiles2Count);
    for (int i = 0; i < settings->infiles2Count; i++)
    {
        if (settings->infiles2 && settings->infiles2[i])
            printf("%s; ", settings->infiles2[i]);
        else
            printf("error? ");
    }

    printf("\n\tOutFiles[%d]: ", settings->outfilesCount);
    for (int i = 0; i < settings->outfilesCount; i++)
    {
        if (settings->outfiles && settings->outfiles[i])
            printf("%s; ", settings->outfiles[i]);
        else
            printf("error? ");
    }

    printf("\n\tIsReverse: %d\n", settings->reverse);
}
