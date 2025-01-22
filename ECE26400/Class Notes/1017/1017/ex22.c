#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static double my_power_helper(double n, long power)
{
   if (power == 0)
      return 1.0;
   if (power == 1) 
      return n;
   long half_power = power/2;
   double result = my_power_helper(n, half_power);
   result *= result;
   if (power % 2 == 1) 
      result *= n;
   return result;
}

static double my_power(double n, long power)
{
   // please change the first line so that
   // 0.0 raised to a negative power is also NAN

   if (n == 0.0 && power == 0)
      return NAN;
   if (power < 0) {
      return 1.0/my_power_helper(n, -power);
   } else {
      return my_power_helper(n, power);
   }
}

int main(int argc, char **argv)
{
   if (argc != 3) {
      fprintf(stderr, "expect a double and an int\n");
      return EXIT_FAILURE;
   }

   double n = strtod(argv[1], NULL);
   long power = strtol(argv[2], NULL, 10);

   fprintf(stdout, "%e^%ld = %e\n", n, power, my_power(n, power));
   return EXIT_SUCCESS;
}
