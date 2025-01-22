// to understand argc and argv
// to understandd call stack

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>

#include "add.h"
#include "ltostr.h"

static int convert_base(char *str, bool *success)
{
   *success = true;
   int base = 0;
   errno = 0;
   char *eptr = NULL;
   long tmp_base = strtol(str, &eptr, 10);

   // error checking
   if ((errno != 0) || (*eptr != '\0') || (eptr == str)) {
      fprintf(stderr, "error number: %d EINVAL %d ERANGE %d, base %ld not valid\n", 
                      errno, EINVAL, ERANGE, tmp_base);
      *success = false;
      return base;
   } 

   if ((tmp_base > INT_MAX) || (tmp_base < INT_MIN)) {
      fprintf(stderr, "base not valid\n");
      *success = false;
      return base;
   }

   base = tmp_base;
   // check for valid base
   strtol("0", NULL, base);
   if (errno != 0) {
      fprintf(stderr, "error number: %d EINVAL %d ERANGE %d, base %d not a valid base in range\n", 
                      errno, EINVAL, ERANGE, base);
      *success = false;
      return base;
   }
   return base;
}

static long convert_a_long(char *str, int base, bool *success)
{
   *success = true;
   errno = 0;
   char *eptr = NULL;
   long i = strtol(str, &eptr, base);
   if (eptr == str) {
      fprintf(stderr, "str %s does not begin with valid symbol, converted value %ld\n", eptr, i);
      *success = false;
      return i;
   }
   if (*eptr != '\0') {
      fprintf(stderr, "str contains invalid symbol %s, converted value %ld\nWill continue\n", eptr, i);
   }
   if (errno != 0) {
      fprintf(stderr, "errno %d EINVAL %d ERANGE %d: converted str out of range, use long max %ld\nWill continue\n", 
                      errno, EINVAL, ERANGE, i);
   }
   return i;
}

//int main(int argc, char *argv[])
int main(int argc, char **argv)
{
   if (argc != 4) {
      fprintf(stderr, "expecting 3 arguments: base (in correct decimal format), two numbers in specified base\n");
      return EXIT_FAILURE;
   }
   bool success;
   int base = convert_base(argv[1], &success);
   if (success == false) {
      return EXIT_FAILURE;
   }
   long i = convert_a_long(argv[2], base, &success);
   if (success == false) {
      return EXIT_FAILURE;
   }
   long j = convert_a_long(argv[3], base, &success);
   if (success == false) {
      return EXIT_FAILURE;
   }

   if (base == 0) 
      base = 10;
   long result;
   add(i, j, &result);
   fprintf(stdout, "%ld + %ld = %ld\n", i, j, result);

   char *str1;
   char *str2;
   char *str3;
   str1 = ltostr(i, base);
   str2 = ltostr(j, base);
   str3 = ltostr(result, base);
   fprintf(stdout, "%s + %s = %s\n", str1, str2, str3);
   free(str1);
   free(str2);
   free(str3);

   return EXIT_SUCCESS;
}
