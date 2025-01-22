// covered this when we talked about recursion

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

int main(int argc, char **argv) 
{
   int array[] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28};
   int array_size = sizeof(array)/sizeof(array[0]);

   treenode *root = build_BST_from_sorted_array(&(array[0]), 0, array_size - 1);

   inorder_print(root);
   fprintf(stdout, "\n");

   preorder_print(root);
   fprintf(stdout, "\n");

   postorder_print(root);
   fprintf(stdout, "\n");

   destroy_tree(root);

   return EXIT_SUCCESS;
}

