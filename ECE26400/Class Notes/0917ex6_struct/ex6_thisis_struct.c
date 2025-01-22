#include <stdlib.h>
#include <stdio.h>

#include "bit_pattern.h"

/* equivalent to, defining struct _istruct as a collection of fields
   defining istruct to be equivalent to struct _istruct, i.e., an alias */

/*
struct _istruct {
   char c;
   short s;
   int i;
   long l;
};

typedef struct _istruct istruct;
*/

// #pragma pack(push)
// #pragma pack(1)
typedef struct _istruct {
   char c;
   short s;
   int i;
   long l;
   void (*prt_func)(void *, int);
} istruct;
// #pragma pack(pop)

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

static void inc2_istruct_addr(istruct *isa)
{
   isa->c += 2;
   isa->s += 2;
   isa->i += 2;
   isa->l += 2;
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
   is.prt_func(&(is.c), sizeof(is.c));
   is.prt_func(&(is.s), sizeof(is.s));
   is.prt_func(&(is.i), sizeof(is.i));
   is.prt_func(&(is.l), sizeof(is.l));
   is.prt_func(&is, sizeof(is));

   fprintf(stdout, "\n");
}

int main(int argc, char **argv)
{
   istruct is = { .c = 0x30, .s = 0x3231, .i = 0x36353433, .l = 0x4368456e476b4f6a, .prt_func = decimal_print };
   // istruct is;
   // is.c = 0x30;   // 00110000
   // is.s = 0x3231;
   // is.i = 0x36353433;
   // is.l = 0x4368456e476b4f6a;
   // is.prt_func = decimal_print;

   fprintf(stdout, "istruct size: %zd\n\n", sizeof(is));

   fprintf(stdout, "address of is: %p, c: %p, s: %p, i: %p, l: %p\n\n", 
                   (void *)&is, (void *)&(is.c), (void *)&(is.s), (void *)&(is.i), (void *)&(is.l));

   fprintf(stdout, "Print is\n");

   print_istruct(is);

   fprintf(stdout, "call a function to \"increment\" is, store result in inc_is\n");

   istruct inc_is = inc_istruct(is);
   inc_is.prt_func = print_a_byte_array;

   fprintf(stdout, "Print is\n");
   print_istruct(is);

   fprintf(stdout, "Print inc_is\n");
   print_istruct(inc_is);
   
   inc2_istruct_addr(&is);
   fprintf(stdout, "Print is\n");
   print_istruct(is);

   istruct *isaddr2;
   isaddr2 = malloc(sizeof(*isaddr2));
   if (isaddr2 == NULL) {
      fprintf(stderr, "memory allocation error\n");
      return EXIT_FAILURE;
   }
   fprintf(stdout, "Address stored in isaddr2: %p\n", (void *)isaddr2);


   *isaddr2 = (istruct) { .c = 0, .s = 1, .i = 2, .l = 3, .prt_func = print_a_byte_array };

   inc2_istruct_addr(isaddr2);
   fprintf(stdout, "Print *isaddr2\n");
   print_istruct(*isaddr2);

   free(isaddr2);
   return EXIT_SUCCESS;
}
