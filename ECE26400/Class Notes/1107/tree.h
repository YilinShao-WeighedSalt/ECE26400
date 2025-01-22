#ifndef __TREE_H__
#define __TREE_H__

typedef struct _treenode {
   int info;
   // struct _treenode *left, *right;
   struct _treenode *left;
   struct _treenode *right;
} treenode;

// tree.c

treenode *build_BST_from_sorted_array(int *array, int lindex, int rindex);

void inorder_print(treenode *tree);

void postorder_print(treenode *tree);

void preorder_print(treenode *tree);

void destroy_tree(treenode *tree);

// tree_1.c

treenode *insert_key(treenode **tree, int key);

treenode *rec_insert_key(treenode **tree, int key);

// tree_2.c

int *collect_postorder(treenode *tree, int *index);

treenode *rebuild_strictly_BST_from_postorder(int *po_array, int size);

// tree_3.c

int *collect_preorder(treenode *tree, int *index);

treenode *rebuild_BST_from_preorder(int *pre_array, int size);

// tree_4.c

treenode *delete_key(treenode **tree, int key);

treenode *rec_delete_key(treenode **tree, int key);

#endif
