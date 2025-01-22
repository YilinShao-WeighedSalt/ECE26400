/* check whether a file contains int (no overflow, no underflow)
   follows the format:
   int,int,int,...,int,int\n
   no space, just numbers separated by commas, and the last number must be followed by \n
   print 1 to stdout for correct format, print 0 to stdout for incorrect format, or other errors
   assume at least 1 int
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

static int read_a_number(FILE *fptr)
{
   errno = 0;
   int ch = fgetc(fptr);
   if (ch == EOF) {
      return 0;
   }
   if (!((isdigit(ch)) || (ch == '+') || (ch == '-'))) {
      return 0;
   }
   fseek(fptr, -1L, SEEK_CUR); // step back one and let fscanf do the work
   long ld;
   int n_conv = fscanf(fptr, "%ld", &ld);
   if ((n_conv == 0) || (errno != 0)) {
      fprintf(stderr, "can't convert or long overflow %d %d\n", n_conv, errno);
      return 0;
   }
   if ((ld > INT_MAX) || (ld < INT_MIN)) {
      fprintf(stderr, "int overflow %ld\n", ld);
      return 0;
   }
   return 1;
}

int main(int argc, char **argv)
{
   if (argc != 2) {
      fprintf(stderr, "expect one filename\n");
      return EXIT_FAILURE;
   }

   FILE *fptr = fopen(argv[1], "r");
   if (fptr == NULL) {
      fprintf(stderr, "input file cannot be opened\n");
      return EXIT_FAILURE;
   }

   int format_flag = 1;
   while (format_flag == 1) {
      format_flag = read_a_number(fptr);
      if (format_flag == 1) {
         int ch = fgetc(fptr);
         if (ch == ',') {
            continue;
         } else if ((ch == '\n') && (fgetc(fptr) == EOF)) {
            break;
         } else {
            format_flag = 0;
         }
      }
   }

   fclose(fptr);
   fprintf(stdout, "%d\n", format_flag);

   return EXIT_SUCCESS;
}
