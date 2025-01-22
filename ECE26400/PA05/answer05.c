#include "answer05.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
static lnode *PQ_enqueue(lnode **pq, treenode *new_object, int (*cmp_fn)(const treenode *, const treenode *))
{
    if (new_object == NULL)
        return NULL;
    lnode *newnode = malloc(sizeof(*newnode));
    if (newnode == NULL)
        return NULL;
    newnode->ptr = new_object;
    lnode dummy;
    dummy.next = *pq;
    lnode *prev = &dummy;
    lnode *curr;
    while (((curr = prev->next) != NULL) && (cmp_fn(curr->ptr, new_object) <= 0))
        prev = curr;
    prev->next = newnode;
    newnode->next = curr;
    *pq = dummy.next;
    return newnode;
}
static int cmp_fn(const treenode *p1, const treenode *p2)
{
    int x;
    if (p1->weight != p2->weight)
        x = p1->weight - p2->weight;
    else
        x = p1->ch - p2->ch;
    return x;
}
static void *PQ_dequeue(lnode **pq)
{
    if (*pq == NULL)
        return NULL;
    void *dummy = (*pq)->ptr;
    lnode *curr = *pq;
    *pq = (*pq)->next;
    free(curr);
    return dummy;
}
void lnode_destroy(lnode *list, void (*destroy_fn)(void *))
{
    while (list != NULL)
    {
        lnode *temp = list->next;
        destroy_fn(list->ptr);
        free(list);
        list = temp;
    }
    return;
}
static void destroyPostorder(treenode *tn)
{
    if (tn == NULL)
        return;
    destroyPostorder(tn->left);
    destroyPostorder(tn->right);
    free(tn);
}
static void printPreorder(treenode *tn, FILE *ofp)
{
    if (tn == NULL)
        return;
    if (tn->ch == 256)
        fprintf(ofp, "0");
    else
        fprintf(ofp, "1%c", tn->ch);
    printPreorder(tn->left, ofp);
    printPreorder(tn->right, ofp);
}
// void printpreorderB(treenode *tn, bFILE *bfp)
// {

// }
long *output_file_1(char *filename)
{
    FILE *fpi = fopen(filename, "rb");
    if (fpi == NULL)
        return NULL;
    long *array_2 = calloc(256, sizeof(*array_2));
    if (array_2 == NULL)
    {
        fclose(fpi);
        return NULL;
    }
    int ch;
    while ((ch = fgetc(fpi)) != EOF)
        array_2[ch]++;
    fclose(fpi);
    return array_2;
}
void output_file_2(long *array, lnode **pq)
{
    int flag = 0;
    for (int i = 0; i < 256; i++)
    {
        if (array[i] != 0)
        {
            flag = 1;
            treenode *newtree = malloc(sizeof(*newtree));
            if (newtree == NULL)
                return;
            newtree->ch = i;
            newtree->weight = array[i];
            newtree->left = NULL;
            newtree->right = NULL;
            PQ_enqueue(pq, newtree, cmp_fn);
        }
    }
    if (!flag)
        *pq = NULL;
}
unsigned char *output_file_3(lnode **pq, char *filename, long *fsize)
{
    FILE *ofp = fopen(filename, "w+");
    if (ofp == NULL)
        return NULL;
    if (*pq == NULL)
    {
        fclose(ofp);
        *fsize = 0;
        return malloc(0);
    }
    while ((*pq)->next != NULL)
    {
        treenode *left;
        treenode *right;
        treenode *newtree = malloc(sizeof(*newtree));

        left = PQ_dequeue(pq);
        right = PQ_dequeue(pq);
        newtree->ch = 256;
        newtree->left = left;
        newtree->right = right;
        newtree->weight = left->weight + right->weight;
        PQ_enqueue(pq, newtree, cmp_fn);
    }
    treenode *n = PQ_dequeue(pq);
    printPreorder(n, ofp);

    fseek(ofp, 0L, SEEK_END);
    *fsize = ftell(ofp);
    fseek(ofp, 0L, SEEK_SET);
    unsigned char *array = malloc(sizeof(*array) * *fsize);
    if (array == NULL)
    {
        fclose(ofp);
        return NULL;
    }
    if (fread(array, 1, *fsize, ofp) != *fsize)
    {
        free(array);
        fclose(ofp);
        return NULL;
    }
    destroyPostorder(n);
    fclose(ofp);
    return array;
}
bFILE *b_fopen(char *filename, char *mode)
{
    bFILE *bfp = malloc(sizeof(*bfp));
    if (bfp == NULL)
        return NULL;
    bfp->fp = fopen(filename, mode);
    if (bfp->fp == NULL)
    {
        free(bfp);
        return NULL;
    }
    bfp->buffer = 0;
    bfp->bit_index = 0;
    bfp->mode = *mode;
    return bfp;
}
void extractbit(bFILE *bfp, unsigned char *array, long fsize)
{
    for (int i = 0; i < fsize; i++)
    {
        if (array[i] == '0')
            fputbit(0, bfp);
        else if (array[i] == '1')
        {
            fputbit(1, bfp);
            if (i <= fsize - 1 && array[i + 1] == '1')
            {
                for (int j = 0; j < 8; j++)
                {
                    int temp = 0;
                    temp |= (array[i + 1] >> j) & 1;
                    fputbit(temp, bfp);
                }
                continue;
            }
        }
        else
        {
            for (int j = 0; j < 8; j++)
            {
                int temp = 0;
                temp |= (array[i] >> j) & 1;
                fputbit(temp, bfp);
            }
        }
        if (i == fsize - 1)
        {
        }
    }
}
int fputbit(int bit, bFILE *bfp)
{
    bfp->buffer |= (bit << bfp->bit_index);
    bfp->bit_index++;
    if (bfp->bit_index == 8)
    {
        if (fwrite(&bfp->buffer, 1, 1, bfp->fp) != 1)
        {
            bfp->buffer = 0;
            bfp->bit_index = 0;
            return bit;
        }
        bfp->buffer = 0;
        bfp->bit_index = 0;
    }
    return bit;
}

int b_fclose(bFILE *bfp)
{
    if (bfp->mode == 'w' && bfp->bit_index != 0)
        fprintf(bfp->fp, "%c", bfp->buffer);
    fclose(bfp->fp);
    free(bfp);
    return 1;
}
// int fgetbit(bFILE *bfp)
// {
//     if (bfp->buffer == NULL)
//     {
//         for(i = 0)
//     }

//         return (int)bfp->buffer;
// }
