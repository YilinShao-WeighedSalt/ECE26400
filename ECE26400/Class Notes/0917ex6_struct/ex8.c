#include <stdio.h>
#include <stdlib.h>

// static void print_non_zero_array(int *array, int count);
// static void count_characters(FILE *fp, int *array);

int main(int argc, char **argv)
{
   if (argc != 2) {
      fprintf(stderr, "expect 1 filename\n");
      return EXIT_FAILURE;
   }
   FILE *ifp = fopen(argv[1], "r");
   if (ifp == NULL) {
      fprintf(stderr, "input file cannot be opened\n");
      return EXIT_FAILURE;
   }
   int *array = calloc(256, sizeof(*array));
   if (array == NULL) {
      fprintf(stderr, "memory allocation problem\n");
      return EXIT_FAILURE;
   }






   free(array);
   fclose(ifp);
   return EXIT_SUCCESS;
}

// print only non-zero entries
// print also the total count
//
/*
static void print_non_zero_array(int *array, int count)
{
   int i;
   int total_count = 0;
   for (i = 0; i < count; i++) {
      if (array[i] > 0) {
         fprintf(stdout, "%c: %d\n", i, array[i]);
         total_count += array[i];
      }
   }
   fprintf(stdout, "total count: %d\n", total_count);
}
*/

// assume an array of 256 int's for counting
// assume all entries start at 0
//
// static void count_characters(FILE *fp, int *array)
// {
// }
