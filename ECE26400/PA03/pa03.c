#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "answer03.h"

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

    ts.floor_length = check_format(argv[2], &success);
    if (success == false)
    {
        fprintf(stderr, "Invalid floor length\n");
        return EXIT_FAILURE;
    }
    ts.row = check_format(argv[3], &success);
    if (success == false)
    {
        fprintf(stderr, "Invalid row coordinate\n");
        return EXIT_FAILURE;
    }
    ts.column = check_format(argv[4], &success);
    if (success == false)
    {
        fprintf(stderr, "Invalid column coordinate\n");
        return EXIT_FAILURE;
    }

    if (ts.floor_length < 1 || ((ts.floor_length & (ts.floor_length - 1)) != 0))
    {
        fprintf(stderr, "Not a power of 2\n");
        return EXIT_FAILURE;
    }

    if (ts.row < -1 || ts.column < -1 || ts.row >= ts.floor_length || ts.column >= ts.floor_length)
    {
        fprintf(stderr, "Not valid coordinate\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-v") == 0)
    {
        int input_f = determine_tiling_solution_category(argv[5], &ts);

        if (input_f != 0)
        {
            if (input_f == 6) // when the floorcontent is not null
                free_2d_array(ts.floor_content, ts.floor_length);
            fprintf(stdout, "%d\n", input_f);
            return EXIT_FAILURE;
        }

        // validation is success
        else
        {
            free_2d_array(ts.floor_content, ts.floor_length);
            fprintf(stdout, "%d\n", VALID_SOLUTION);
            return EXIT_SUCCESS;
        }
    }
    else if (strcmp(argv[1], "-g") == 0)
    {
        generate_tiling_solution(&ts);
        if(ts.floor_content == NULL)
            return EXIT_FAILURE;
        int save = save_tiling_solution(argv[5], &ts);
        if (save != 1)
        {
            free_2d_array(ts.floor_content, ts.floor_length);
            return EXIT_FAILURE;
        }
        free_2d_array(ts.floor_content, ts.floor_length);
        return EXIT_SUCCESS;
    }
    else
        return EXIT_FAILURE;
}

static int check_format(char *str, bool *success)
{
    char *endptr = NULL;
    errno = 0;

    if (str[0] == '0' && isdigit(str[1]))
    {   
        fprintf(stderr,"Comes 1\n");

        *success = false;
        return 0;
    }

    long temp = strtol(str, &endptr, 10);
    if ((errno != 0) || (endptr == str) || (*endptr != '\0'))
    {
        *success = false;
        return 0;
    }
    if (temp <= -1 || temp > INT_MAX)
    {
        fprintf(stderr,"Comes 3\n");

        *success = false;
        return 0;
    }
    return (int)temp;
}

