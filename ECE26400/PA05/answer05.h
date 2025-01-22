#ifndef ANSWER05_H
#define ANSWER05_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _bFILE
{
    FILE *fp;
    unsigned char buffer;
    unsigned char bit_index;
    unsigned char mode;
} bFILE;

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

bFILE *b_fopen(char *filename, char *mode);
// int fgetbit(bFILE *bfp);
int fputbit(int bit, bFILE *bfp);
int b_fclose(bFILE *bfp);
long *output_file_1(char *filename);
void output_file_2(long *array, lnode **pq);
unsigned char *output_file_3(lnode **pq, char *filename, long *fsize);
void lnode_destroy(lnode *list, void (*destroy_fn)(void *));
void extractbit(bFILE *bfp, unsigned char *array,long fsize);
#endif
