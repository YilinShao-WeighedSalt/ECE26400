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
    if (strcmp(argv[1], "-e") == 0)
    {
        long *array = output_file_1(argv[2]);
        if (array == NULL)
        {
            FILE *empty_fp = fopen(argv[3], "wb");
            if (empty_fp == NULL)
            {
                fprintf(stderr, "Error creating output file.\n");
                return EXIT_FAILURE;
            }
            fclose(empty_fp);
            return EXIT_SUCCESS;
        }
        lnode *pq = NULL;
        output_file_2(array, &pq);
        bFILE *bfp = output_file_3(&pq, argv[3]);
        if (bfp == NULL)
        {
            fprintf(stderr, "output file can't open\n");
            free(array);
            lnode_destroy(pq, destroy_fn);
            return EXIT_FAILURE;
        }
        b_fclose(bfp);
        lnode_destroy(pq, destroy_fn);
        free(array);

        return EXIT_SUCCESS;
    }
    else if (strcmp(argv[1], "-d") == 0)
    {
        long *array = output_file_1(argv[2]);
        if (array == NULL)
        {
            FILE *empty_fp = fopen(argv[3], "wb");
            if (empty_fp == NULL)
            {
                fprintf(stderr, "Error creating output file.\n");
                return EXIT_FAILURE;
            }
            fclose(empty_fp);
            return EXIT_SUCCESS;
        }
        lnode *pq = NULL;
        output_file_2(array, &pq);
        bFILE *bfpi = b_fopen(argv[2], "r");
        if (bfpi == NULL)
        {
            free(array);
            lnode_destroy(pq, destroy_fn);
            return EXIT_FAILURE;
        }
        treenode *tn = rebuild_tree(&pq, bfpi);
        if (tn == NULL)
        {
            free(array);
            lnode_destroy(pq, destroy_fn);
            b_fclose(bfpi);
            return EXIT_FAILURE;
        }
        b_fclose(bfpi);

        bFILE *bfpo = b_fopen(argv[3], "w");
        if (bfpo == NULL)
            return EXIT_FAILURE;
        postorderB(tn, bfpo);
        b_fclose(bfpo);
        destroyPostorder(tn);
        lnode_destroy(pq, destroy_fn);
        return EXIT_SUCCESS;
    }
    else
        return EXIT_FAILURE;
}