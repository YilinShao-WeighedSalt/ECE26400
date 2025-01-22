// more on linked lists
// search and delete
// insert in order or in reverse 
//
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main(int argc, char **argv) 
{
   listnode *list = NULL;
   int i;
   for (i = 0; i < argc; i++) {
      if (insert_in_front(&list, argv[i]) == NULL) {
         fprintf(stderr, "can't malloc\n");
      }
   }

   print_list(list);
   if (search_and_delete_1(&list, argv[argc-1]) == 0) {
      fprintf(stderr, "%s not in list\n", argv[argc-1]);
   }
   print_list(list);
   if (search_and_delete_2(&list, argv[argc-2]) == 0) {
      fprintf(stderr, "%s not in list\n", argv[argc-2]);
   }
   print_list(list);
   if (search_and_delete_3(&list, argv[argc-3]) == 0) {
      fprintf(stderr, "%s not in list\n", argv[argc-3]);
   }
   print_list(list);

   if (search_and_delete_1(&list, "Koh") == 0) {
      fprintf(stderr, "%s not in list\n", "Koh");
   }
   if (search_and_delete_1(&list, argv[0]) == 0) {
      fprintf(stderr, "%s not in list\n", argv[0]);
   }
   if (search_and_delete_2(&list, argv[1]) == 0) {
      fprintf(stderr, "%s not in list\n", argv[1]);
   }
   if (search_and_delete_3(&list, argv[2]) == 0) {
      fprintf(stderr, "%s not in list\n", argv[2]);
   }
   print_list(list);
   destroy_list(list);

   list = NULL;
   for (i = 0; i < argc; i++) {
      if (insert_in_order(&list, argv[i]) == NULL) {
         fprintf(stderr, "can't malloc\n");
      }
   }
   print_list(list);
   destroy_list(list);

   listnode *rev_list = NULL;
   for (i = 0; i < argc; i++) {
      if (insert_in_reverse(&rev_list, argv[i]) == NULL) {
         fprintf(stderr, "can't malloc\n");
      }
   }
   print_list(rev_list);

   destroy_list(rev_list);
   return EXIT_SUCCESS;
}
