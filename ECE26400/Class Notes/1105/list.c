#include <stdio.h>
#include <stdlib.h>

#include "list.h"

listnode *insert_in_front(listnode **list, char *str)
{
   listnode *newnode = malloc(sizeof(*newnode));
   if (newnode == NULL) {
      return NULL;
   }
   newnode->str = str;
   newnode->next = *list;
   *list = newnode;
   return newnode;
}

void print_list(listnode *list) 
{
   while (list != NULL) {
      fprintf(stdout, "%s->", list->str);
      list = list->next;
   }
   fprintf(stdout, "NULL\n");
}

void destroy_list(listnode *list)
{
   while (list != NULL) {
      listnode *tmp = list->next;
      free(list);
      list = tmp;
   }
}
