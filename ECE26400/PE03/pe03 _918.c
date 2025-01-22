#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>

#include "answer03.h"

static double check_format_range_d(char *, bool *);
static int check_format_range_i(char *, bool *);
int main(int argc, char **argv)
{
   double upper_limit;
   double lower_limit;
   int n_intervals;
   bool success;

   // fill in the correct statements to complete the main function
   //
   // we expect four arguments:
   if (argc != 5)
      return EXIT_FAILURE;
   //
   // the first argument is from the sets {"-m", "-t"}
   // -m: run mid_point_numerical_integration
   // -t: run trapezoidal_numerical_integration
   if (strcmp(argv[1], "-m") != 0 && strcmp(argv[1], "-t") != 0)
      return EXIT_FAILURE;
   // otherwise: return EXIT_FAILURE
   // to run any of the two integration functions, expect the next
   // three arguments to be the lower limit of the integration (double),
   // the upper limit of the integration (double), and the number of
   // intervals for the integration (int)
   //

   lower_limit = check_format_range_d(argv[2], &success);
   if (success == false)
   {
      return EXIT_FAILURE;
   }
   upper_limit = check_format_range_d(argv[3], &success);
   if (success == false)
   {
      return EXIT_FAILURE;
   }
   // use strtod to convert an argument to a double
   // use strtol to convert an argument to a long (and then to an int)
   // check that the arguments are of the correct format and within range
   n_intervals = check_format_range_i(argv[4], &success);
   if (success == false)
   {
      return EXIT_FAILURE;
   }

   double integrand = 0.0;
   if (strcmp(argv[1], "-m") == 0)
      integrand = mid_point_numerical_integration(lower_limit, upper_limit, n_intervals);
   if (strcmp(argv[1], "-t") == 0)
      integrand = trapezoidal_numerical_integration(lower_limit, upper_limit, n_intervals);
   fprintf(stdout, "%.10e\n", integrand);
   return EXIT_SUCCESS;
}

static double check_format_range_d(char *argv, bool *success)
{
   char *endptr;
   double value;
   *success = true;
   errno = 0;
   endptr = NULL;

   value = strtod(argv, &endptr);
   if ((endptr == argv) || (*endptr != '\0') || (errno != 0))
   {
      *success = false;
      return value;
   }
   if (isinf(value) != 0)
   {
      *success = false;
      return value;
   }
   if (isnan(value) != 0)
   {
      *success = false;
      return value;
   }
   // fprintf(stderr, "Limit = %f\n", value);
   return value;
}

static int check_format_range_i(char *argv, bool *success)
{
   char *endptr;
   long value;
   int base = 0;
   *success = true;
   errno = 0;
   endptr = NULL;

   value = strtol(argv, &endptr, 10);

   if ((endptr == argv) || (*endptr != '\0') || (errno != 0))
   {
      *success = false;
      return base;
   }
   if (value < 1 || value > INT_MAX)
   {
      *success = false;
      return base;
   }
   // fprintf(stderr, "Intervals = %ld\n", value);

   return (int)value;
}
