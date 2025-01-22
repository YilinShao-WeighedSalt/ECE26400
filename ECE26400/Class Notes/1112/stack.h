#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>
#include "tree.h"

typedef struct _listnode {
   treenode *tree;
   struct _listnode *next;
} listnode;

listnode *push(listnode **stack, treenode *tree);

treenode *pop(listnode **stack);

int peek(listnode *stack, bool *valid);

void clean_stack(listnode *stack);

#endif
