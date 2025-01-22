#include <stddef.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>
#include "answer01.h"

#define INV_SYMBOL 36

static int char_to_int(char c)
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
// you should try to re-use a majority of the algorithms in PE02
// for this programming assignment.
// However, you have to take care of endptr, base 0, and base 16
// these are the three additional things you have to deal with in
// this assignment, as compared to the str_to_long_int function
// that you wrote for PE02.
//
// it is really IMPORTANT that you extensively try out the function
// strtol on your own.
//
long int my_strtol(char const *nptr, char **endptr, int base)
{
   long int ret_value = 0; // return value
   char const *p = nptr;
   int i = 0;
   int negative = 1;
   errno = 0;
   int count = 0;

   if (endptr == NULL)
      return 0;
   // if invalid base, set errno and return immediately
   if (base < 0 || base == 1 || base > 36)
   {
      errno = EINVAL;
      return 0;
   }
   if (endptr != NULL)
      *endptr = (char *)(p + i);
   // valid base, skip over white space

   while (isspace(p[i]))
   {
      i++;
   }

   // if encounter a sign, expect a number after that
   // if a negative sign is encountered, change the sign
   if (p[i] == '-' && isalnum(p[i + 1]))
   {
      negative = -1;
      i++;
      if (base == 0)
      {
         if (p[i] == '0')
         {
            if (p[i + 1] == 'x' || p[i + 1] == 'X')
            {
               base = 16;
            }
            else
            {
               base = 8;
               i++;
            }
         }
         else
            base = 10;
      }
      if (!isalnum(p[i]) || char_to_int(p[i]) >= base)
      {
         *endptr = (char *)nptr;
         return 0;
      }
   }
   else if (p[i] == '+' && isalnum(p[i + 1]))
   {
      i++;
      if (base == 0)
      {
         if (p[i] == '0')
         {
            if (p[i + 1] == 'x' || p[i + 1] == 'X')
            {
               base = 16;
            }
            else
            {
               base = 8;
               i++;
            }
         }
         else
         {
            base = 10;
         }
      }
      if (!isalnum(p[i]) || char_to_int(p[i]) >= base)
      {
         *endptr = (char *)nptr;
         return 0;
      }
   }
   else if (!isalnum(p[i]))
   {
      return 0;
   }

   // the exact algorithm is not given, but these are
   // the tasks the function has to perform:
   //
   // for base 0, determine the actual base
   //    if it starts with '0', it is octal
   //    if '0' is followed by 'x' or 'X' it is hexadecimal or base 16
   //    otherwise, it is decimal
   // therefore you have to determine the actual base and the starting
   // location to perform conversion
   if (base == 0)
   {
      if (p[i] == '0' && p[i + 1] != '\0' && isalnum(p[i + 1]))
      {
         if (p[i + 1] == 'x' || p[i + 1] == 'X')
         {
            base = 16;
         }
         else
         {
            base = 8;
            i++;
         }
      }
      else
         base = 10;
   }

   // for bases 2 to 15, perform conversion as in PE02
   //
   // for base 16, you have to decide when the conversion should
   // start: after the optional "0x" or "0X" or immediately
   // question: if you have "0xG", what should be converted?
   //
   // for bases 17 to 36, perform conversion as in PE02
   //
   // after you have determine the real base, and where to start,
   // perform the conversion
   if (base == 16)
   {
      if (p[i] == '0' && (p[i + 1] == 'x' || p[i + 1] == 'X'))
      {
         if (!isalnum(p[i + 2]))
         {
            *endptr = (char *)(p + i + 1);
            return 0;
         }
         i += 2;
      }
   }

   while (p[i] != '\0')
   {
      int digit = char_to_int(p[i]);

      count += 1;
      if (digit >= base)
      {
         if (count == 1)
         {
            *endptr = (char *)nptr;
            break;
         }
         *endptr = (char *)(p + i);
         break;
      }
      if (ret_value > (LONG_MAX - digit) / base)
      {
         errno = ERANGE;
         while (p[i] != '\0' && char_to_int(p[i]) < base)
         {
            if (isalnum(p[i]))
               i++;
            else
            {
               *endptr = (char *)(p + i);
               break;
            }
         }
         *endptr = (char *)(p + i);
         if (negative == 1)
         {
            return LONG_MAX;
         }
         else
         {
            return LONG_MIN;
         }
      }
      ret_value = ret_value * base + digit;

      i++;
      *endptr = (char *)(p + i);
   }

   ret_value *= negative;

   // clean up, set ret_value properly if the conversion went out of range
   // set errno if necessary
   // set *endptr properly if the endptr is not NULL
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
