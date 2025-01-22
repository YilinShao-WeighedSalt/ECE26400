#ifndef __ANSWER07_H__
#define __ANSWER07_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#pragma pack(push) // save the original data alignment
#pragma pack(1)    // Set data alignment to 1 byte boundary

/*
 * BMP files are laid out in the following fashion:
 *   --------------------------
 *   |          Header        |   54 bytes
 *   |-------------------------
 *   |       Image Data       |   file size - 54 (for 24-bit images)
 *   --------------------------
 */

/**
 * BMP header (54 bytes).
 * uint16_t is 16-bit unsigned integer
 * uint32_t is 32-bit unsigned integer
 * int32_t is 32-bit signed integer
 */

typedef struct _BMP_header
{
    uint16_t type;             // Magic identifier
    uint32_t size;             // File size in bytes
    uint16_t reserved1;        // Not used
    uint16_t reserved2;        // Not used
    uint32_t offset;           // Offset to image data in bytes from
                               // beginning of file (54 bytes)
    uint32_t DIB_header_size;  // DIB header size in bytes (40 bytes)
    int32_t width;             // Width of the image
    int32_t height;            // Height of image
    uint16_t planes;           // Number of color planes
    uint16_t bits;             // Bits per pixel
    uint32_t compression;      // Compression type
    uint32_t imagesize;        // Image size in bytes
    int32_t xresolution;       // Pixels per meter
    int32_t yresolution;       // Pixels per meter
    uint32_t ncolours;         // Number of colors
    uint32_t importantcolours; // Important colors
} BMP_header;

#pragma pack(pop) // restore the previous pack setting

typedef struct _BMP_image
{
    BMP_header header;
    unsigned char *data;
} BMP_image;

// Functions to be defined by students

// Read BMP_image from a given file
//
BMP_image *read_BMP_image(char *filename);

// Check the validity of the header with the file from which the header is read
//
bool is_BMP_header_valid(BMP_header *bmp_hdr, FILE *fptr);

// Write BMP_image to a given file
//
int write_BMP_image(char *filename, BMP_image *image);

// Free memory in a given image
//
void free_BMP_image(BMP_image *image);

// Given a BMP_image, create a new image that is a vertical and/or horizontal
// reflection of the given image
// All padding bytes must be assigned 0
// The new image may be similar to the given image, except the padding bytes
// It may be a horizontal reflection (with the vertical mirror being placed
// at the center of the image)
// It may be a vertical reflection (with the horizontal mirror being placed
// at the center of the image)
// It may be a horizontal reflection followed by a vertical reflection (or
// equivalently, a vertical reflection followed by horizontal reflection).
// hrefl == true implies that a horizontal reflection should take place
// hrefl == false implies that a horizontal reflection should not take place
// vrefl == true implies that a vertical reflection should take place
// vrefl == false implies that a vertical reflection should not take place
//
BMP_image *reflect_BMP_image(BMP_image *image, bool hrefl, bool vrefl);

#endif /* answer07.h */
