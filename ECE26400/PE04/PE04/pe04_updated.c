#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>

#include "aux04.h"
#include "answer04.h"

static double check_format_range_d(char *, bool *);
static int check_format_range_i(char *, bool *);

// fill in the correct statements to complete the main function
// we expect four arguments:
//
// the first argument is from the sets {"1", "2", "3"}
// it specifies the unknown function to be integrated
// 1:  unknown_function_1
// 2:  unknown_function_2
// 3:  unknown_function_3
// otherwise: return EXIT_FAILURE

// to integrate any of the three functions, expect the next three
// arguments to be the lower limit of the integration (double),
// the upper limit of the integration (double), and the number of
// intervals for the integration (int)

// use strtod to convert an argument to a double
// use strtol to convert an argument to a long (and then to an int)
// check that the arguments are of the correct format and within range

// You should declare a variable of type integrand.  You should use the four
// arguments to initialize the structure, and pass the structure to the
// simpson's method

// after printing the integral, return EXIT_SUCCESS

int main(int argc, char **argv)
{
   double integral = 0.0;
   bool success;
   if (argc != 5)
      return EXIT_FAILURE;
   if (strcmp(argv[1], "1") != 0 && strcmp(argv[1], "2") != 0 && strcmp(argv[1], "3") != 0)
      return EXIT_FAILURE;

   double lower_limit = check_format_range_d(argv[2], &success);
   if (success == false)
      return EXIT_FAILURE;
   double upper_limit = check_format_range_d(argv[3], &success);
   if (success == false)
      return EXIT_FAILURE;

   int n_intervals = check_format_range_i(argv[4], &success);
   if (success == false)
      return EXIT_FAILURE;

   integrand intg_arg = {.lower_limit = lower_limit, .upper_limit = upper_limit, .n_intervals = n_intervals};

   if (strcmp(argv[1], "1") == 0)
      intg_arg.func_to_be_integrated = unknown_function_1;
   else if (strcmp(argv[1], "2") == 0)
      intg_arg.func_to_be_integrated = unknown_function_2;
   else if (strcmp(argv[1], "3") == 0)
      intg_arg.func_to_be_integrated = unknown_function_3;
   // you job is to fill in the fields of a variable of type integrand
   // and pass the variable to simpson_numerical_integration

   integral = simpson_numerical_integration(intg_arg);
   fprintf(stdout, "%.10e\n", integral);
   return EXIT_SUCCESS;
}
static double check_format_range_d(char *str, bool *success)
{
   char *endptr = NULL;
   *success = false;
   errno = 0;
   double value = strtod(str, &endptr);
   // fprintf(stderr, "errno = %d\n", errno);

   if (errno != 0)
      return value;

   if (endptr == str)
      return value;

   if (*endptr != '\0')
      return value;

   if (isinf(value) != 0)
      return value;

   if (isnan(value) != 0)
      return value;

   // fprintf(stderr, "Value is %f\n", value);
   *success = true;
   return value;
}
static int check_format_range_i(char *str, bool *success)
{
   char *endptr = NULL;
   int base = 0;
   *success = true;
   errno = 0;
   long value = strtol(str, &endptr, 10);

   if ((endptr == str) || (*endptr != '\0') || (errno != 0))
   {
      *success = false;
      return base;
   }
   if (value < 1 || value > INT_MAX)
   {
      *success = false;
      return base;
   }

   return (int)value;
}
