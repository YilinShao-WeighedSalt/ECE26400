#include <stdlib.h>

#include "list.h"

// in cmp function, node->str as first parameter, str as second parameter
//
listnode *insert_in_order_generic(listnode **list, char *str, int (*cmp)(char const *, char const *))
{
   listnode *newnode = malloc(sizeof(*newnode));
   if (newnode == NULL) {
      return NULL;
   }
   newnode->str = str;
   listnode dummy;
   dummy.next = *list;
   listnode *prev = &dummy;
   // old version
   // 
   // listnode *curr = *list;
   // while (curr) {
   //    if (cmp(curr->str, str) >= 0) {
   //       break;
   //    } 
   // prev = curr;
   // curr = curr->next;
   // }
   
   // new version
   // 
   listnode *curr;
   while (((curr = prev->next) != NULL) && (cmp(curr->str, str) < 0)) {
      prev = curr;
   }
   prev->next = newnode;
   newnode->next = curr;
   *list = dummy.next;
   return newnode;
}

