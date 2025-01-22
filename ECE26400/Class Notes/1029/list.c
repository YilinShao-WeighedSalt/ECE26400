#include <stdio.h>
#include <stdlib.h>

#include "list.h"

listnode *insert_in_front(listnode **list, char *str)
{
   listnode *newnode;
   newnode = malloc(sizeof(*newnode));
   if (newnode == NULL) {
      return newnode;
   }
   newnode->str = str;
   newnode->next = *list;
   *list = newnode;
   return newnode;
}

void print_list(listnode *list) 
{
   while (list != NULL) {
      fprintf(stdout, "%s\n", list->str);
      list = list->next;
   }
}

void destroy_list(listnode *list)
{
   while (list != NULL) {
      listnode *tmp = list->next;
      free(list);
      list = tmp;
   }
}

