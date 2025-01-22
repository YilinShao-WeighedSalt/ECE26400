#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "answer05.h"
static void destroy_fn(void *ptr)
{
    free(ptr);
}
int main(int argc, char **argv)
{
    if (argc != 4)
        return EXIT_FAILURE;
    char *filename = "temp.txt";
    if (strcmp(argv[1], "-e") == 0)
    {
        long *array = output_file_1(argv[2]);
        if (array == NULL)
        {
            fprintf(stderr, "input file can't process\n");
            return EXIT_FAILURE;
        }
        lnode *pq = NULL;
        long fsize = 0;
        output_file_2(array, &pq);
        unsigned char *topo_char = output_file_3(&pq, filename, &fsize);
        if (topo_char == NULL && fsize != 0)
        {
            free(array);
            lnode_destroy(pq, destroy_fn);
            return EXIT_FAILURE;
        }
        bFILE *bfp = b_fopen(argv[3], "w");
        if (bfp == NULL)
        {
            fprintf(stderr, "output file can't open\n");
            free(array);
            free(topo_char);
            lnode_destroy(pq, destroy_fn);
            return EXIT_FAILURE;
        }
        if (fsize > 0)
            extractbit(bfp, topo_char, fsize);
        b_fclose(bfp);
        lnode_destroy(pq, destroy_fn);
        free(array);
        free(topo_char);
        return EXIT_SUCCESS;
    }
    else if (strcmp(argv[1], "-d") == 0)
    {
        return EXIT_SUCCESS;
    }
    else
        return EXIT_FAILURE;
}