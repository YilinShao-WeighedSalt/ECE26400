#include <stdlib.h>
#include <stdio.h>

typedef struct _arrstruct {
   int array[5];
   int size;
} arrstruct;

static void inc_array(int *array, int size, int inc)
{
   for (int i = 0; i < size; i++) 
      array[i] += inc;
}

static arrstruct inc1_arrstruct(arrstruct arrs)
{
   inc_array(&(arrs.array[0]), arrs.size, 1);
   return arrs;
}

int main(int argc, char **argv)
{
   arrstruct arrs = { .array = { 0x30, 0x31, 0x32, 0x34, 0x35 }, .size = 5 };

   arrstruct inc_arrs = inc1_arrstruct(arrs);

   return EXIT_SUCCESS;
}

/*
static void print_array(int *array, int size)
{
   for (int i = 0; i < size; i++) 
      fprintf(stdout, "%d ", array[i]);
   fprintf(stdout, "\n");
}

static void print_arrstruct(arrstruct arrs)
{
   print_array(&(arrs.array[0]), arrs.size);
}
*/

/*
   fprintf(stdout, "Print arrs\n");
   print_arrstruct(arrs);

   fprintf(stdout, "Print inc_arrs\n");
   print_arrstruct(inc_arrs);
*/
/*
   fprintf(stdout, "Print arrs\n");
   print_arrstruct(arrs);
 
   fprintf(stdout, "call a function to \"increment\" arrs, store result in inc_arrs\n");
*/
