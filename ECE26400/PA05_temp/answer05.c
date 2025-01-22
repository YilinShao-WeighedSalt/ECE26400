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
void destroyPostorder(treenode *tn)
{
    if (tn == NULL)
        return;
    destroyPostorder(tn->left);
    destroyPostorder(tn->right);
    free(tn);
}
// static void printPreorder(treenode *tn)
// {
//     if (tn == NULL)
//         return;
//     if (tn->ch == 256)
//         fprintf(stderr, "0");
//     else
//         fprintf(stderr, "1%c", tn->ch);
//     printPreorder(tn->left);
//     printPreorder(tn->right);
// }
// void postorder(treenode *tn)
// {
//     if (tn == NULL)
//         return;
//     postorder(tn->left);
//     postorder(tn->right);
//     if (tn->ch == 256)
//         fprintf(stderr, "0");
//     else
//         fprintf(stderr, "1%c", tn->ch);
// }
void postorderB(treenode *tn, bFILE *bfp)
{
    if (tn == NULL)
        return;

    postorderB(tn->left, bfp);
    postorderB(tn->right, bfp);
    if (tn->ch == 256)
        fputbit(0, bfp);
    else
    {
        fputbit(1, bfp);
        for (int i = 0; i < 8; i++)
        {
            int bit = 0;
            bit |= (tn->ch >> i) & 1;
            fputbit(bit, bfp);
        }
    }
}
void printPreorder_b(treenode *tn, bFILE *bfp)
{
    if (tn == NULL)
        return;

    if (tn->ch == 256)
    {
        fputbit(0, bfp);
    }
    else
    {
        fputbit(1, bfp);
        for (int j = 0; j < 8; j++)
        {
            int bit = 0;
            bit |= (tn->ch >> j) & 1;
            fputbit(bit, bfp);
        }
    }
    printPreorder_b(tn->left, bfp);
    printPreorder_b(tn->right, bfp);
}
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
bFILE *output_file_3(lnode **pq, char *filename)
{
    bFILE *bfp = b_fopen(filename, "w");
    if (bfp == NULL)
        return NULL;
    if (*pq == NULL)
    {
        b_fclose(bfp);
        return NULL;
    }
    while ((*pq)->next != NULL)
    {
        treenode *left;
        treenode *right;
        treenode *newtree = malloc(sizeof(*newtree));
        if (newtree == NULL)
        {
            b_fclose(bfp);
            return NULL;
        }

        left = PQ_dequeue(pq);
        right = PQ_dequeue(pq);
        newtree->ch = 256;
        newtree->left = left;
        newtree->right = right;
        newtree->weight = left->weight + right->weight;
        PQ_enqueue(pq, newtree, cmp_fn);
    }
    treenode *n = PQ_dequeue(pq);
    // printPreorder(n);
    // postorder(n);
    printPreorder_b(n, bfp);
    destroyPostorder(n);

    return bfp;
}
treenode *rebuild_tree(lnode **pq, bFILE *bfp)
{
    if (*pq == NULL)
    {
        return NULL;
    }
    while ((*pq)->next != NULL)
    {
        treenode *left;
        treenode *right;
        treenode *newtree = malloc(sizeof(*newtree));
        if (newtree == NULL)
        {
            b_fclose(bfp);
            return NULL;
        }

        left = PQ_dequeue(pq);
        right = PQ_dequeue(pq);
        newtree->ch = 256;
        newtree->left = left;
        newtree->right = right;
        newtree->weight = left->weight + right->weight;
        PQ_enqueue(pq, newtree, cmp_fn);
    }
    treenode *n = PQ_dequeue(pq);
    // postorder(n);
    return n;
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
int fgetbit(bFILE *bfp)
{
    if (bfp->bit_index == 0)
    {
        bfp->buffer = fgetc(bfp->fp);
        bfp->bit_index = 8;
    }
    int bit = (bfp->buffer >> (7 - bfp->bit_index)) & 1;
    bfp->bit_index--;
    return bit;
}
