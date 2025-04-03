#include <stdint.h>

// Structures

#pragma pack(push, 1) // Ensure no padding
                      // Color with 24 bpp
                      // Define a union to allow access to RGB channels as one 24-bit value or individually

struct Color24
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

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

struct CBMPSettings
{
    char **infiles;
    int infilesCount;
    char **infiles2;
    int infiles2Count;
    char **outfiles;
    int outfilesCount;
    int reverse;
};

/*
    Temporary documentation for a temporary function.
*/
void createBMP_baseTest(const char *, int, int);

void createBMP(struct CBMPSettings *settings);
/*
Returns a formatted text with the CBMPSettings.
*/
void printSettings(struct CBMPSettings *settings);
/*
 * Writes the data to the buffer...
 */
int encodingSimple();
int readFileBytes();