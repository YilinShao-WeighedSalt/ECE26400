#include <stdlib.h>
#include <stdio.h>

#include "bit_pattern.h"

#pragma pack(push)
#pragma pack(1)
typedef struct _istruct {
   char c;
   short s;
   int i;
   long l;
} istruct;
#pragma pack(pop)

static void decimal_print(void *vaddr, int size)
{
   switch (size) {
      case sizeof(char): 
         fprintf(stdout, "%hhd\n", *(char *)vaddr);
         break;
      case sizeof(short):
         fprintf(stdout, "%hd\n", *(short *)vaddr);
         break;
      case sizeof(int):
         fprintf(stdout, "%d\n", *(int *)vaddr);
         break;
      case sizeof(long):
         fprintf(stdout, "%ld\n", *(long *)vaddr);
         break;
      default: 
         for (int i = 0; i < size; i++) {
            fprintf(stdout, "%c", ((char *)vaddr)[i]);
         }
         fprintf(stdout, "\n");
   }
}

static istruct inc_istruct(istruct is)
{
   is.c += 1;
   is.s += 1;
   is.i += 1;
   is.l += 1;
   return is;
}

static void print_istruct(istruct is)
{
   decimal_print(&is.c, sizeof(is.c));
   decimal_print(&is.s, sizeof(is.s));
   decimal_print(&is.i, sizeof(is.i));
   decimal_print(&is.l, sizeof(is.l));
   decimal_print(&is, sizeof(is));
   fprintf(stdout, "\n");
}

int main(int argc, char **argv)
{
   istruct is = { .c = 0x30, .s = 0x3231, .i = 0x36353433, .l = 0x4368456e476b4f6a };

   fprintf(stdout, "istruct size: %zd\n\n", sizeof(is));

   fprintf(stdout, "address of is: %p, c: %p, s: %p, i: %p, l: %p\n\n", 
                   (void *)&is, (void *)&(is.c), (void *)&(is.s), (void *)&(is.i), (void *)&(is.l));

   fprintf(stdout, "Print is\n");

   print_istruct(is);

   fprintf(stdout, "call a function to \"increment\" is, store result in inc_is\n");

   istruct inc_is = inc_istruct(is);

   fprintf(stdout, "Print is\n");
   print_istruct(is);

   fprintf(stdout, "Print inc_is\n");
   print_istruct(inc_is);
   
   return EXIT_SUCCESS;
}
