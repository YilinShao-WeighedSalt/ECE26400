#include <stdlib.h>
#include <limits.h>

#include "tree.h"

treenode *insert_key(treenode **tree, int key)
{
   treenode *newnode = malloc(sizeof(*newnode));
   if (newnode == NULL) 
      return NULL;
   newnode->info = key;
   newnode->left = newnode->right = NULL;

   // new version
   treenode *curr;
   while ((curr = *tree) != NULL) {
      if (curr->info >= key) {
         tree = &(curr->left);
      } else {
         tree = &(curr->right);
      }
   }  
   *tree = newnode;
   return newnode;

   /* old version */
   /*

   treenode dummy;
   dummy.left = *tree;
   dummy.info = INT_MAX;
   treenode *parent = &dummy;
   treenode *curr = *tree;
 
   while (curr != NULL) {
      parent = curr;
      if (curr->info >= key) {
         curr = curr->left;
      } else {
         curr = curr->right;
      }
   }
   if (parent->info >= key) {
      parent->left = newnode;
   } else {
      parent->right = newnode;
   }
   *tree = dummy.left;
   return newnode;

   */
}

treenode *rec_insert_key(treenode **tree, int key)
{
   if (*tree == NULL) {
      treenode *newnode = malloc(sizeof(*newnode));
      if (newnode) {
         newnode->info = key;
         newnode->left = newnode->right = NULL;
      }
      *tree = newnode;
      return newnode;
   }
   if ((*tree)->info >= key) {
      return rec_insert_key(&((*tree)->left), key);
   } else {
      return rec_insert_key(&((*tree)->right), key);
   }
}
