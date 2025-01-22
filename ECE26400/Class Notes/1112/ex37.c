// reconstruction of a strictly binary BST (with distinct keys)
// from a postorder traversal of the original BST with the help of a stack
// the stack is implemented using a linked list

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

int main(int argc, char **argv) 
{
   int array[] = {2, 6, 10, 14, 18, 22, 26};
   int array_size = sizeof(array)/sizeof(array[0]);
   treenode *root = build_BST_from_sorted_array(&(array[0]), 0, array_size - 1);

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

   int posize;
   int *poarray = collect_postorder(root, &posize);
   destroy_tree(root);
   for (i = 0; i < posize; i++) {
      fprintf(stderr, "%d ", poarray[i]);
   }
   fprintf(stderr, "\n");

   treenode *reconstructed_root = rebuild_strictly_BST_from_postorder(poarray, posize);
   free(poarray);
   inorder_print(reconstructed_root);
   fprintf(stdout, "\n");
   preorder_print(reconstructed_root);
   fprintf(stdout, "\n");
   postorder_print(reconstructed_root);
   fprintf(stdout, "\n");
   destroy_tree(reconstructed_root);

   return EXIT_SUCCESS;
}

