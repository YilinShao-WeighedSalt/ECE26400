// can you write a program that prints each integer partitioning solution
// in non-increasing order

#include <stdio.h>
#include <stdlib.h>

static void print_array(int *array, int size)
{
   int newsize = size - 1;
   for (int i = 0; i < newsize; i++) 
      fprintf(stdout, "%d + ", array[i]);
   fprintf(stdout, "%d\n", array[newsize]);
}

static void int_partition_helper(int n, int *array, int idx, int lower_bound, int *count)
{
   if (n == 0) {
      fprintf(stdout, "%d: ", *count);
      print_array(array, idx);
      (*count)++;
      return;
   }
   for (int i = lower_bound; i <= n; i++) {
      array[idx] = i;
      int_partition_helper(n - i, array, idx+1, i, count);
   }
}

static void int_partition(int n)
{
   int count = 0;
   int *array = malloc(sizeof(*array) * n);
   if (array == NULL) {
      return;
   }
   int_partition_helper(n, array, 0, 1, &count);
   free(array);
}

int main(int argc, char **argv)
{
   if (argc != 2) {
      fprintf(stderr, "expect a number\n");
      return EXIT_FAILURE;
   }

   // no longer doing vigorous check with strtol
   // atoi converts a string into a base 10 integer

   int n = atoi(argv[1]);
   if (n < 1) {
      fprintf(stderr, "require >= 1 to partition\n");
      return EXIT_FAILURE;
   }
   int_partition(n);
   return EXIT_SUCCESS;
}
