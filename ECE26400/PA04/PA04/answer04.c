#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "answer04.h"

// macros used in Is_BMP_Header_Valid function

#define BMP_TYPE 0x4d42
#define BMP_HEADER_SIZE 54
#define DIB_HEADER_SIZE 40

/* check whether a header is valid
 * assume that header has been read from fptr
 * the position of the indicator of fptr is not certain
 * could be at the beginning of the file, end of the file or
 * anywhere in the file
 * note that the check is only for this exercise/assignment
 * in general, the format is more complicated
 */

bool is_BMP_header_valid(BMP_header *header, FILE *fptr)
{
  // Make sure this is a BMP file
  if (header->type != BMP_TYPE)
  {
    return false;
  }
  // skip the two unused reserved fields

  // check the offset from beginning of file to image data
  // essentially the size of the BMP header
  // BMP_HEADER_SIZE for this exercise/assignment
  if (header->offset != BMP_HEADER_SIZE)
  {
    return false;
  }

  // check the DIB header size == DIB_HEADER_SIZE
  // For this exercise/assignment
  if (header->DIB_header_size != DIB_HEADER_SIZE)
  {
    return false;
  }

  // Make sure there is only one image plane
  if (header->planes != 1)
  {
    return false;
  }
  // Make sure there is no compression
  if (header->compression != 0)
  {
    return false;
  }

  // skip the test for xresolution, yresolution

  // ncolours and importantcolours should be 0
  if (header->ncolours != 0)
  {
    return false;
  }
  if (header->importantcolours != 0)
  {
    return false;
  }

  // Make sure we are getting 24 bits per pixel
  // or 16 bits per pixel
  if (header->bits != 24 && header->bits != 16)
  {
    return false;
  }

  // fill in code to check for file size, image size
  // based on bits, width, and height
  int bytes_per_pixel = header->bits / 8;
  int num_of_bytes = header->width * bytes_per_pixel;
  int size = (num_of_bytes + 3) & ~3;
  int exp_image_size = size * header->height;
  int exp_filesize = exp_image_size + BMP_HEADER_SIZE;

  fseek(fptr, 0, SEEK_END);
  int fp = ftell(fptr);
  if (fp != exp_filesize)
    return false;
  if (header->size != exp_filesize)
    return false;
  if (header->imagesize != exp_image_size)
    return false;
  return true;
}
BMP_image *read_BMP_image(char *filename)
{
  FILE *fp = fopen(filename, "rb");
  if (fp == NULL)
  {
    fprintf(stderr, "Could not open file");
    return NULL;
  }
  BMP_image *image = malloc(sizeof(*image));
  if (image == NULL)
  {
    fclose(fp);
    fprintf(stderr, "Error allocating memory for BMP_IMAGE\n");
    return NULL;
  }

  if (fread(&image->header, sizeof(BMP_header), 1, fp) != 1)
  {
    free(image);
    fclose(fp);
    fprintf(stderr, "Could not read header\n");
    return NULL;
  }
  if (!is_BMP_header_valid(&image->header, fp))
  {
    free(image);
    fclose(fp);
    fprintf(stderr, "Invalid header\n");
    return NULL;
  }

  image->data = malloc(image->header.imagesize);
  if (image->data == NULL)
  {
    free(image);
    fclose(fp);
    fprintf(stderr, "Failed allocating memopry for image data\n");
    return NULL;
  }

  fseek(fp, image->header.offset, SEEK_SET);
  if (fread(image->data, image->header.imagesize, 1, fp) != 1)
  {
    free(image->data);
    free(image);
    fclose(fp);
    fprintf(stderr, "Failed reading for data\n");
    return NULL;
  }

  fclose(fp);
  return image;
}
int write_BMP_image(char *filename, BMP_image *image)
{
  FILE *fp = fopen(filename, "wb");
  if (fp == NULL)
  {
    fprintf(stderr, "Failed opening file for writing\n");
    return 0;
  }

  if (fwrite(&image->header, sizeof(BMP_header), 1, fp) != 1)
  {
    fprintf(stderr, "Failed writing from header\n");
    fclose(fp);
    return 0;
  }

  if ((fwrite(image->data, image->header.imagesize, 1, fp)) != 1)
  {
    fprintf(stderr, "Failed writing from data\n");
    fclose(fp);
    return 0;
  }
  fclose(fp);
  return 1;
}
void free_BMP_image(BMP_image *image)
{
  free(image->data);
  free(image);
}
BMP_image *convert_24_to_16_BMP_image(BMP_image *image)
{
  BMP_image *New_16_Image = malloc(sizeof(*New_16_Image));
  if (New_16_Image == NULL)
  {
    fprintf(stderr, "Can not allocate memory to new iamge\n");
    return NULL;
  }

  New_16_Image->header = image->header;
  New_16_Image->header.bits = 16;
  int width = New_16_Image->header.width;
  int height = New_16_Image->header.height;
  int byte_per_row = width * 2; // without the padding byte
  int act_byte_per_row = (byte_per_row + 3) & ~3;
  int act_byte_per_row_24 = (image->header.width * 3 + 3) & ~3;
  New_16_Image->header.imagesize = act_byte_per_row * height;
  New_16_Image->header.size = New_16_Image->header.imagesize + New_16_Image->header.offset;
  New_16_Image->data = calloc(New_16_Image->header.imagesize, sizeof(*(New_16_Image->data)));
  if (New_16_Image->data == NULL)
  {
    fprintf(stderr, "Can't allocate memory to the new data\n");
    return NULL;
  }

  for (int i = 0; i < height; i++)
  {
    int src_row_offset = i * act_byte_per_row_24;
    int dst_row_offset = i * act_byte_per_row;

    for (int j = 0; j < width; j++)
    {
      int offset_24 = src_row_offset + j * 3;
      unsigned char red = image->data[offset_24 + 2];
      unsigned char green = image->data[offset_24 + 1];
      unsigned char blue = image->data[offset_24];

      unsigned short red_5 = (red >> 3) & 0x1F;
      unsigned short green_5 = (green >> 3) & 0x1F;
      unsigned short blue_5 = (blue >> 3) & 0x1F;

      unsigned short pixel_16 = (red_5 << 10) | (green_5 << 5) | blue_5;

      New_16_Image->data[dst_row_offset + j * 2 + 1] = pixel_16 >> 8;
      New_16_Image->data[dst_row_offset + j * 2] = pixel_16 & 0xFF;

      // fprintf(stderr, "Original R=%d G=%d B=%d => R5=%d G5=%d B5=%d => Pixel_16=%04x\n",
      //         red, green, blue, red_5, green_5, blue_5, pixel_16);
    }
  }
  return New_16_Image;
}
BMP_image *convert_16_to_24_BMP_image(BMP_image *image)
{
  BMP_image *New_24_Image = malloc(sizeof(*New_24_Image));
  if (New_24_Image == NULL)
  {
    fprintf(stderr, "Can not allocate memory to new iamge\n");
    return NULL;
  }

  New_24_Image->header = image->header;
  New_24_Image->header.bits = 24;
  int width = New_24_Image->header.width;
  int height = New_24_Image->header.height;
  int byte_per_row = width * 3;
  int act_byte_per_row = (byte_per_row + 3) & ~3;
  // int act_byte_per_row_16 = (image->header.width * 2 + 3) & ~3;
  New_24_Image->header.imagesize = act_byte_per_row * height;
  New_24_Image->header.size = New_24_Image->header.imagesize + New_24_Image->header.offset;
  New_24_Image->data = calloc(New_24_Image->header.imagesize, sizeof(*(New_24_Image->data)));
  if (New_24_Image->data == NULL)
  {
    fprintf(stderr, "Can't allocate memory to the new data\n");
    return NULL;
  }

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      int offset_16 = i * width * 2 + j * 2;

      unsigned short pixel_16 = image->data[offset_16] | (image->data[offset_16 + 1] << 8);
      unsigned short red = (pixel_16 >> 10) & 0x1F;
      unsigned short green = (pixel_16 >> 5) & 0x1F;
      unsigned short blue = pixel_16 & 0x1F;

      unsigned char red_8 = red * 255 / 31;
      unsigned char green_8 = green * 255 / 31;
      unsigned char blue_8 = blue * 255 / 31;

      New_24_Image->data[j * 3 + i * act_byte_per_row] = blue_8;
      New_24_Image->data[j * 3 + i * act_byte_per_row + 1] = green_8;
      New_24_Image->data[j * 3 + i * act_byte_per_row + 2] = red_8;
    }
  }
  return New_24_Image;
}
BMP_image *convert_24_to_16_BMP_image_with_dithering(BMP_image *image)
{
  BMP_image *new_image = malloc(sizeof(*new_image));

  if (new_image == NULL)
    return NULL;
  // assign header to new image
  new_image->header = image->header;
  new_image->header.bits = 24;
  // calculate the size with padding
  int act_byte_per_row = (image->header.width * 3 + 3) & ~3;
  new_image->header.imagesize = act_byte_per_row * new_image->header.height;
  new_image->header.size = new_image->header.imagesize + new_image->header.offset;

  new_image->data = calloc(new_image->header.imagesize, sizeof(*(new_image->data)));
  if (new_image->data == NULL)
    return NULL;
  double *new_image_data = malloc(sizeof(*new_image_data) * image->header.imagesize);

  // for loop to fill in new image data from image->data
  for (int i = 0; i < image->header.imagesize; i++)
  {
    new_image_data[i] = image->data[i];
  }

  for (int y = image->header.height - 1; y >= 0; y--)
  {
    for (int x = 0; x < image->header.width; x++)
    {
      for (int z = 0; z < 3; z++)
      {
        double value_24 = new_image_data[y * act_byte_per_row + x * 3 + z];
        short value_16 = value_24 / 8;
        short value_equ_24 = (value_16 * 255) / 31;
        if (value_equ_24 < 0)
          value_equ_24 = 0;
        else if (value_equ_24 > 255)
          value_equ_24 = 255;
        double error = value_24 - value_equ_24;
        new_image->data[y * act_byte_per_row + x * 3 + z] = value_equ_24;
        if (x < image->header.width - 1)
          new_image_data[y * act_byte_per_row + (1 + x) * 3 + z] += error * 7 / 16;
        if (y > 1)
        {
          new_image_data[(y - 1) * act_byte_per_row + (x - 1) * 3 + z] += error * 3 / 16;
          new_image_data[(y - 1) * act_byte_per_row + x * 3 + z] += error * 5 / 16;
        }
        if (y > 1 && x < image->header.width - 1)
          new_image_data[(y - 1) * act_byte_per_row + (1 + x) * 3 + z] += error * 1 / 16;
      }
    }
  }
  convert_24_to_16_BMP_image(new_image);
  return new_image;
}
