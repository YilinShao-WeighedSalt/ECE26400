// inserting into an ordered list, based on comparison functions
// the use of addresses of functions
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

int cmp_2(char const *str1, char const *str2) {
   return -strcmp(str1, str2);
}

int main(int argc, char **argv) 
{
   listnode *list = NULL;
   int i;

   for (i = 0; i < argc; i++) {
      if (insert_in_order_generic(&list, argv[i], strcmp) == NULL) {
         fprintf(stderr, "can't malloc\n");
      }
   }
   print_list(list);
   destroy_list(list);

   listnode *rev_list = NULL;
   for (i = 0; i < argc; i++) {
      if (insert_in_order_generic(&rev_list, argv[i], cmp_2) == NULL) {
         fprintf(stderr, "can't malloc\n");
      }
   }
   print_list(rev_list);

   destroy_list(rev_list);
   return EXIT_SUCCESS;
}

