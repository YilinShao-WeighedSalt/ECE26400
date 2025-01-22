#include <stdio.h>
#include <stdlib.h>

#include "answer09.h"

static lnode *PQ_enqueue(lnode **pq, treenode *new_object,
                         int (*cmp_fn)(const treenode *, const treenode *))
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
static void lnode_print(const lnode *list, void (*print_fn)(const treenode *, FILE *), FILE *ofp)
{
    while (list != NULL)
    {
        // print the memory associated with list->ptr
        print_fn(list->ptr, ofp);
        // print an arrow
        fprintf(ofp, "->");
        list = list->next;
    }
    // print NULL and a newline after that
    fprintf(ofp, "NULL\n");
}
static void print_fn(const treenode *ptr, FILE *ofp)
{
    fprintf(ofp, "%c:%ld", ptr->ch, ptr->weight);
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
static void destroyPostorder(treenode *tn)
{
    if (tn == NULL)
        return;
    destroyPostorder(tn->left);
    destroyPostorder(tn->right);
    free(tn);
}
long *output_file_1(char *filename)
{
    FILE *fpi = fopen(filename, "r");

    long *array_2 = calloc(256, sizeof(*array_2));
    int ch;
    while ((ch = fgetc(fpi)) != EOF)
        array_2[ch]++;
    fclose(fpi);
    return array_2;
}

int write_to_file(char *filename, long *array)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
        return -1;
    if (fwrite(array, sizeof(*array), 256, fp) != 256)
    {
        fclose(fp);
        return -1;
    }
    fclose(fp);
    return 1;
}

void output_file_2(char *filename, long *array, lnode **pq)
{
    FILE *ofp = fopen(filename, "w");
    if (ofp == NULL)
        return;
    for (int i = 0; i < 256; i++)
    {
        if (array[i] != 0)
        {
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
    lnode_print(*pq, print_fn, ofp);

    fclose(ofp);
}

void output_file_3(char *filename, lnode **pq)
{
    FILE *ofp = fopen(filename, "w");
    if (ofp == NULL)
        return;

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
    treenode *n;
    n = PQ_dequeue(pq);
    printPreorder(n, ofp);
    destroyPostorder(n);
    fclose(ofp);
}
