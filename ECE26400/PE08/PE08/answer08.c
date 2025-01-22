#include <stdio.h>
#include <stdlib.h>
#include "answer08.h"




/* the following functions deal with priority queues implemented         */
/* as a linked list of lnode's, with the address of each object of       */
/* interest stored in the ptr field of an lnode in the list              */

/* adding an lnode to a priority queue (PQ) implemented as a linked list */
/* such that linked list is ordered (accordinging to the cmp_fn          */
/* function) from smallest to the largest                                */
/* *pq is the address of the first lnode in the linked list; it is NULL  */
/* if the linked list is empty                                           */
/* new_object is the address of the new object to be stored in the ptr   */
/* field of the new lnode in the linked list pq; if it is NULL, the      */
/* linked list should remain the same                                    */
/* cmp_fn is the address of the function that can compare two objects    */
/* whose addresses are passed to the cmp_fn function;  the two addresses */
/* are typically stored in the ptr fields of two lnodes in the           */
/* linked list; returns a negative number if the first object is smaller,*/
/* a positive number if the first object is bigger, 0 if the two objects */
/* are the same                                                          */
/*                                                                       */
/* *pq should be updated if the new lnode added becomes the first lnode  */
/* of the linked list                                                    */
/* returns the address of the newly added lnode in the linked list       */
/* if you cannot allocate space for the new lnode, keep the linked list  */
/* the same and you should return NULL                                   */
/* if new_object is NULL, you should keep the linked list the same and   */
/* return NULL                                                           */


lnode *PQ_enqueue(lnode **pq, const void *new_object,
                  int (*cmp_fn)(const void *, const void *))
{
   if (new_object == NULL)
      return NULL;
   lnode *newnode = malloc(sizeof(*newnode));
   if (newnode == NULL)
      return NULL;
   newnode->ptr = new_object;
   lnode dummy;
   dummy.next = *pq;
   lnode *prev = &dummy;
   lnode *curr;
   while (((curr = prev->next) != NULL) && (cmp_fn(curr->ptr, new_object) < 0))
      prev = curr;
   prev->next = newnode;
   newnode->next = curr;
   *pq = dummy.next;
   return newnode;
}

/* remove the first lnode in a priority queue (PQ) implemented as a      */
/* linked list                                                           */
/* *pq is the address of the first lnode in the linked list; *pq is NULL */
/* if the linked list is empty                                           */
/*                                                                       */
/* if the linked list is empty, returns NULL                             */
/* otherwise, remove the first lnode from the linked list and update *pq */
/* return the address of the object stored in the ptr field of removed   */
/* lnode, must free the removed lnode                                    */

void *PQ_dequeue(lnode **pq)
{
   if (*pq == NULL)
      return NULL;
   void *dummy = (*pq)->ptr;
   lnode *curr = *pq;
   *pq = (*pq)->next;
   free(curr);
   return dummy;
}

/* the following functions deal with stacks implemented                  */
/* as a linked list of lnode's, with the address of each object of       */
/* interest stored in the ptr field of an lnode in the list              */

/* adding an lnode to a stack implemented as a linked list               */
/* *stack is the address of the first lnode in the linked list; it is    */
/* NULL if the linked list is empty                                      */
/* new_object is the address of the new object to be stored in the ptr   */
/* field of the new lnode in the linked list pq; if it is NULL, the      */
/* linked list should remain the same                                    */
/*                                                                       */
/* *stack should be updated after adding the new lnode as the first lnode*/
/* of the linked list                                                    */
/* returns the address of the newly added lnode in the linked list       */
/* if you cannot allocate space for the new lnode, keep the linked list  */
/* the same and you should return NULL                                   */
/* if new_object is NULL, you should keep the linked list the same and   */
/* return NULL                                                           */

lnode *stack_push(lnode **stack, const void *new_object)
{
   if (new_object == NULL)
      return NULL;
   lnode *newnode = malloc(sizeof(*newnode));
   if (newnode == NULL)
      return NULL;
   newnode->ptr = new_object;
   newnode->next = *stack;
   *stack = newnode;

   return newnode;
}

/* remove the first lnode on a stack implemented as a linked list        */
/* *stack is the address of the first lnode in the linked list; *stack   */
/* is NULL if the linked list is empty                                   */
/*                                                                       */
/* if the linked list is empty, returns NULL                             */
/* otherwise, remove the first lnode from the linked list and update     */
/* *stack                                                                */
/* return the address of the object stored in the ptr field of removed   */
/* lnode, must free the removed lnode                                    */

void *stack_pop(lnode **stack)
{
   if (*stack == NULL)
      return NULL;
   void *dummy = (*stack)->ptr;
   lnode *curr = *stack;
   *stack = (*stack)->next;
   free(curr);
   return dummy;
}

/* remove the last lnode in a linked list of lnode's                     */
/* *list is the address of the first lnode in the linked list; *list     */
/* is NULL if the linked list is empty                                   */
/*                                                                       */
/* if the linked list is empty, returns NULL                             */
/* otherwise, remove the last lnode from the linked list and update      */
/* *list if necessay                                                     */
/* return the address of the object stored in the ptr field of removed   */
/* lnode, must free the removed lnode                                    */

void *lnode_remove_last(lnode **list)
{
   if (*list == NULL)
      return NULL;
   void *dummy;
   lnode *curr = *list;
   lnode *prev = NULL;
   if (curr->next == NULL)
   {
      dummy = curr->ptr;
      *list = NULL;
      free(curr);
      return dummy;
   }
   while ((curr->next) != NULL)
   {
      prev = curr;
      curr = curr->next;
   }
   dummy = curr->ptr;
   prev->next = NULL;
   free(curr);
   return dummy;
}

/* destroy an entire linked list, freeing all memory used                */
/* list is the address of the first lnode in the linked list             */
/* destroy_fn is the address of the function to free the memory          */
/* associated with the address of the generic object stored in the ptr   */
/* field of lnode in the linked list                                     */
/* if ptr is storing an address of a simple data type, the function free */
/* is an appropriate destroy_fn                                          */
/* if ptr is storing an address of a structure or an array that stores   */
/* other addresses, a user-defined destroy_fn would be required.         */

void lnode_destroy(lnode *list, void (*destroy_fn)(void *))
{

   while (list != NULL)
   {
      lnode *temp = list->next;
      destroy_fn(list->ptr);
      free(list);
      list = temp;
   }
   return;
}

/* print an entire linked list                                           */
/* list is the address of the first lnode in the linked list             */
/* print_fn is the address of the function to print the generic object,  */
/* of which the address is stored in the ptr field of an lnode in the    */
/* linked list                                                           */
/*                                                                       */
/* DO NOT CHANGE THIS FUNCTION, OTHERWISE YOUR OUTPUT WILL BE DIFFERENT  */
/* AND YOU WILL NOT RECEIVE CREDIT                                       */

void lnode_print(const lnode *list, void (*print_fn)(const void *))
{
   while (list != NULL)
   {
      // print the memory associated with list->ptr
      print_fn(list->ptr);
      // print an arrow
      fprintf(stdout, "->");
      list = list->next;
   }
   // print NULL and a newline after that
   fprintf(stdout, "NULL\n");
}
