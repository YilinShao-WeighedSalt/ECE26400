#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tree.h"
#include "stack.h"

static int count_nodes(treenode *tree)
{
   if (tree == NULL) 
      return 0;
   return 1 + count_nodes(tree->left) + count_nodes(tree->right);
}

static void collect_postorder_helper(treenode *tree, int *array, int *index)
{
   if (tree == NULL) {
      return;
   }
   collect_postorder_helper(tree->left, array, index);
   collect_postorder_helper(tree->right, array, index);
   array[*index] = tree->info;
   *index += 1;
}

// return array as int *, return the number of valid items in *index
//
int *collect_postorder(treenode *tree, int *index)
{
   int count = count_nodes(tree);
   int *poarray = malloc(sizeof(*poarray) * count);
   if (poarray == NULL) {
      return NULL;
   }
   *index = 0;
   collect_postorder_helper(tree, poarray, index);
   return poarray;
}

// we assume that the tree is strictly binary 
// we assume that the tree has the property:
// key(left_tree) <= key(root) < key(right_tree)
//
treenode *rebuild_strictly_BST_from_postorder(int *po_array, int size)
{
   if (size == 0) {
      return NULL;
   }
   listnode *stack = NULL;
   bool valid;
   int peeked;
   int i;
   for (i = 0; i < size; i++) {
      treenode *newnode = malloc(sizeof(*newnode));
      if (newnode == NULL) {
         clean_stack(stack);
         return NULL;
      }
      newnode->info = po_array[i];
      peeked = peek(stack, &valid);
      if (valid == false) {
         newnode->left = newnode->right = NULL;
      } else {
         if (po_array[i] > peeked) { // po_array[i] must be on the other side
            newnode->left = newnode->right = NULL;
         } else {
            newnode->right = pop(&stack);
            newnode->left = pop(&stack);
         } 
      }
      push(&stack, newnode);
   }
   treenode *root = pop(&stack);
   peeked = peek(stack, &valid);
   if (valid == true) {
      clean_stack(stack);
      destroy_tree(root);
      return NULL;
   }
   return root;
}
