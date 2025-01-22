#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "answer02.h"

// a sample test function to call char_to_int
//
static void test_char_to_int()
{
   fprintf(stderr, "%d\n", char_to_int('9'));
   fprintf(stderr, "%d\n", char_to_int('z'));
   fprintf(stderr, "%d\n", char_to_int('Z'));
   fprintf(stderr, "%d\n", char_to_int('-'));
   fprintf(stderr, "%d\n", char_to_int('!'));
}

// a sample test function to call test_str_to_long_int
//
static void test_str_to_long_int()
{
   char *endptr; // this is for strtol
   int base;

   // test for a range of base, including an invalid base 37
   // here are some suggestions for additional test, exceeding LONG_MAX, or
   // going below LONG_MIN, and many others

   // for (base = 2; base < 38; base++)
   // {

   //    // before you call the function str_to_long_int
   //    // set errno to zero

   //    errno = 0;
   //    long int test = str_to_long_int("     +0X044", base);

   //    // print errno
   //    // typically, you want to check errno when the returned value
   //    // is LONG_MAX or LONG_MIN in a more useful program

   //    fprintf(stderr, "%ld %d\n", test, errno);

   //    // call strtol to cross check the results
   //    // note that the results should not match when base == 16.
   //    // before you call the function strtol
   //    // set errno to zero

   //    endptr = NULL;
   //    errno = 0;
   //    test = strtol("     +0X044", &endptr, base);
   //    fprintf(stderr, "%ld :%s %d\n", test, endptr, errno);
   // }

   // additional cases
   const char *test_cases[] = {
       "92931231293123131231231231312",  // LONG_MAX
       "-92931231293123131231231231312", // LONG_MIN
       "garbage",
       "12345",
       "-12345",
       "0",
       "0X1234",
       "    123 ",
       "  +-123",
       "   +1-1",
       " 0x044",
       " \f\n\r \f\n\r\t\v- 1111111111111111111111111111111",
       "   0.123",
       " "};

   for (int i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++)
   {
      const char *str = test_cases[i];
      for (base = 2; base < 36; base++)
      {
         errno = 0;
         long int result = str_to_long_int(str, base);
         fprintf(stderr, "str_to_long_int: \"%s\", base=%d, result=%ld, errno=%d\n", str, base, result, errno);

         errno = 0;
         long int expected = strtol(str, &endptr, base);
         fprintf(stderr, "strtol: \"%s\", base=%d, result=%ld, endptr=%s, errno=%d\n", str, base, expected, endptr, errno);
         if (result == expected)
            fprintf(stderr, "YOU ARE CORRECT!\n");
         else
            fprintf(stderr, "WRONG!!!\n");
      }
   }

   // Test for invalid base (0 and 37)
   errno = 0;
   long int result = str_to_long_int("123", 0);
   fprintf(stderr, "str_to_long_int: base=0, result=%ld, errno=%d\n", result, errno);

   errno = 0;
   result = str_to_long_int("123", 37);
   fprintf(stderr, "str_to_long_int: base=37, result=%ld, errno=%d\n", result, errno);
}

int main(int argc, char **argv)
{
   fprintf(stderr, "Welcome to ECE264, we are working on PE02.\n\n");

   // testing the char_to_int function
   // question:  how to do a comprehensive test

   test_char_to_int();

   // testing the str_to_long_int function
   // question:  how to do a comprehensive test

   test_str_to_long_int();

   return EXIT_SUCCESS;
}
