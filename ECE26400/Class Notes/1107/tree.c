#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

treenode *build_BST_from_sorted_array(int *array, int lindex, int rindex)
{
   if (lindex > rindex) {
      return NULL;
   }
   int med_index = (lindex + rindex) / 2; 
   treenode *newnode = malloc(sizeof(*newnode));
   if (newnode == NULL) {
      return NULL;
   }
   newnode->info = array[med_index];
   newnode->left = build_BST_from_sorted_array(array, lindex, med_index - 1);
   newnode->right = build_BST_from_sorted_array(array, med_index + 1, rindex);
   return newnode;
}

void inorder_print(treenode *tree)
{
   if (tree == NULL) {
      return;
   }
   inorder_print(tree->left);
   fprintf(stdout, "%d ", tree->info);
   inorder_print(tree->right);
}

void postorder_print(treenode *tree)
{
   if (tree == NULL) {
      return;
   }
   postorder_print(tree->left);
   postorder_print(tree->right);
   fprintf(stdout, "%d ", tree->info);
}

void preorder_print(treenode *tree)
{
   if (tree == NULL) {
      return;
   }
   fprintf(stdout, "%d ", tree->info);
   preorder_print(tree->left);
   preorder_print(tree->right);
}

void destroy_tree(treenode *tree)
{
   if (tree == NULL) {
      return;
   }
   destroy_tree(tree->left);
   destroy_tree(tree->right);
   free(tree);
}

