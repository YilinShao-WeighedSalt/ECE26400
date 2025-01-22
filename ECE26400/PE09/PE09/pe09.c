#include <stdio.h>
#include <stdlib.h>

#include "answer09.h"
static void destroy_fn(void *ptr)
{
    free(ptr);
}
int main(int argc, char **argv)
{
    long *array = output_file_1(argv[1]);
    lnode *pq = NULL;
    output_file_2(argv[3], array, &pq);
    output_file_3(argv[4], &pq);
    lnode_destroy(pq, destroy_fn);
    free(array);
    return EXIT_SUCCESS;
}