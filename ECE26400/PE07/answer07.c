#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "answer07.h"

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

  if (header->size != exp_filesize)
    return false;
  if (header->imagesize != exp_image_size)
    return false;
  return true;
}
BMP_image *read_BMP_image(char *filename)
{
  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
    return NULL;
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
  FILE *fp = fopen(filename, "w");
  if (fp == NULL)
  {
    fprintf(stderr, "Failed opening file for writing\n");
    fclose(fp);
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
BMP_image *reflect_BMP_image(BMP_image *image, bool hrefl, bool vrefl)
{
  BMP_image *reflect_image = malloc(sizeof(*reflect_image));
  if (reflect_image == NULL)
    return NULL;

  reflect_image->header = image->header;
  reflect_image->data = calloc(image->header.imagesize, sizeof(*(image->data)));

  if (reflect_image->data == NULL)
  {
    free(reflect_image);
    return NULL;
  }
  int bytes_per_pixel = image->header.bits / 8;
  int width = image->header.width;
  int height = image->header.height;
  int pixel_data_size = width * bytes_per_pixel;
  int row_size = (width * bytes_per_pixel + 3) & ~3;

  unsigned char **temp;
  // copy the data to the reflected image
  // for (int i = 0; i < height; i++)
  // {
  //   unsigned char *src_row = image->data + i * row_size;
  //   unsigned char *dest_row = reflect_image->data + i * row_size;
  //   memcpy(dest_row, src_row, pixel_data_size); // Copy only pixel data, leaving padding bytes as zero
  // }

  // // Horizontal reflection: swap pixels within each row
  // if (hrefl)
  // {
  //   for (int i = 0; i < height; i++)
  //   {
  //     unsigned char *row = reflect_image->data + i * row_size;
  //     for (int j = 0; j < width / 2; j++)
  //     {
  //       unsigned char temp[bytes_per_pixel];
  //       memcpy(temp, &row[j * bytes_per_pixel], bytes_per_pixel);
  //       memcpy(&row[j * bytes_per_pixel], &row[(width - 1 - j) * bytes_per_pixel], bytes_per_pixel);
  //       memcpy(&row[(width - 1 - j) * bytes_per_pixel], temp, bytes_per_pixel);
  //     }
  //   }
  // }

  // // Vertical reflection: swap rows
  // if (vrefl)
  // {
  //   for (int i = 0; i < height / 2; i++)
  //   {
  //     unsigned char *top_row = reflect_image->data + i * row_size;
  //     unsigned char *bottom_row = reflect_image->data + (height - 1 - i) * row_size;

  //     // Swap the entire rows
  //     unsigned char temp_row[row_size];
  //     memcpy(temp_row, top_row, row_size);
  //     memcpy(top_row, bottom_row, row_size);
  //     memcpy(bottom_row, temp_row, row_size);
  //   }
  // }

  return reflect_image;
}