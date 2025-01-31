#include <stdio.h>
#include <stdlib.h>

#include "utility01.h"

// The following include statement includes the declarations of the
// functions that you have to write in this assignment.
static void test_largest_difference(int *array, int len, int expected);

#include "answer01.h"

// At the specified location, modify this function to study the behavior of
// valgrind

static void print_array(int *array, int len)
{
   fprintf(stderr, "{");
   int ind;

   // inject error
   // change "ind < len" to "ind <= len" for your valgrind exercise
   // change it back to "ind < len" after you have completed the valgrind
   // exercise

   for (ind = 0; ind < len; ++ind)
   {
      fprintf(stderr, "%d", array[ind]);
      if (ind != len - 1)
      {
         fprintf(stderr, ", ");
      }
   }
   fprintf(stderr, "}");
   // If we don't include a '\n' character, then we have to
   // perform a fflush(stderr);
   // to ensure that our output is immediately printed to stderr
   fflush(stderr);
}

// test function for smallest_partial_sum
//
static void test_smallest_partial_sum(int *array, int len, int expected)
{
   print_array(array, len);
   int sum = smallest_partial_sum(array, len);
   fprintf(stderr, ". partial sum = %d, expected = %d.", sum, expected);
   if (sum != expected)
      fprintf(stderr, " FAIL");
   fprintf(stderr, "\n");
}

// test function for smallest_partial_sum
//
static void test_00_smallest_partial_sum()
{
   fprintf(stderr, "Testing smallest_partial_sum(...)\n");

   // Here we use "static initialization" to create an array
   // note that for ISO C, we cannot have a zero-size array in static
   // allocation, but can have an zero-size memory in dynamic allocation

   int array1[] = {-4, -1, 0, 1, 5, 10, 20, 21};
   int len1 = sizeof(array1) / sizeof(array1[0]);
   test_smallest_partial_sum(array1, len1, -5);

   int array2[] = {1, 4, -1, 6, -5, 4};
   int len2 = sizeof(array2) / sizeof(array2[0]);
   test_smallest_partial_sum(array2, len2, -5);

   int array3[] = {-1, -2, -3, -4};
   int len3 = sizeof(array3) / sizeof(array3[0]);
   test_smallest_partial_sum(array3, len3, -10);

   // use dynamic allocation for zero-size array

   int *array4 = malloc(sizeof(*array4) * 0);
   int len4 = 0;
   test_smallest_partial_sum(array4, len4, 0);

   // inject error
   // comment the free statement
   free(array4);

   // You can add more test-cases here
   // ...

   fprintf(stderr, "\n"); // Tidy output is easier to use
}

// you may want to write your own test function
// make sure that you print all debugging information to stderr
//
static void test_largest_difference(int *array, int len, int expected)
{
   print_array(array, len);
   int sum = largest_difference(array, len);
   fprintf(stderr, ". largest difference = %d, expected = %d.", sum, expected);
   if (sum != expected)
      fprintf(stderr, " FAIL");
   fprintf(stderr, "\n");
}

static void test_01_largest_difference()
{
   fprintf(stderr, "Testing largest_difference(...)\n");
   // write your own test function
   int array1[] = {-4, -1, 0, 1, 5, 10, 20, 21};
   int len1 = sizeof(array1) / sizeof(array1[0]);
   test_largest_difference(array1, len1, 25);

   int array2[] = {-1, 0, 1, 1, 1};
   int len2 = sizeof(array2) / sizeof(array2[0]);
   test_largest_difference(array2, len2, 2);

   int array3[] = {-10, -11, -12, -13};
   int len3 = sizeof(array3) / sizeof(array3[0]);
   test_largest_difference(array3, len3, 3);

   int *array4 = malloc(sizeof(*array4) * 0);
   int len4 = 0;
   test_largest_difference(array4, len4, 0);

   free(array4);

   fprintf(stderr, "\n");
   // ...

   fprintf(stderr, "\n");
}

// fill in statements to call smallest_partial_sum or largest_difference
// depending on the first input argument
//
int main(int argc, char **argv)
{
   fprintf(stderr, "Welcome to ECE264, we are working on PE01.\n\n");

   if (argc == 3)
   { // try to parse the arguments and call the correct function
      int return_value = 0;
      int *array = NULL;
      int len = 0;

      // modify and fill in the correct statements to complete the main function
      // we expect two arguments:
      //
      if (argv[1][0] == '0' && argv[1][1] == '\0')
      {
         array = read_in_array(argv[2], &len);
         return_value = smallest_partial_sum(array, len);
      }
      else if (argv[1][0] == '1' && argv[1][1] == '\0')
      {
         array = read_in_array(argv[2], &len);
         return_value = largest_difference(array, len);
      }
      else
         return EXIT_FAILURE;
      // the first argument is an integer from the sets {0, 1}
      // 0: run smallest_partial_sum(int * array, int len)
      // 1: run largest_difference(int * array, int len)
      // otherwise: do nothing, return EXIT_FAILURE;
      //

      // the second argument is a filename.  The function read_in_array
      // is called to fill in the array and to initialize len correctly.
      // if array is NULL, should return EXIT_FAILURE
      //
      // call smallest_partial_sum or largest_difference on the non-NULL array
      // based on the first argument
      // store the results in the variable return_value, e.g., return_value = smallest_partial_sum(...);
      // print the return_value using the statement fprintf(stdout, "%d\n", return_value);
      // return EXIT_SUCCESS;

      print_array(array, len);
      fprintf(stderr, ". number of elements in array: %d\n", len);
      fprintf(stdout, "%d\n", return_value);
      free(array);
      return EXIT_SUCCESS;
   }
   else
   { // when no arguments are given, we are in test mode
      test_00_smallest_partial_sum();
      test_01_largest_difference();
      return EXIT_FAILURE;
   }
}
