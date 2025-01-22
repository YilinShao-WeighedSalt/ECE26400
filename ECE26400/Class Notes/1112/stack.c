#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "tree.h"
#include "stack.h"

listnode *push(listnode **stack, treenode *tree)
{
   listnode *newnode = malloc(sizeof(*newnode));
   if (newnode == NULL) {
      return NULL;
   }
   newnode->tree = tree;
   newnode->next = *stack;
   *stack = newnode;
   return newnode;
}

treenode *pop(listnode **stack)
{
   if (*stack == NULL) {
      return NULL;
   }
   listnode *top = *stack;
   treenode *ret_tree = top->tree; 
   *stack = top->next;
   free(top);
   return ret_tree;
}

//  when stack is empty, force the first entry looked at
//  to be pushed onto the stack as a single-node tree.
//
int peek(listnode *stack, bool *valid)
{
   if (stack == NULL) {
      *valid = false;
      return INT_MIN;
   }
   *valid = true;
   return stack->tree->info;
}

// clean up when run out of memory
//
void clean_stack(listnode *stack)
{
   while (stack) {
      listnode *tmp = stack->next;
      destroy_tree(stack->tree);
      free(stack);
      stack = tmp;
   }
}

