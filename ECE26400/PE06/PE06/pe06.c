#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include "answer06.h"

static int check_format(char *str, bool *success);
int main(int argc, char **argv)
{
    if (argc != 6)
    {
        fprintf(stderr, "Not enough arguent.\n");
        return EXIT_FAILURE;
    }

    tiling_solution ts;
    bool success = true;

    ts.floor_length = check_format(argv[1], &success);
    if (success == false)
        return EXIT_FAILURE;

    ts.row = check_format(argv[2], &success);
    if (success == false)
        return EXIT_FAILURE;

    ts.column = check_format(argv[3], &success);
    if (success == false)
        return EXIT_FAILURE;

    int input_f = determine_tiling_solution_category(argv[4], &ts);

    if (input_f != 0)
    {
        if(input_f == 6)
        {
            free_2d_array(ts.floor_content,ts.floor_length);
        }
        fprintf(stdout, "%d\n", input_f);
        return EXIT_FAILURE;
    }

    int save = save_tiling_solution(argv[5], &ts);
    free_2d_array(ts.floor_content,ts.floor_length);
    if (save != 1)
    {
        fprintf(stdout, "%d\n", INVALID_OUTPUT_FILE);
        return EXIT_FAILURE;
    }

    fprintf(stdout, "%d\n", VALID_SOLUTION);
    return EXIT_SUCCESS;
}

static int check_format(char *str, bool *success)
{
    char *endptr = NULL;
    errno = 0;

    long temp = strtol(str, &endptr, 10);
    if ((errno != 0) || (endptr == str) || (*endptr != '\0'))
    {
        *success = false;
        return 0;
    }
    if (temp <= -1 || temp > INT_MAX)
    {
        *success = false;
        return 0;
    }
    return (int)temp;
}