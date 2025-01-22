#include "answer05.h"
#include <ctype.h>
#include <errno.h>
#include <limits.h>

static bool check_for_leading(int ch)
{
    if (ch == EOF)
        return false;
    if (ch == '0')
    {
        fprintf(stderr, "Leading zero\n");
        return false;
    }
    if (!(isdigit(ch)))
    {
        fprintf(stderr, "encounter not a number\n");
        return false;
    }
    return true;
}
bool is_floor_length_valid(FILE *fp)
{
    fseek(fp, 0L, SEEK_SET);
    long floor_length = 0;
    int ch = fgetc(fp);

    if (!check_for_leading(ch))
    {
        fprintf(stderr, "Wrong for 2\n");
        return false;
    }

    fseek(fp, -1L, SEEK_CUR); // go back

    // check for correct format
    errno = 0;
    int n_c = fscanf(fp, "%ld", &floor_length);

    fprintf(stderr, "n_c = %d, floor_length = %ld, errno = %d\n", n_c, floor_length, errno);
    if ((n_c == 0) || (errno != 0) || (floor_length > INT_MAX) || (floor_length < INT_MIN))
    {
        fprintf(stderr, "fscanf wrong\n");
        return false;
    }

    // check again where fscanf stop
    if (n_c == 1 && (ch = fgetc(fp)) == '\n')
    {
        fprintf(stderr, "Successfully dealt with the invalid character issue.\n");
    }
    else
    {
        fprintf(stderr, "Encounter a invalid input\n");
        return false;
    }

    // check for power of 2 or out of bound
    if (floor_length < 1 || ((floor_length & (floor_length - 1)) != 0))
    {
        fprintf(stderr, "not a power of 2 number\n");
        return false;
    }

    return true;
}

bool are_coordinates_valid(FILE *fp)
{
    fseek(fp, 0L, SEEK_SET);
    long x, y;
    int floor_length;
    int re;
    // go to next line and get floor length
    if ((re = fscanf(fp, "%d\n", &floor_length)) != 1)
        return false;

    int ch = fgetc(fp);

    if (!check_for_leading(ch))
    {
        return false;
    }

    fseek(fp, -1L, SEEK_CUR);
    errno = 0;

    int n_c = fscanf(fp, "%ld,%ld", &x, &y);

    if ((n_c == 0) || (errno != 0) || (x > INT_MAX) || (x < INT_MIN) || (y > INT_MAX) || (y < INT_MIN))
    {
        fprintf(stderr, "fscanf wrong\n");
        return false;
    }

    // check again where fscanf stop is '\n' or not
    if (n_c == 2 && (ch = fgetc(fp)) == '\n')
    {
        fprintf(stderr, "Successfully dealt with the invalid character issue.\n");
    }
    else
    {
        fprintf(stderr, "Encounter a invalid input\n");
        return false;
    }

    if (x > floor_length || y > floor_length)
        return false;

    return true;
}
static int number_of_digits(int num)
{
    int digits = 0;
    while (num > 0)
    {
        digits++;
        num /= 10;
    }
    return digits;
}
bool is_file_size_valid(FILE *fp)
{
    int floor_length;
    int row, col;
    int re1, re2;

    fseek(fp, 0L, SEEK_END);
    long fsize = ftell(fp);

    fseek(fp, 0L, SEEK_SET);
    if ((re1 = fscanf(fp, "%d\n", &floor_length)) != 1)
        return false;
    if ((re2 = fscanf(fp, "%d,%d\n", &row, &col)) != 2)
        return false;

    int size1 = number_of_digits(floor_length) + 1;
    int size2 = number_of_digits(row) + 1 + number_of_digits(col) + 1;
    int tiling_size = floor_length * (floor_length + 1);

    long expected_size = size1 + size2 + tiling_size;

    if (fsize != expected_size)
        return false;
    return true;
}
bool is_floor_content_valid(FILE *fp)
{
    int floor_length;
    int row, col;
    int re1, re2;

    fseek(fp, 0L, SEEK_SET);
    if ((re1 = fscanf(fp, "%d\n", &floor_length)) != 1)
        return false;
    if ((re2 = fscanf(fp, "%d,%d\n", &row, &col)) != 2)
        return false;

    int size1 = number_of_digits(floor_length) + 1;
    int size2 = number_of_digits(row) + 1 + number_of_digits(col) + 1;
    long pos = size1 + size2;
    fseek(fp, pos, SEEK_SET);

    char ch;
    bool flag = false;
    for (int i = 0; i < floor_length; i++)
    {
        for (int j = 0; j < floor_length; j++)
        {
            ch = fgetc(fp);
            if (ch < '0' || ch > '4')
                return false;
            if (ch == '4')
            {
                if (flag || i != row || j != col)
                    return false;
                flag = true;
            }
        }
        ch = fgetc(fp);
        if (ch != '\n')
            return false;
    }
    if (!flag) // no '4' was found
        return false;

    return true;
}

int determine_tiling_solution_category(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        return INVALID_FILENAME;

    if (!is_floor_length_valid(fp))
    {
        fclose(fp);
        return INVALID_FLOOR_LENGTH;
    }
    if (!are_coordinates_valid(fp))
    {
        fclose(fp);
        return INVALID_COORDINATES;
    }
    if (!is_file_size_valid(fp))
    {
        fclose(fp);
        return INVALID_FILE_SIZE;
    }
    if (!is_floor_content_valid(fp))
    {
        fclose(fp);
        return INVALID_FLOOR_CONTENT;
    }

    fclose(fp);
    return VALID_SOLUTION;
}