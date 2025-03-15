# cbmp

The idea of the project is to display data in various forms.
The most basic form is encoding all the bytes as colors in a BMP image file. Due to it's uncompressed nature, it's simple to used and perfect for this project as a first POC.

The idea is to create a shell program with multiple possible encodings.

The current expected structure is:

cbmp [**-h** | **--help**]  
cbmp [**-if** *infiles*] [**-if2** *infiles2*] [**-of** *outfiles*]

[Encodings](#securityencodingencription) - Contains a list of valid encodings.

## security/encoding/encription

[Simple](#encoding-simple)
[Mixed](#encoding-mixed)

### Encoding Simple

    For now only simple will be implemented.
    mixed

### Encoding Mixed

    Mix 2 files in one output. Meant to be used with 2 separate file sources.
    Source 1 *infiles1* is the data to be encoded that shouldn't be recovreable.
    Source 2 *infiles2* is the image to use as a base. The original image will not be recoverable.
    Output *outfiles* will be an image, simmilar to Source 2, but with the N least significant bits swapped by bits from Source 1.
    EX assumming 1 byte (= 8 bits) per pixel per chanel:
        N=4
        IN2 = 0xFA 50 07 FA 50 07 = (1111 1010 0101 0000 0000 0111 1111 1010 0101 0000 0000 0111)2
        IN1 = 0x41 42 43 =          (0100 0001 0100 0010 0100 0011)2
        OUT = 0xF4 51 04 F2 54 03 = (1111 0100 0101 0001 0000 0100 1111 0010 0101 0100 0000 0011)2

### Encoding XOR

    Expects 2 files (One must be a BMP) and outputs a BMP file.
    The outputed image file will have the data equal to the bitwise XOR of the data from both sources.
    If N != 8, for each color, the N least significant bits will be XORed with bits from the file source.
