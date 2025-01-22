#include <stdio.h>
#include <stdlib.h>

typedef struct _Tnode {
   int key;
   struct _Tnode *left, *right;
} Tnode;

static Tnode *Build_BST(int *sorted_array, int lidx, int ridx)
{
   if (ridx < lidx) { // empty array, empty tree
      return NULL; 
   }
   int midx = (lidx + ridx)/2;  // only if no overflow
   Tnode *root = malloc(sizeof(*root));
   if (root) {
      root->key = sorted_array[midx];
      root->left = Build_BST(sorted_array, lidx, midx - 1);
      root->right = Build_BST(sorted_array, midx + 1, ridx);
   }
   return root;
}

static void Destroy_tree(Tnode *root)
{
   if (root == NULL) 
      return;
   Destroy_tree(root->left);
   Destroy_tree(root->right);
   free(root);
}

static void Preorder(Tnode *root)
{
   if (root == NULL) 
      return;
   fprintf(stdout, "%d ", root->key);
   Preorder(root->left);
   Preorder(root->right);
}

static void Inorder(Tnode *root)
{
   if (root == NULL) 
      return;
   Inorder(root->left);
   fprintf(stdout, "%d ", root->key);
   Inorder(root->right);
}

static void Postorder(Tnode *root)
{
   if (root == NULL) 
      return;
   Postorder(root->left);
   Postorder(root->right);
   fprintf(stdout, "%d ", root->key);
}

int main(int argc, char **argv)
{
   int sorted_array[] = { 0, 2, 4, 6, 8, 10, 12 }; 
   // int sorted_array[] = { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28 };

   int size = sizeof(sorted_array)/sizeof(sorted_array[0]);
   
   Tnode *BST = Build_BST(&(sorted_array[0]), 0, size - 1);

   Preorder(BST);
   fprintf(stdout, "\n");
   Inorder(BST);
   fprintf(stdout, "\n");
   Postorder(BST);
   fprintf(stdout, "\n");

   Destroy_tree(BST);
   return EXIT_SUCCESS;
}
