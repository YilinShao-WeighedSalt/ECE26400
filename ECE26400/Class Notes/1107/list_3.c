// did not cover this in class
// will cover later
// release this to you so that you can compile the program

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"

// return the last exchange
// 
static bool bubble_sort_one_pass(listnode *prev, listnode *last_exchange, listnode **curr_last_exchange)
{
   bool sorted = true;
   listnode *curr = prev->next;
   listnode *curr_next = curr->next;
   while (curr_next != last_exchange) {
      if (strcmp(curr->str, curr_next->str) > 0) {
         // prev->curr->curr_next->next -> prev->curr_next->curr->next
         prev->next = curr_next;
         curr->next = curr_next->next;
         curr_next->next = curr; 
         sorted = false;
         *curr_last_exchange = curr;
      } 
      prev = prev->next;
      curr = prev->next;
      curr_next = curr->next;
   }
   return sorted;
}

listnode *bubble_sort(listnode *list)
{
   if ((list == NULL) || (list->next == NULL)) {
      return list; 
   }
   
   listnode dummy;
   dummy.next = list;
   bool sorted = false;
   listnode *last_exchange = NULL;
   while (!sorted) {
      sorted = bubble_sort_one_pass(&dummy, last_exchange, &last_exchange);
   }
   return dummy.next;
}

