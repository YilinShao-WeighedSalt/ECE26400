#include <stdlib.h>
#include <string.h>

#include "list.h"

int search_and_delete_1(listnode **list, char *key)
{
   listnode *prev = NULL;
   listnode *curr = *list;
   while (curr) {
      if (strcmp(curr->str, key) == 0) {
         if (prev == NULL) { // removing the first node of linked list
            *list = curr->next;
         } else {
            prev->next = curr->next;
         }
         free(curr);
         return 1;
      } 
      prev = curr;
      curr = curr->next;
   }
   return 0;
}

int search_and_delete_2(listnode **list, char *key)
{
   listnode dummy;
   dummy.next = *list;

   listnode *prev = &dummy;
   listnode *curr = *list;
   while (curr) {
      if (strcmp(curr->str, key) == 0) {
         prev->next = curr->next;
         free(curr);
         *list = dummy.next;
         return 1;
      } 
      prev = curr;
      curr = curr->next;
   }
   return 0;
}

int search_and_delete_3(listnode **list, char *key)
{
   listnode *curr;
   while ((curr = *list) != NULL) {
      if (strcmp(curr->str, key) == 0) {
         *list = curr->next;
         free(curr);
         return 1;
      } 
      list = &(curr->next);
   }
   return 0;
}

listnode *insert_in_order(listnode **list, char *str)
{
   listnode *newnode = malloc(sizeof(*newnode));
   if (newnode == NULL) {
      return NULL;
   }
   newnode->str = str;
   listnode dummy;
   dummy.next = *list;
   listnode *prev = &dummy;
   listnode *curr = *list;
   while (curr) {
      if (strcmp(curr->str, str) >= 0) {
         break;
      } 
      prev = curr;
      curr = curr->next;
   }
   prev->next = newnode;
   newnode->next = curr;
   *list = dummy.next;
   return newnode;
}

listnode *insert_in_reverse(listnode **list, char *str)
{
   listnode *newnode = malloc(sizeof(*newnode));
   if (newnode == NULL) {
      return NULL;
   }
   newnode->str = str;

   listnode *curr;
   while ((curr = *list) != NULL) {
      if (strcmp(curr->str, str) <= 0) {
         break;
      } 
      list = &(curr->next);
   }
   *list = newnode;
   newnode->next = curr;
   return newnode;
}

