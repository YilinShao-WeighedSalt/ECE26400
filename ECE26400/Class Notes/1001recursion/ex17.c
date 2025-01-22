#include <stdio.h>
#include <stdlib.h>

static unsigned long Fib(unsigned int n)
{
   if (n <= 1) 
      return n;
   unsigned long n1 = Fib(n - 1);
   unsigned long n2 = Fib(n - 2);
   return n1 + n2;
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
   if (n < 0 || n > 93) {  // 93-th Fibonacci number is the largest an unsigned long can hold
      fprintf(stderr, "negative number or a number too large %d\n", n);
      return EXIT_FAILURE;
   } 
   fprintf(stdout, "Fib(%d): %lu\n", n, Fib(n));
/*
   for (int i = 0; i <= n; i++) {
      fprintf(stdout, "Fib(%d): %lu\n", i, Fib(i));
   }
*/

   return EXIT_SUCCESS;
}
