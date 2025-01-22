// linked list
// insert in front

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main(int argc, char **argv) 
{
   listnode *list = NULL;
   int i;
   for (i = 0; i < argc; i++) {
      if(insert_in_front(&list, argv[i]) == NULL) {
         fprintf(stderr, "can't malloc\n");
      }
   }

   print_list(list);

   destroy_list(list);

   return EXIT_SUCCESS;
}

