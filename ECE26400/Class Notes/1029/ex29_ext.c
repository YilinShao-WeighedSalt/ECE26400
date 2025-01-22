// read in from a binary file
// solve and write to a text file
// impose a 2-D array structure on a 1-D array
// use sentinels in the solution
// use bit-fields for conversion

#include <stdio.h>
#include <stdlib.h>

typedef struct _byte {
   signed char bit0: 1, bit1: 1, bit2: 1, bit3: 1, bit4: 1, bit5: 1, bit6: 1, bit7: 1;
} byte;

typedef struct _row_col {
   int row;
   int col;
} row_col;

typedef struct _maze_header {
   row_col dimensions;
   row_col entry;
   row_col exit;
} maze_header;

typedef struct _maze {
   maze_header header;
   char *array;
} maze;

static void convert_bytes(char *array, byte *char_byte)
{
   char char_byte_array[8] = { char_byte->bit7, char_byte->bit6, char_byte->bit5, char_byte->bit4,
                               char_byte->bit3, char_byte->bit2, char_byte->bit1, char_byte->bit0 };
   int i;
   for (i = 0; i < 8; i++) {
      array[i] = char_byte_array[i] == -1 ? '*' : ' ';
   }
}

static void destroy_maze(maze *my_maze)
{
   if (my_maze) {
      free(my_maze->array);
      free(my_maze);
   }
}

// set up maze structure from a file

static maze *read_maze_from_file(char *filename)
{
   FILE *fp = fopen(filename, "r");
   if (fp == NULL) {
      return NULL;
   }
   maze_header header;
   if (fread(&header, sizeof(header), 1, fp) != 1) {
      fclose(fp);
      return NULL;
   }
   int bytes_per_row = (header.dimensions.col + 31)/32 * 4;
   int data_per_row = (header.dimensions.col + 7)/8;
   unsigned char (*byte_array)[bytes_per_row] = malloc(sizeof(*byte_array) * header.dimensions.row);
   if (byte_array == NULL) {
      fclose(fp);
      return NULL;
   }
   if (fread(byte_array, sizeof(*byte_array), header.dimensions.row, fp) != header.dimensions.row) {
      free(byte_array);
      fclose(fp);
      return NULL;
   }
   fclose(fp);

   char (*array)[header.dimensions.col] = malloc(sizeof(*array) * (header.dimensions.row+2));
   if (array == NULL) {
      free(byte_array);
      return NULL;
   }

   maze *my_maze = malloc(sizeof(*my_maze));
   if (my_maze == NULL) {
      fprintf(stderr, "can't allocate maze memory\n");
      free(byte_array);
      free(array);
      return NULL;
   }
   *my_maze = (maze) { .header = header, .array = (char *)&(array[0]) };
   
   int col;
   int bottom_row = header.dimensions.row + 1;
   for (col = 0; col < header.dimensions.col; col++) {
      array[0][col] = array[bottom_row][col] = '*';
   }

   int i;
   for (i = 0; i < header.dimensions.row; i++) {
      int j;
      for (j = 0; j < data_per_row; j++) {
         char char_byte_array[8];
         convert_bytes(char_byte_array, (byte *)&(byte_array[i][j]));
         int k;
         for (k = 0; k < 8; k++) {
            col = j * 8 + k;
            if (col < header.dimensions.col) {  // real data
               array[i+1][col] = char_byte_array[k];
            } else {
               break;
            } 
         }
      }
   }
   free(byte_array);
   return my_maze; 
} 

static int print_maze_to_file(char *filename, maze *my_maze)
{
   FILE *fp = fopen(filename, "w");
   if (fp == NULL) {
      return 0;
   }
   fprintf(fp, "%d,%d\n", my_maze->header.dimensions.row, my_maze->header.dimensions.col);
   fprintf(fp, "%d,%d\n", my_maze->header.entry.row, my_maze->header.entry.col);
   fprintf(fp, "%d,%d\n", my_maze->header.exit.row, my_maze->header.exit.col);
   char (*array)[my_maze->header.dimensions.col] = (char (*)[my_maze->header.dimensions.col])my_maze->array;
   int i, j;
   for (i = 0; i < my_maze->header.dimensions.row; i++) {
      for (j = 0; j < my_maze->header.dimensions.col; j++) {
         fputc(array[i+1][j], fp);
      }
      fputc('\n', fp);
   }
   fclose(fp);
   return 1;
}

static int valid_space(char *arr, row_col coord, int col)
{
   char (*array)[col] = (char (*)[col])arr;
   if (array[coord.row][coord.col] == ' ') {
      return 1;
   }
   return 0;
}

static int solve_maze_helper(char *arr, row_col exit, row_col curr, int col) 
{
   char (*array)[col] = (char (*)[col])arr;
   if (exit.row == curr.row && exit.col == curr.col) {
      array[curr.row][curr.col] = 'p';
      return 1;
   }
   if (!valid_space(arr, curr, col)) {
      return 0;
   }
   array[curr.row][curr.col] = 'v'; // mark it so that recursive call solve a smaller problem

   // next stores the next position to explore, down, up, right, left

   row_col next[4] = {{ .row = curr.row+1, .col = curr.col }, { .row = curr.row-1, .col = curr.col },
                      { .row = curr.row, .col = curr.col+1 }, { .row = curr.row, .col = curr.col-1 }};
   int i = 0;
   for (i = 0; i < 4; i++) {
      if (solve_maze_helper(arr, exit, next[i], col) == 1) {
         array[curr.row][curr.col] = 'p';
         return 1;
      }
   }
   return 0;
}

static int solve_maze(maze *my_maze)
{
   row_col actual_exit = { .row = my_maze->header.exit.row + 1, .col = my_maze->header.exit.col };
   row_col actual_entry = { .row = my_maze->header.entry.row + 1, .col = my_maze->header.entry.col };
   int col = my_maze->header.dimensions.col;
   
   if (valid_space(my_maze->array, actual_exit, col) && valid_space(my_maze->array, actual_entry, col)) {
      return solve_maze_helper(my_maze->array, actual_exit, actual_entry, col);
   }
   return 0; 
}

int main(int argc, char **argv)
{
   if (argc != 3) {
      fprintf(stderr, "expect j arguments\n");
      return EXIT_FAILURE;
   }
   maze *my_maze = read_maze_from_file(argv[1]);
   if (my_maze == NULL) {
      fprintf(stderr, "can't read\n");
      return EXIT_FAILURE;
   }
   int status = solve_maze(my_maze);
   int w_status = print_maze_to_file(argv[2], my_maze);

   destroy_maze(my_maze);
   if (status && w_status) 
      return EXIT_SUCCESS;
   return EXIT_FAILURE;
}

