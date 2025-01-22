#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "answer01.h"

// a sample test function to call test_my_strtol
//
static void test_my_strtol()
{
   // these are for my_strtol
   char *my_endptr;
   int my_errno;

   // these are for c strtol
   char *c_endptr;
   int c_errno;

   int flag = 1;

   int base;
   const char *test_cases[] = {
       "0000008931231293123131231231231312", // LONG_MAX
       "1.11111E+30",
       "-1.11111E+30",
       " \f\n\r\t\v0000002D09uC3 \f\n\r\t\v",
       " \f\n\r\t\veBelf99.123",
       " \f\n\r\t\v- 1111111111111111111111111111111",
       " \f\n\r\t\v+zik0Zk \f\n\r\t\v",
       " \f\n\r\t\v+-1111111111111111111111111111111",
       "   -00010a:",
       " \f\n\r\t\v-282Ba4aB0",
       " \f\n\r\t\v0000001728002635214590698 \f\n\r\t\v",
       " \f\n\r\t\v-0000003igOeCJBMcA689q", // base_26 is wrong --> at 8 where it reaches the LONG_MIN(MAX)
       " \f\n\r\t\v-33d3D8307B21400a.123",
       " 0xFFFFFFFFFFFFFFFFAAA ",
       " -0xFFFFFFFFFFFFFFFFAAA "
       "-82931231293123131231231231312", // LONG_MIN
       "garbage",
       "12345",
       "-12345",
       "0",
       "0X1234",
       "-0X1234",
       " ++ ",
       " - ",
       " -x ",
       "+x1",
       " +x ",
       " -0xAaG ",
       "    123 ",
       "  +-123",
       "   +1-1",
       " 0x044",
       " \f\n\r \f\n\r\t\v- 1111111111111111111111111111111111111111111",
       " \f\n\r\t\v-27C57H36.123",
       " \f\n\r\t\v-0000003928g3H6I",
       " \f\n\r\t\v+1Bk39F3AH3DMq7 \f\n\r\t\v",
       " \f\n\r\t\vq1Se8f0m04IsB",
       " \f\n\r\t\v2HeiCIiie82DH97.123",
       "+0000004340724c6C71dC7A7E", // line 38
       "\f\n\r\t\v - 0000008000000000000000 \f\n\r\t\v",
       "\f\n\r\t\v - q1sE8f0m04iSc",
       "\f\n\r\t\v - 9223372036854775808.123",
       "\f\n\r\t\v - 000000aCD772JNC9l0l8o",
       "\f\n\r\t\v + A487504730968B08A0 \f\n\r\t\v",
       "\f\n\r\t\v000000113333333333333333333333333333330 \f\n\r\t\v 2.78E+21",
       "\f\n\r\t\v2343041131043231311322324230 .123 + 00000020752587082923245560a",
       "\f\n\r\t\v - 0000002g549DHa03A97H60 \f\n\r\t\v - 2.08E+19",
       "\f\n\r\t\v - 164EF23f50C150B0.123",
       "\f\n\r\t\v - 00000018000000000000000g",
       "\f\n\r\t\v + 2021110011022210012102010021220101220222 \f\n\r\t\v",
       "\f\n\r\t\v0000001728002635214590698 \f\n\r\t\v 1.10E+27",
       "\f\n\r\t\v41a792678515120368 .123 + 00000010B269549075433c38d",
       "\f\n\r\t\v - 0000001Bk39f3aH3dmQ9 \f\n\r\t\v - 1.73E+18",
       "\f\n\r\t\v - 33d3D8307B21400a.123",
       "\f\n\r\t\v - 0000003igOeCJBMcA689q",
       "1111111222",
       "0x  ",
       " \f\n\r\t\v-00000010000000000000000000000000000001 \f\n\r\t\v",
       "   0.123",
       " ",
   };
   // test for a range of base, including an invalid bases 1 and 37
   // here are some suggestions for additional test, exceeding LONG_MAX, or
   // going below LONG_MIN, and many others
   for (int i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++)
   {
      const char *str = test_cases[i];
      for (base = 0; base < 38; base++)
      {
         my_endptr = NULL;
         errno = 0;
         long int result = my_strtol(str, &my_endptr, base);
         my_errno = errno;

         fprintf(stderr, "my_strtol: \"%s\", base=%d, result=%ld, errno=%d, my_endptr(p)=%p, my_endptr(s) =%s\n\n", str, base, result, my_errno, my_endptr, my_endptr);

         c_endptr = NULL;
         errno = 0;
         long int expected = strtol(str, &c_endptr, base);
         c_errno = errno;
         fprintf(stderr, "strtol: \"%s\", base=%d, result=%ld, errno=%d,c_endptr(p)=%p, c_endptr(s) =%s\n\n", str, base, expected, c_errno, c_endptr, c_endptr);

         // if (result == expected)
         //    fprintf(stderr, "YOU ARE CORRECT!\n");
         // else
         //    fprintf(stderr, "YOU ARE WRONG!\n");
         // if (my_errno == c_errno)
         //    fprintf(stderr, "YOU ARE CORRECT!\n");
         // else
         //    fprintf(stderr, "YOU ARE WRONG!\n");
         // if (my_endptr == c_endptr)
         //    fprintf(stderr, "YOU ARE CORRECT!\n");
         // else
         //    fprintf(stderr, "YOU ARE WRONG!\n");
         if (result != expected)
            flag = 0;
         if (c_errno != my_errno)
            flag = -1;
         if (c_endptr != my_endptr)
            flag = -2;
      }
      if (flag == 1)
         fprintf(stderr, "YOU ARE CORRECT!!!\n");
      else
         fprintf(stderr, "YOU ARE WRONG!\n");

      // for (base = 0; base < 38; base++)
      // {

      //    // before you call the function str_to_long_int
      //    // set errno to zero

      //    my_endptr = NULL;
      //    errno = 0;
      //    long int test = my_strtol("     +0X044", &my_endptr, base);
      //    my_errno = errno;

      //    // print errno
      //    // typically, you want to check errno when the returned value
      //    // is LONG_MAX or LONG_MIN in a more useful program

      //    fprintf(stderr, "%ld:%p,%s,%d\n", test, my_endptr, my_endptr, my_errno);

      //    // call strtol to cross check the results
      //    // note that the results should not match when base == 16.
      //    // before you call the function strtol
      //    // set errno to zero

      //    c_endptr = NULL;
      //    errno = 0;
      //    long int test = strtol("     +0X044", &c_endptr, base);
      //    c_errno = errno;

      //    fprintf(stderr, "%ld:%p,%s,%d\n", test, c_endptr, c_endptr, c_errno);
      // }
   }
}

int main(int argc, char **argv)
{
   fprintf(stderr, "Welcome to ECE264, we are working on PA01.\n\n");

   // testing the test_my_strtol function
   // question:  how to do a comprehensive test

   test_my_strtol();

   return EXIT_SUCCESS;
}
