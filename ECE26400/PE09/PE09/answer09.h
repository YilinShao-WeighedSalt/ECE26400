#ifndef ANSWER09_H
#define ANSWER09_H

typedef struct _treenode
{
    long weight;
    int ch;
    struct _treenode *left;
    struct _treenode *right;
} treenode;

typedef struct _lnode
{
    treenode *ptr;
    struct _lnode *next;
} lnode;

long *output_file_1(char *filename);
int write_to_file(char *filename, long *array);
void output_file_2(char *filename, long *array, lnode **pq);
void output_file_3(char *filename, lnode **pq);
void lnode_destroy(lnode *list, void (*destroy_fn)(void *));
#endif