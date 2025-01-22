#ifndef __ANSWER05_H__
#define __ANSWER05_H__

#include <stdio.h>
#include <stdbool.h>

#define VALID_SOLUTION 0
#define INVALID_FILENAME 1
#define INVALID_FLOOR_LENGTH 2
#define INVALID_COORDINATES 3
#define INVALID_FILE_SIZE 4
#define INVALID_FLOOR_CONTENT 5

bool is_floor_length_valid(FILE *fp)
                __attribute__((nonnull (1)));

bool are_coordinates_valid(FILE *fp)
                __attribute__((nonnull (1)));

bool is_file_size_valid(FILE *fp)
                __attribute__((nonnull (1)));

bool is_floor_content_valid(FILE *fp)
                __attribute__((nonnull (1)));

int determine_tiling_solution_category(char *filename)
                __attribute__((nonnull (1)));

#endif
