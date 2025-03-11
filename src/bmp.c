#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Define the BMP header structures

// BMP file header (14 bytes)
#pragma pack(push, 1) // Ensure no padding
typedef struct {
    uint16_t bfType;         // File type, must be 'BM'
    uint32_t bfSize;         // Size of the BMP file
    uint16_t bfReserved1;    // Reserved, should be 0
    uint16_t bfReserved2;    // Reserved, should be 0
    uint32_t bfOffBits;      // Offset to the start of pixel data
} BMPHeader;

// BMP info header (40 bytes)
typedef struct {
    uint32_t biSize;         // Size of the info header
    int32_t biWidth;         // Width of the image
    int32_t biHeight;        // Height of the image
    uint16_t biPlanes;       // Number of planes, must be 1
    uint16_t biBitCount;     // Bits per pixel (24 for RGB)
    uint32_t biCompression;  // Compression method (0 = none)
    uint32_t biSizeImage;    // Size of the image data
    int32_t biXPelsPerMeter; // X pixels per meter (0 for default)
    int32_t biYPelsPerMeter; // Y pixels per meter (0 for default)
    uint32_t biClrUsed;      // Number of colors used (0 for default)
    uint32_t biClrImportant; // Number of important colors (0 for default)
} BMPInfoHeader;

#pragma pack(pop)

// Function to write BMP image
void createBMP(const char *filename, int width, int height, uint8_t red, uint8_t green, uint8_t blue) {
    // Create the BMP file
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Unable to create BMP file");
        return;
    }

    // Prepare headers
    BMPHeader bmpHeader = {0};
    BMPInfoHeader bmpInfoHeader = {0};

    bmpHeader.bfType = 0x4D42;  // "BM" in ASCII
    bmpHeader.bfSize = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + (width * height * 3); // Total file size
    bmpHeader.bfOffBits = sizeof(BMPHeader) + sizeof(BMPInfoHeader); // Data offset

    bmpInfoHeader.biSize = sizeof(BMPInfoHeader);
    bmpInfoHeader.biWidth = width;
    bmpInfoHeader.biHeight = height;
    bmpInfoHeader.biPlanes = 1;
    bmpInfoHeader.biBitCount = 24; // 24 bits for RGB
    bmpInfoHeader.biCompression = 0; // No compression
    bmpInfoHeader.biSizeImage = width * height * 3; // Image data size
    // bmpInfoHeader.biXPelsPerMeter = 2835; // 72 DPI
    // bmpInfoHeader.biYPelsPerMeter = 2835; // 72 DPI
    bmpInfoHeader.biXPelsPerMeter = 0; // 0 = no data
    bmpInfoHeader.biYPelsPerMeter = 0; // 0 = no data

    // Write headers to file
    fwrite(&bmpHeader, sizeof(BMPHeader), 1, file);
    fwrite(&bmpInfoHeader, sizeof(BMPInfoHeader), 1, file);

    // Prepare pixel data (RGB)
    // uint32_t *pixelData = (uint32_t *)malloc(width * height * 4);
    uint8_t *pixelData = (uint8_t *)malloc(width * height * 3);
    if (!pixelData) {
        perror("Unable to allocate memory for pixel data");
        fclose(file);
        return;
    }

    // Set the pixel data (all pixels will have the specified color)
    for (int i = 0; i < width * height; i++) {
        // pixelData[i] = 0xFFFFFF;   // Blue
        pixelData[i * 3] = blue;   // Blue
        pixelData[i * 3 + 1] = green; // Green
        pixelData[i * 3 + 2] = red; // Red
    }

    // Write pixel data to the file
    fwrite(pixelData, 1, width * height * 3, file);

    // Clean up and close the file
    free(pixelData);
    fclose(file);
}

int main() {
    int width = 100; // Image width
    int height = 100; // Image height
    uint8_t red = 255, green = 0, blue = 0; // Color (red)

    // Create a BMP file with the specified dimensions and color
    createBMP("output.bmp", width, height, red, green, blue);

    printf("BMP image created successfully!\n");
    return 0;
}
