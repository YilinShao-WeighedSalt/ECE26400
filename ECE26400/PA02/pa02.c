#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>

#include "answer02.h"
#include "aux02.h"
#include "utility02.h"

static double check_format_range_d(char *, bool *);
static int check_format_range_i(char *, bool *);

int main(int argc, char **argv)
{
   bool success;
   // check for correct number of arguments.  If not, exit and return
   // exit_failure
   
   if (argc != 7)
      return EXIT_FAILURE;
   // if (argc != 8)
   //    return EXIT_FAILURE;
   // now, try to parse the arguments and call the correct function

   // fill in the correct statements to complete the main function
   // we expect six arguments:
   //
   // the first argument is 1 character from the sets {"1", "2", "3"}
   // it specifies the unknown function for which we are computing
   // the associated Fourier series
   // 1:  unknown_function_1
   // 2:  unknown_function_2
   // 3:  unknown_function_3
   // otherwise: return EXIT_FAILURE
   if (strcmp(argv[1], "1") != 0 && strcmp(argv[1], "2") != 0 && strcmp(argv[1], "3") != 0)
      return EXIT_FAILURE;

   // to compute the Fourier series, specify the range over which we
   // want to perform the integration, the next two arguments
   // should specify the lower limit (double) and upper limit (double)
   // of the range
   //
   // see PE03 and PE04 regarding the conversion
   //
   // if lower limit == upper limit, return EXIT_FAILURE
   double lower_limit = check_format_range_d(argv[2], &success);
   if (success == false)
      return EXIT_FAILURE;
   double upper_limit = check_format_range_d(argv[3], &success);
   if (success == false)
      return EXIT_FAILURE;
   if (lower_limit == upper_limit)
      return EXIT_FAILURE;

   // the next argument specifies the number of intervals (int) to be used
   // for integration
   //
   // see PE03 and PE04 regarding the conversion
   int n_intervals = check_format_range_i(argv[4], &success);
   if (success == false)
      return EXIT_FAILURE;

   // the next argument specifies the number of terms (int) in the
   // Fourier series
   //
   // see similar conversion as in PE03 and PE04
   int ai_terms = check_format_range_i(argv[5], &success);
   if (success == false)
      return EXIT_FAILURE;

   // the next argument is the name of the file to store the coefficients
   integrand intg_arg = {.lower_limit = lower_limit, .upper_limit = upper_limit, .n_intervals = n_intervals};
   if (strcmp(argv[1], "1") == 0)
      intg_arg.func_to_be_integrated = unknown_function_1;
   else if (strcmp(argv[1], "2") == 0)
      intg_arg.func_to_be_integrated = unknown_function_2;
   else if (strcmp(argv[1], "3") == 0)
      intg_arg.func_to_be_integrated = unknown_function_3;

   // fill in the fields of fourier_arg properly and call the correct
   // functions to compute the coefficients and to save the coefficients

   fourier fourier_arg;
   fourier_arg.n_terms = ai_terms; // you should change this, this is initialized
                                   // so that the following statements are fine
   fourier_arg.intg = intg_arg;
   // keep the code below
   //
   // based on fourier_arg.nterms
   // allocate space for fourier_arg.a_i and fourier_arg.b_i;

   fourier_arg.a_i = malloc(sizeof(*(fourier_arg.a_i)) * fourier_arg.n_terms);
   if (fourier_arg.a_i == NULL)
   {
      return EXIT_FAILURE;
   }
   fourier_arg.b_i = malloc(sizeof(*(fourier_arg.b_i)) * fourier_arg.n_terms);
   if (fourier_arg.b_i == NULL)
   {
      free(fourier_arg.a_i);
      return EXIT_FAILURE;
   }

   // keep the code above
   compute_fourier_coefficients(fourier_arg);
   save_fourier_coefficients(fourier_arg.a_i, fourier_arg.b_i, fourier_arg.n_terms, argv[6]);
   // function_plot(intg_arg.func_to_be_integrated, lower_limit, upper_limit, fourier_arg.a_i, fourier_arg.b_i, fourier_arg.n_terms, argv[7]);
   print_fourier_coefficients(fourier_arg.a_i, fourier_arg.b_i, fourier_arg.n_terms);
   // add code to compute Fourier coefficients and save them in a file

   // keep the code below

   free(fourier_arg.a_i);
   free(fourier_arg.b_i);

   // keep the code above

   return EXIT_SUCCESS;
}
static double check_format_range_d(char *str, bool *success)
{
   char *endptr = NULL;
   *success = false;
   errno = 0;

   double value = strtod(str, &endptr);
   // fprintf(stderr, "errno = %d\n", errno);

   if (errno != 0 || (endptr == str) || (*endptr != '\0'))
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
   *success = false;
   errno = 0;

   long value = strtol(str, &endptr, 10);

   if ((endptr == str) || (*endptr != '\0') || (errno != 0))
   {
      return base;
   }
   if (value < 1 || value > INT_MAX)
   {
      return base;
   }
   *success = true;

   return (int)value;
}
