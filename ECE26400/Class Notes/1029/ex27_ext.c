#include <stdio.h>
#include <stdlib.h>

// int main(int argc, char *argv[])
int main(int argc, char **argv)
{
   int array[17];  // integer array, but we are going to access the bytes individually

   // row-by-col items
   int row = 4;
   int col = 3;

   // bytes per time
   int bytes_per_item = 5;
   int padding = 2;

   int actual_per_row = col * bytes_per_item;  // 3 * 5, informative
   int bytes_per_row = actual_per_row + padding;  // 3 * 5 + 2 = 17
   int total_bytes = row * bytes_per_row; // 17 * 4

   // treat the address of the first int in array as an address of char

   char *carray = (char *)&(array[0]);

   // first way of accessing the "3D" array
   // we initialize the array

   int index = 0;
   int i, j, k;
   for (i = 0; i < row; i++) {
      for (j = 0; j < col; j++) {
         for (k = 0; k < bytes_per_item; k++) {
            carray[index] = index + '0';
            index++;
         }
      }
      for (j = actual_per_row; j < bytes_per_row; j++) {
         carray[index] = '\0';
         index++;
      }
   }

   // second way of accessing the "3D" array
   // we print the array

   char (*carray2d)[bytes_per_row] = (char (*)[bytes_per_row])&(array[0]);
   for (i = 0; i < row; i++) {
      char (*row2d)[bytes_per_item] = (char (*)[bytes_per_item])&(carray2d[i]);
      for (j = 0; j < col; j++) {
         for (k = 0; k < bytes_per_item; k++) {
            fprintf(stdout, "%c", row2d[j][k]);
         }
         fprintf(stdout, ",");
      }
      for (j = actual_per_row; j < bytes_per_row; j++) {
         fprintf(stdout, "%hhd", carray2d[i][j]);
      }
      fprintf(stdout, "\n");
   }
   
   fprintf(stdout, "\n");

   for (i = 0; i < 17; i++) {
      fprintf(stdout, "%d ", array[i]);
   }
   fprintf(stdout, "\n\n");
   
   // third way of accessing the "3D" array
   // we update the array

   for (i = 0; i < row; i++) {
      for (j = 0; j < col; j++) {
         for (k = 0; k < bytes_per_item; k++) {
            carray[i * bytes_per_row + j * bytes_per_item + k] += 1;
         }
      }
      for (j = actual_per_row; j < bytes_per_row; j++) {
         carray[i * bytes_per_row + j] = '\0' + 2;
         index++;
      }
   }

   // we print the array again, using the second way

   for (i = 0; i < row; i++) {
      char (*row2d)[bytes_per_item] = (char (*)[bytes_per_item])&(carray2d[i]);
      for (j = 0; j < col; j++) {
         for (k = 0; k < bytes_per_item; k++) {
            fprintf(stdout, "%c", row2d[j][k]);
         }
         fprintf(stdout, ",");
      }
      for (j = actual_per_row; j < bytes_per_row; j++) {
         fprintf(stdout, "%hhd", carray2d[i][j]);
      }
      fprintf(stdout, "\n");
   }

   fprintf(stdout, "\n");

   for (i = 0; i < 17; i++) {
      fprintf(stdout, "%d ", array[i]);
   }
   fprintf(stdout, "\n");
   
   return EXIT_SUCCESS;
}
