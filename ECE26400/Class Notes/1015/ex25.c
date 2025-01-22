// read in a maze using fscanf (because the maze file is human readable
// solve the maze using sentinels
// write to an output using fprintf

#include <stdio.h>
#include <stdlib.h>

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
   char **array;
} maze;

static void destroy_array(char **array, int rows)
{
   if (array) {
      int i; 
      for (i = 0; i < rows; i++) {
         free(array[i]);
      }
      free(array);
   }
}

// include top and bottom boundary rows
//
static char **allocate_array_with_boundary(row_col dimensions)
{
   int actual_rows = dimensions.row + 2;
   char **array = malloc(sizeof(*array) * actual_rows);
   if (array == NULL) 
      return NULL;
   int i;
   for (i = 0; i < actual_rows; i++) {
      array[i] = malloc(sizeof(*(array[i])) * dimensions.col);
      if (array[i] == NULL) {
         destroy_array(array, i);
         return NULL;
      }
   }
   return array;
}

static void destroy_maze(maze *my_maze)
{
   if (my_maze) {
      destroy_array(my_maze->array, my_maze->header.dimensions.row+2);
      free(my_maze);
   }
}

static int read_header_from_file(FILE *fp, maze_header *header)
{
   if (fscanf(fp, "%d,%d\n", &(header->dimensions.row), &(header->dimensions.col)) != 2) {
      fprintf(stderr, "can't read header\n");
      return 0;
   }
   if (fscanf(fp, "%d,%d\n", &(header->entry.row), &(header->entry.col)) != 2) {
      fprintf(stderr, "can't read header\n");
      return 0;
   }
   if (fscanf(fp, "%d,%d\n", &(header->exit.row), &(header->exit.col)) != 2) {
      fprintf(stderr, "can't read header\n");
      return 0;
   }
   return 1;
}

// set up maze structure from a file
// 
static maze *read_maze_from_file(char *filename)
{
   FILE *fp = fopen(filename, "r");
   if (fp == NULL) {
      return NULL;
   }
   maze_header header;
   int status = read_header_from_file(fp, &header);
   if (status == 0) {
      fclose(fp);
      return NULL;
   }
   char **array = allocate_array_with_boundary(header.dimensions);
   if (array == NULL) {
      fprintf(stderr, "can't allocate array memory\n");
      fclose(fp);
      return NULL;
   }
   maze *my_maze = malloc(sizeof(*my_maze));
   if (my_maze == NULL) {
      fprintf(stderr, "can't allocate maze memory\n");
      destroy_array(array, header.dimensions.row + 2);
      fclose(fp);
      return NULL;
   }
   *my_maze = (maze) { .header = header, .array = array };
   
   int col;
   int bottom_row = header.dimensions.row + 1;
   for (col = 0; col < header.dimensions.col; col++) {
      array[0][col] = array[bottom_row][col] = '*';
   }

   int i;
   for (i = 1; i <= header.dimensions.row; i++) {
      if (fread(array[i], sizeof(*(array[i])), header.dimensions.col, fp) == header.dimensions.col) {
         if (fgetc(fp) == '\n') {
            continue;
         }
      }
      destroy_maze(my_maze);
      fclose(fp);
      return NULL;
   }
   fclose(fp); 
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
   int i; // , j;
   for (i = 1; i <= my_maze->header.dimensions.row; i++) {
      if (fwrite(my_maze->array[i], sizeof(*(my_maze->array[i])), my_maze->header.dimensions.col, fp) == my_maze->header.dimensions.col) {
      // for (j = 0; j < my_maze->header.dimensions.col; j++) {
      //   fputc(my_maze->array[i][j], fp);
      // }
         fputc('\n', fp);
      } else {
         fclose(fp);
         return 0;
      }
   }
   fclose(fp);
   return 1;
}

static int valid_space(char **array, row_col coord)
{
   if (array[coord.row][coord.col] == ' ') {
      return 1;
   }
   return 0;
}

static int solve_maze_helper(char **array, row_col exit, row_col curr) 
{
   if (!valid_space(array, curr)) {
      return 0;
   }
   if (exit.row == curr.row && exit.col == curr.col) {
      array[curr.row][curr.col] = 'p';
      return 1;
   }
   array[curr.row][curr.col] = 'v'; // mark it so that recursive call solve a smaller problem

   // next stores the next position to explore, down, up, right, left

   row_col next[4] = {{ .row = curr.row+1, .col = curr.col }, { .row = curr.row-1, .col = curr.col },
                      { .row = curr.row, .col = curr.col+1 }, { .row = curr.row, .col = curr.col-1 }};
   int i = 0;
   for (i = 0; i < 4; i++) {
      if (solve_maze_helper(array, exit, next[i]) == 1) {
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
   
   if (valid_space(my_maze->array, actual_exit) && valid_space(my_maze->array, actual_entry)) {
      return solve_maze_helper(my_maze->array, actual_exit, actual_entry);
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
