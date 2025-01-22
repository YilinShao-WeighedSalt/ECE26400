// covered only the enqueue function
// will cover bubble sort later
//
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

static listnode *enqueue(listnode **head, listnode **tail, char *str)
{
   listnode *newnode = malloc(sizeof(*newnode));
   if (newnode == NULL) {
      return NULL;
   }
   *newnode = (listnode) { .str = str, .next = NULL };
   if (*head == NULL) {
      return *head = *tail = newnode;
   }   
   (*tail)->next = newnode;
   *tail = newnode;
   return newnode;
}

int main(int argc, char **argv) 
{
   listnode *q_head = NULL;
   listnode *q_tail = NULL;
   int i;
   for (i = 1; i < argc; i++) {
      enqueue(&q_head, &q_tail, argv[i]);
   }
   print_list(q_head);

   q_head = bubble_sort(q_head);
 
   // beware: q_tail is no long valid

   q_tail = NULL;

   print_list(q_head);

   destroy_list(q_head);

   return EXIT_SUCCESS;
}

