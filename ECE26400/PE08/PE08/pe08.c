#include <stdio.h>

#include "answer08.h"
static int cmp_fn(const void *p1, const void *p2)
{
    return *(const int *)p1 - *(const int *)p2;
}
static void print_fn(const void *ptr)
{
    printf("%d", *(const int *)ptr);
}
static void destroy_fn(void *ptr)
{
    free(ptr);
}
int main(int argc, char **argv)
{
    lnode *list;
    list = NULL;
    int new = 7;
    for (int i = 0; i < argc; i++)
    {
        PQ_enqueue(&list, argv[i], cmp_fn);
    }
    lnode_print(list, print_fn);
    lnode_destroy(list, destroy_fn);
    return 0;
}
