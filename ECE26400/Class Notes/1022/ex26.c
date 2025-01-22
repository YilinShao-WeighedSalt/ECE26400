// read from a "textfile" using fscanf
// write to a binary file
//
#include <stdio.h>
#include <stdlib.h>

typedef struct _row_col
{
   int row;
   int col;
} row_col;

typedef struct _maze_header
{
   row_col dimensions;
   row_col entry;
   row_col exit;
} maze_header;

typedef struct _maze
{
   maze_header header;
   char **array;
} maze;

static void destroy_array(char **array, int rows)
{
   if (array)
   {
      int i;
      for (i = 0; i < rows; i++)
      {
         free(array[i]);
      }
      free(array);
   }
}

// include top and bottom boundary rows
static char **allocate_array_with_boundary(row_col dimensions)
{
   int actual_rows = dimensions.row + 2;
   char **array = malloc(sizeof(*array) * actual_rows);
   if (array == NULL)
      return NULL;
   int i;
   for (i = 0; i < actual_rows; i++)
   {
      array[i] = malloc(sizeof(*array[i]) * dimensions.col);
      if (array[i] == NULL)
      {
         destroy_array(array, i);
         return NULL;
      }
   }
   return array;
}
static void destroy_maze(maze *my_maze)
{
   if (my_maze)
   {
      destroy_array(my_maze->array, my_maze->header.dimensions.row + 2);
      free(my_maze);
   }
}
static int read_header_from_file(FILE *fp, maze_header *header)
{
   if (fscanf(fp, "%d,%d\n", &(header->dimensions.row), &(header->dimensions.col)) != 2)
   {
      fprintf(stderr, "can't read header\n");
      return 0;
   }
   if (fscanf(fp, "%d,%d\n", &(header->entry.row), &(header->entry.col)) != 2)
   {
      fprintf(stderr, "can't read header\n");
      return 0;
   }
   if (fscanf(fp, "%d,%d\n", &(header->exit.row), &(header->exit.col)) != 2)
   {
      fprintf(stderr, "can't read header\n");
      return 0;
   }
   return 1;
}

// set up maze structure from a file
static maze *read_maze_from_file(char *filename)
{
   FILE *fp = fopen(filename, "r");
   if (fp == NULL)
   {
      return NULL;
   }
   maze_header header;
   int status = read_header_from_file(fp, &header);
   if (status == 0)
   {
      fclose(fp);
      return NULL;
   }
   char **array = allocate_array_with_boundary(header.dimensions);
   if (array == NULL)
   {
      fprintf(stderr, "can't allocate array memory\n");
      fclose(fp);
      return NULL;
   }
   maze *my_maze = malloc(sizeof(*my_maze));
   if (my_maze == NULL)
   {
      fprintf(stderr, "can't allocate maze memory\n");
      destroy_array(array, header.dimensions.row + 2);
      fclose(fp);
      return NULL;
   }
   *my_maze = (maze){.header = header, .array = array};
   int col;
   int bottom_row = header.dimensions.row + 1;
   for (col = 0; col < header.dimensions.col; col++)
   {
      array[0][col] = array[bottom_row][col] = '*';
   }
   int i;
   for (i = 1; i <= header.dimensions.row; i++)
   {
      if (fread(array[i], sizeof(*(array[i])), header.dimensions.col, fp) != header.dimensions.col)
      {
         destroy_maze(my_maze);
         fclose(fp);
         return NULL;
      }
      if (fgetc(fp) != '\n')
      {
         destroy_maze(my_maze);
         fclose(fp);
         return NULL;
      }
   }
   fclose(fp);
   return my_maze;
}
static int write_maze_to_file(char *filename, maze *my_maze)
{
   FILE *fp = fopen(filename, "w");
   if (fp == NULL)
   {
      return 0;
   }
   if (fwrite(&(my_maze->header), sizeof(my_maze->header), 1, fp) != 1)
   {
      fclose(fp);
      return 0;
   }
   // use a bit to represent each location
   // each row must be a multple of 4 bytes, padding bit must be 1
   // for each byte, read from MSB to LSB, as in how we read the maze file
   // in each row, the padding bytes are of higher index
   // for each byte with padding bits, the bits are of lower significance
   int bytes_per_row = (my_maze->header.dimensions.col + 31) / 32 * 4;
   int data_per_row = (my_maze->header.dimensions.col + 7) / 8;
   int total_bytes = bytes_per_row * my_maze->header.dimensions.row;
   unsigned char *byte_array = malloc(sizeof(*byte_array) * total_bytes);
   if (byte_array == NULL)
   {
      fclose(fp);
      return 0;
   }
   int i;
   for (i = 0; i < my_maze->header.dimensions.row; i++)
   {
      int j;
      for (j = 0; j < data_per_row; j++)
      {
         unsigned char mask = 0x80;
         byte_array[i * bytes_per_row + j] = 0; // initialize to 0
         int k;
         for (k = 0; k < 8; k++)
         {
            int col = j * 8 + k;
            if (col < my_maze->header.dimensions.col)
            { // real data
               if (my_maze->array[i + 1][col] == '*')
               {
                  byte_array[i * bytes_per_row + j] |= mask;
               }
            }
            else
            {
               byte_array[i * bytes_per_row + j] |= mask;
            }
            mask >>= 1;
         }
      }
      // handle the padding bits in the last byte in a row
      for (; j < bytes_per_row; j++)
      { // handle the padding bytes
         byte_array[i * bytes_per_row + j] = 0xff;
      }
   }
   int status = fwrite(byte_array, sizeof(*byte_array), total_bytes, fp) == total_bytes;
   free(byte_array);
   fclose(fp);
   return status;
}
int main(int argc, char **argv)
{
   if (argc != 3)
   {
      fprintf(stderr, "expect 2 arguments\n");
      return EXIT_FAILURE;
   }
   maze *my_maze = read_maze_from_file(argv[1]);
   if (my_maze == NULL)
   {
      fprintf(stderr, "can't read\n");
      return EXIT_FAILURE;
   }
   int w_status = write_maze_to_file(argv[2], my_maze);
   destroy_maze(my_maze);
   if (w_status)
      return EXIT_SUCCESS;
   return EXIT_FAILURE;
}
