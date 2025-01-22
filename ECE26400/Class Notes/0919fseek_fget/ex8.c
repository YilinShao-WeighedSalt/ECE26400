#include <stdio.h>
#include <stdlib.h>

// print only non-zero entries
// print also the total count
//
static void print_non_zero_array(int *array, int count)
{
   int i;
   int total_count = 0;
   for (i = 0; i < count; i++)
   {
      if (array[i] > 0)
      {
         fprintf(stdout, "%c,%hhu,%hhd: %d\n", i, i, i, array[i]);
         total_count += array[i];
      }
   }
   fprintf(stdout, "total count: %d\n", total_count);
}

// assume an array of 256 int's for counting
// assume all entries start at 0
//
static void count_characters(FILE *fp, int *array)
{
   int ch;
   while ((ch = fgetc(fp)) != EOF)
   {
      array[ch] += 1;
   }
}

int main(int argc, char **argv)
{
   if (argc != 2)
   {
      fprintf(stderr, "expect 1 filename\n");
      return EXIT_FAILURE;
   }
   FILE *ifp = fopen(argv[1], "r");
   if (ifp == NULL)
   {
      fprintf(stderr, "input file cannot be opened\n");
      return EXIT_FAILURE;
   }
   int *array = calloc(256, sizeof(*array));
   if (array == NULL)
   {
      fprintf(stderr, "memory allocation problem\n");
      fclose(ifp);
      return EXIT_FAILURE;
   }

   // count_characters(ifp, array);
   // print_non_zero_array(array, 256);

   // file position can be moved to a location beyond the end of file

   fprintf(stdout, "file position index: %ld\n", ftell(ifp));
   int c = fgetc(ifp);
   if (c == EOF)
   {
      fprintf(stdout, "still correct in that it is EOF\n");
   }
   fprintf(stdout, "file position index: %ld\n", ftell(ifp));
   fseek(ifp, 3L, SEEK_END);
   fprintf(stdout, "file position index: %ld\n", ftell(ifp));
   c = fgetc(ifp);
   if (c == EOF)
   {
      fprintf(stdout, "still correct in that it is EOF\n");
   }
   fprintf(stdout, "file position index: %ld\n", ftell(ifp));

   // file position cannot be moved to a location before the beginning of file
   fseek(ifp, 1L, SEEK_CUR);
   fprintf(stdout, "file position index when moved 1 from 65:%ld\n", ftell(ifp));
   fseek(ifp, 1L, SEEK_SET);
   fprintf(stdout, "file position index: %ld\n", ftell(ifp));
   fseek(ifp, -2L, SEEK_CUR);
   fprintf(stdout, "file position index: %ld\n", ftell(ifp));
   fseek(ifp, -1L, SEEK_CUR);
   fprintf(stdout, "file position index: %ld\n", ftell(ifp));

   free(array);
   fclose(ifp);
   return EXIT_SUCCESS;
}
