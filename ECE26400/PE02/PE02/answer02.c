#include <errno.h>
#include <ctype.h>
#include <limits.h>

#include "answer02.h"

// Given a char c, return a numeric value
// '0'..'9' --> 0..9
// 'a'..'z' --> 10..35
// 'A'..'Z' --> 10..35
// for other characters, return INV_SYMBOL (see answer02.h);
//
int char_to_int(char c)
{
   // what if c is '0'--'9'
   if (isdigit(c) && c >= '0' && c <= '9')
   {
      return c - '0';
   }

   // what if c is 'a'--'z'
   else if (islower(c))
   {
      return c - 'a' + 10;
   }

   // what if c is 'A'--'Z'
   else if (isalpha(c))
   {
      return c - 'A' + 10;
   }

   // otherwise
   else
      return INV_SYMBOL;
}

// you are not allowed to change the contents at the location whose address in
// stored in nptr (the way to interpret the type of nptr is that it is an address
// pointing to a constant char.)
//
// you have to check for whether the base in the valid range 2 through 36
// if not, set errno to EINVAL
//
// This is a suggestion on how you should process the string
// (1)  skip over all white space
// (2)  if a +/- sign is encountered, set the polarity of the number accordingly
//      By default, the number is assumed to be positive if no sign is given.
// (3)  Convert the string until you encounter an invalid symbol for that
//      base or when you reach the end of the string.
//
// examples (not exhaustive, of course):
//    "10a:" in base 10 is 10, in base 16 is 266, in base 36 is 1306
//    "   -10a:" in base 10 is -10, in base 16 is -266, and in base 36 is -1306
//    " +10a:" in base 10 is 10, in base 16 is 266, in base 36 is 1306
//    "922337203685477580710304" in base 10 should return LONG_MAX, and errno
//    should be set to ERANGE.
//    "-922337203685477580710304" in base 10 should return LONG_MIN, and errno
//    should be set to ERANGE.
//    "garbage" should be 0 in base 10, 0 in base 16, and 35479055534 in base 36
//
long int str_to_long_int(char const *nptr, int base)
{
   long int ret_value = 0; // return value
   char const *p = nptr;
   int i = 0;
   int negative = 1;
   errno = 0;
   // if no conversion happens, return 0
   if (base < 2 || base > 36)
   {
      errno = EINVAL;
      return 0;
   }
   // if invalid base, set errno and return immediately

   while (isspace(p[i]))
   {
      i++;
   }
   // valid base, skip over white space

   // if encounter a sign, expect a number after that
   // if a negative sign is encountered, the conversion must
   // produce a negative number
   if (p[i] == '-' && isalnum(p[i + 1]))
   {
      negative = -1;
      i++;
   }
   else if (p[i] == '+' && isalnum(p[i + 1]))
   {
      i++;
   }
   else if (!isalnum(p[i]))
   {
      return 0;
   }

   // now, convert the string to number
   // the conversion has to account for the +/- sign
   // need to check whether you have out-of-range ret_value
   while (p[i] != '\0')
   {
      int digit = char_to_int(p[i]);
      if (digit >= base)
      {
         break;
      }

      if (ret_value > (LONG_MAX - digit) / base)
      {
         errno = ERANGE;
         if (negative == 1)
            return LONG_MAX;
         else
            return LONG_MIN;
      }
      ret_value = ret_value * base + digit;
      i++;
   }

   ret_value *= negative;

   // clean up before returning
   // need to set errno and ret_value correctly if the converted number
   // is out of range
   if (ret_value > 0 && negative == -1)
   {
      errno = ERANGE;
      return LONG_MIN;
   }
   else if (ret_value < 0 && negative == 1)
   {
      errno = ERANGE;
      return LONG_MAX;
   }
   return ret_value;
}
