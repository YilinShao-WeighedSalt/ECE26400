// if n = 2m
//    Fib_2m = 2 * Fib_m-1 * Fib_m + Fib_m * Fib_m
//    Fib_2m-1 = Fib_m * Fib_m + Fib_m-1 * Fib_m-1
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// assume that n is even
static void log_Fib_helper(unsigned int n, unsigned long *fibn, unsigned long *fibn1)
{
   unsigned int half_n = n/2;
   if (n <= 2) {
      *fibn = *fibn1 = half_n;
      return;
   }
   unsigned long fibhalf_n, fibhalf_n1;
   if (half_n % 2 == 0) { // half_n is even
      log_Fib_helper(half_n, &fibhalf_n, &fibhalf_n1);
   } else {
      log_Fib_helper(half_n-1, &fibhalf_n1, &fibhalf_n);
      fibhalf_n += fibhalf_n1;
   }
   *fibn = (2 * fibhalf_n1 + fibhalf_n) * fibhalf_n;
   *fibn1 = fibhalf_n * fibhalf_n + fibhalf_n1 * fibhalf_n1;
}

static unsigned long log_Fib(unsigned int n)
{
   if (n <= 1) {
      return n;
   }
   unsigned long fibn, fibn1; // fib(n) and fib(n-1)
   if (n % 2 == 0) { // n is even
      log_Fib_helper(n, &fibn, &fibn1);
   } else {
      // fib(n-1) and fib(n-2)
      log_Fib_helper(n-1, &fibn1, &fibn); 
      // add fib(n-1) to fib(n-2) to make fibn
      fibn += fibn1;
   }
   return fibn;   
}

static unsigned long exp_Fib(unsigned int n)
{
   if (n <= 1) 
      return n;
   unsigned long n1 = exp_Fib(n - 1);
   unsigned long n2 = exp_Fib(n - 2);
   return n1 + n2;
}

static unsigned long lin_Fib_helper(unsigned int n, unsigned long *fn1)
{
   if (n == 2) {
      return (*fn1 = 1);
   }
   unsigned long fn2;
   *fn1 = lin_Fib_helper(n-1, &fn2);
   return (*fn1 + fn2);
}

static unsigned long lin_Fib(unsigned int n)
{
   if (n <= 1) 
      return n;
   unsigned long fn1;
   unsigned long fn = lin_Fib_helper(n, &fn1);
   return fn;
}

int main(int argc, char **argv)
{
   if (argc != 3) {
      fprintf(stderr, "expect a number\n");
      return EXIT_FAILURE;
   }

   unsigned long (*fib_func[3])(unsigned int) = { log_Fib, lin_Fib, exp_Fib };

   // no longer doing vigorous check with strtol
   // atoi converts a string into a base 10 integer

   int n = atoi(argv[1]);
//   if (n < 0 || n > 93) {  // 93-th Fibonacci number is the largest an unsigned long can hold
//      fprintf(stderr, "negative number or a number too large %d\n", n);
//      return EXIT_FAILURE;
//   } 

   int choice = 0;
   if (strcmp(argv[2], "lin") == 0) {
      choice = 1;
   } else if (strcmp(argv[2], "exp") == 0) {
      choice = 2;
   } else if (strcmp(argv[2], "log") == 0) {
      choice = 0;
   } else {
      fprintf(stderr, "%s invalid choice (exp, log, or lin)\n", argv[2]);
      return EXIT_FAILURE;
   }

   for (int i = 0; i <= n; i++) {
      fprintf(stdout, "Fib(%d): %lu\n", i, fib_func[choice](i));
   }

   return EXIT_SUCCESS;
}
