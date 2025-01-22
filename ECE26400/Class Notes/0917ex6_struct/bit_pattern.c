#include <stdio.h>
#include "bit_pattern.h"

static void print_a_byte(unsigned char byte, char separator)
{
   unsigned char mask = 0x80;
   int i;
   for (i = 0; i < 8; i++) {
      fprintf(stdout, "%c", (mask & byte) == 0? '0': '1');
      mask = mask >> 1;
   }
   fprintf(stdout, "%c", separator);
}

void print_a_byte_array(void *addr, int nelements)
{
   // unsigned char *uc_byte = addr;
   int i;

   for (i = nelements - 1; i > 0; i--) {  // print from most significant byte to less significant bytes
      // print_a_byte(uc_byte[i], ' ');
      print_a_byte(((unsigned char *)addr)[i], ' ');
   }

   if (i == 0) {
      // print_a_byte(uc_byte[i], '\n'); // print the least significant byte
      print_a_byte(((unsigned char *)addr)[i], '\n'); // print the least significant byte
   }
}
























/*

   unsigned char mask = 0x80;
   int i;
   for (i = 0; i < 8; i++) {
      fprintf(stdout, "%c", (mask & byte) == 0? '0': '1');
      mask = mask >> 1;
   }
   fprintf(stdout, "%c", separator);

*/
