#include <stdlib.h>
#include <stdio.h>

// defining a structure or struct
// the type is
//    struct _strtol_ret
/*
struct _strtol_ret {
   long converted_value;
   char *addr_of_char_that_stops_conversion;
};
*/

// giving the struct (struct a different name for ease of typing)
// typedef (i.e., defining a type), the existing type (struct _strtol_ret),
// the new name (strtol_ret)
/*
typedef struct _strtol_ret strtol_ret;
*/

// my preferred way of defining and naming a struct
// together

/*
typedef struct _strtol_ret {
   long converted_value;
   char *addr_of_char_that_stops_conversion;
} strtol_ret;
*/

typedef struct _istruct
{
   long l;
   int i;
   short s;
   char c;
} istruct;

static void decimal_print(void *vaddr, int size)
{
   switch (size)
   {
   case sizeof(char):
      fprintf(stdout, "%hhd\n", *(char *)vaddr); // the first * is to get the address of the (char *)vaddr, and the (char *) is a typecasting to let vaddr points to a char since it used to point to a void* which is anything
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
      for (int i = 0; i < size; i++)
      {
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
   istruct is = {.c = 0x30, .s = 0x3231, .i = 0x36353433, .l = 0x4368456e476b4f6a};
   // istruct is;
   // is.c = 0x30;   // 00110000
   // is.s = 0x3231;
   // is.i = 0x36353433;
   // is.l = 0x4368456e476b4f6a;

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
