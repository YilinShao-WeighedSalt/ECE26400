#include <stdio.h>
#include <stdlib.h>

void print_3d_blocks(int *array, int x_dim, int y_dim, int z_dim)
{
   int (*ptr)[y_dim][z_dim] = (int (*)[y_dim][z_dim])&(array[0]);
   // what is the sizeof(ptr[0]);
   // what is the sizeof(ptr[0][0]);
   // what is the sizeof(ptr[0][0][0]);
   fprintf(stdout, "sizes: %zd %zd %zd\n\n", sizeof(ptr[0]), sizeof(ptr[0][0]), sizeof(ptr[0][0][0]));
  
   int i;
   for (i = 0; i < x_dim; i++) {
      int j;
      for (j = y_dim - 1; j >= 0; j--) {
         int k;
         for (k = 0; k < z_dim; k++) {
            fprintf(stdout, "%d ", ptr[i][j][k]);
         }
         fprintf(stdout, "\n");
      }
      fprintf(stdout, "\n");
   }
}

// int *arrayptr[3][2] vs int (*array)[3][2]
// type of arrayptr: ([3][2] block of (int *)), or a block of [3][2] (int *)
// type of array: address pointing to a block of [3][2] int, int (*)[3][2]

// void print_true_3d_blocks(int (*array)[3][2]) 
// void print_true_3d_blocks(int array[][3][2]) // array[] is treated as (*array)
void print_true_3d_blocks(int array[2][3][2])  // 2 in the left most [] is ignored
{
   for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 3; j++) {
         for (int k = 0; k < 2; k++) {
            fprintf(stdout, "%d ", array[i][j][k]);
         }
         fprintf(stdout, "\n");
      }
      fprintf(stdout, "\n");
   }
}

void func(int *(*ptr)[2])
{
   return;
}

// int main(int argc, char *argv[])
int main(int argc, char **argv)
{
   int array3d[2][3][2] = { { {  0,  2 }, {  4,  6 }, {  8, 10 } },
                            { { 12, 14 }, { 16, 18 }, { 20, 22 } } };

   fprintf(stdout, "sizes: %zd %zd %zd %zd\n", sizeof(array3d), sizeof(array3d[0]), 
                                        sizeof(array3d[0][0]), sizeof(array3d[0][0][0]));
   fprintf(stdout, "addresses of array3d, array3d[0], array3d[1], array3d[1][1], array3d[1][1][1]\n");
   fprintf(stdout, "%p %p %p %p %p\n", (void *)&(array3d), (void *)&(array3d[0]), (void *)&(array3d[1]), 
                                    (void *)&(array3d[1][1]), (void *)&(array3d[1][1][1]));
   fprintf(stdout, "%p %p %p %p %p\n", (void *)&(array3d), (void *)&(array3d[0]), (void *)(&(array3d[0])+1), 
                                    (void *)(&(array3d[1][0])+1), (void *)(&(array3d[1][1][0])+1));
   fprintf(stdout, "\n");

   // array3d[0] is of type int [3][2]
   // therefore, &array3d[0] is of type int (*)[3][2]

   fprintf(stdout, "printing 3d block:\n");
   print_true_3d_blocks(&(array3d[0]));
   
   // array3d is treated as int (*)[3][2] by compiler when it is passed as a parameter
   // to a function

   fprintf(stdout, "printing 3d block again:\n");
   print_true_3d_blocks(array3d);

   // compilation error if the following statement is uncommented
   // passing in address of array3d, array3d is of type int [2][3][2]
   // therefore &array3d is of type int (*)[2][3][2]

   // print_true_3d_blocks(&array3d); 

   int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

   fprintf(stdout, "printing 1d block as [2][3][2]:\n");
   print_3d_blocks(&(array[0]), 2, 3, 2);

   // array is treated as int (*) by compiler when it is passed as a parameter to a function

   fprintf(stdout, "printing 1d block as [2][2][3]:\n");
   print_3d_blocks(array, 2, 2, 3);

   int *addr = malloc(sizeof(*addr) * 12);
   if (addr != NULL) {
      for (int i = 0; i < 12; i++)
         addr[i] = i;

      fprintf(stdout, "printing malloc'd 1d block as [3][2][2]:\n");
      print_3d_blocks(addr, 3, 2, 2);

      free(addr);
   }

   return EXIT_SUCCESS;
}
