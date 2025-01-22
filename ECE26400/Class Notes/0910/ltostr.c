#include <stdlib.h>
#include <stdio.h>

#include "ltostr.h"

static int num_of_syms(long n, int base)
{
   int count = 0;
   if (n < 0) {
      count++;
   }
   do {
      count++;
      n = n/base;
   } while (n != 0);
   return count;
}

static char int_to_char(int value);

static void fill_in_string(long n, int base, char *str, int str_size)
{
   int sign = 1;
   if (n < 0) {
      str[0] = '-';
      sign = -1;
   }
   str[str_size - 1] = '\0';
   str_size--;
   do {
      int remainder = n % base;
      str[str_size - 1] = int_to_char(remainder * sign);
      str_size--;
      n = n/base;
   } while (n != 0);
}

char int_to_char(int value)
{
   if (value <= 9) { 
      return '0' + value;
   } else {
      return 'A' + value - 10;
   }
}

// return a string, i.e., a block of char ended with '\0'
// given a long int, and given a base int
//
// first, count the number of chars required to store the number as a string
// allocate the space for the string
// store the symbols representing the number in the string 
char *ltostr(long n, int base)
{
   int str_size = num_of_syms(n, base) + 1; // additional char for '\0'
   // fprintf(stderr, "number of symbols %d\n", str_size);
   char *str = malloc(sizeof(*str) * str_size);
   if (str == NULL) {
      return NULL;
   }
   fill_in_string(n, base, str, str_size);
   return str;
}
