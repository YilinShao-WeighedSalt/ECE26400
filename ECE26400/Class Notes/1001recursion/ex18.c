#include <stdio.h>
#include <stdlib.h>

static void ToH(int n, char src, char intm, char dest)
{
   if (n == 1) {
      fprintf(stdout, "move disk %d from %c to %c\n", n, src, dest);
      return;
   }
   ToH(n-1, src, dest, intm);
   fprintf(stdout, "move disk %d from %c to %c\n", n, src, dest);
   ToH(n-1, intm, src, dest);
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
      fprintf(stderr, "require >= 1 disk to move\n");
      return EXIT_FAILURE;
   }
   ToH(n, 'A', 'B', 'C');
   return EXIT_SUCCESS;
}
