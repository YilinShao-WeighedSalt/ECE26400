#include <stdio.h>
#include <stdlib.h>


#include "answer05.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "expect one filename.\n");
        return EXIT_FAILURE;
    }
    fprintf(stdout, "%d\n", determine_tiling_solution_category(argv[1]));

    return EXIT_SUCCESS;
}