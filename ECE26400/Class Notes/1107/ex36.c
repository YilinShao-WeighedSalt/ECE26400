// covered the iterative method, will cover the recursive method
// later
// we will insert a few more keys into the build BST
// we use iterative method and recursive method

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

int main(int argc, char **argv) 
{
   int array[] = {2, 6, 10, 14, 18, 22, 26};
   int array_size = sizeof(array)/sizeof(array[0]);
   treenode *root = build_BST_from_sorted_array(&(array[0]), 0, array_size - 1);
   inorder_print(root);
   fprintf(stdout, "\n");
   preorder_print(root);
   fprintf(stdout, "\n");
   postorder_print(root);
   fprintf(stdout, "\n");

   int iarray[] = {0, 4, 8, 12, 3, 5};
   int iarray_size = sizeof(iarray)/sizeof(iarray[0]);
   int i;
   for (i = 0; i < iarray_size; i++) {
      treenode *newnode = insert_key(&root, iarray[i]);
      if (newnode) {
         fprintf(stderr, "key %d inserted\n", newnode->info);
      } else {
         fprintf(stderr, "key %d not inserted\n", iarray[i]);
      }
   }
   inorder_print(root);
   fprintf(stdout, "\n");
   preorder_print(root);
   fprintf(stdout, "\n");
   postorder_print(root);
   fprintf(stdout, "\n");

   int rarray[] = {24, 28, 23, 25};
   int rarray_size = sizeof(rarray)/sizeof(rarray[0]);
   for (i = 0; i < rarray_size; i++) {
      treenode *newnode = rec_insert_key(&root, rarray[i]);
      if (newnode) {
         fprintf(stderr, "key %d inserted\n", newnode->info);
      } else {
         fprintf(stderr, "key %d not inserted\n", rarray[i]);
      }
   }
   inorder_print(root);
   fprintf(stdout, "\n");
   preorder_print(root);
   fprintf(stdout, "\n");
   postorder_print(root);
   fprintf(stdout, "\n");
   
   destroy_tree(root);

   return EXIT_SUCCESS;
}

