#include "answer06.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

static bool check_for_leading(int ch);
static bool is_floor_length_valid(FILE *fp,tiling_solution *ts);
static bool are_coordinates_valid(FILE *fp,tiling_solution *ts);
static int number_of_digits(int num);
static bool is_file_size_valid(FILE *fp);
static bool is_floor_content_valid(FILE *fp, char **temp, tiling_solution *ts);
static void get_array(FILE *fp, tiling_solution *ts);
static void copy_array(char **temp, tiling_solution *ts);

char **allocate_2d_array(int n)
{
    char **array = malloc(sizeof(*array) * n);
    if ((array == NULL) || (n == 0))
    {
        return NULL;
    }
    for (int i = 0; i < n; i++)
    {
        array[i] = malloc(sizeof(**array) * n);
        if (array[i] == NULL)
        {
            free_2d_array(array, n);
            return NULL;
        }
    }
    return array;
}
void free_2d_array(char **array, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(array[i]);
    }
    free(array);
}
int determine_tiling_solution_category(char *filename, tiling_solution *ts)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        return INVALID_FILENAME;
    if (!is_floor_length_valid(fp,ts))
    {
        ts->floor_content = NULL;
        fclose(fp);
        return INVALID_FLOOR_LENGTH;
    }
    if (!are_coordinates_valid(fp,ts))
    {
        ts->floor_content = NULL;
        fclose(fp);
        return INVALID_COORDINATES;
    }
    if (!is_file_size_valid(fp))
    {
        ts->floor_content = NULL;
        fclose(fp);
        return INVALID_FILE_SIZE;
    }
    ts->floor_content = allocate_2d_array(ts->floor_length);
    if (ts->floor_content == NULL)
    {
        fclose(fp);
        return INSUFFICIENT_MEMORY;
    }
    char **temp = allocate_2d_array(ts->floor_length);
    if (temp == NULL)
    {
        ts->floor_content = NULL;
        fclose(fp);
        return INSUFFICIENT_MEMORY;
    }

    if (!is_floor_content_valid(fp, temp, ts))
    {
        free_2d_array(temp,ts->floor_length);
        fclose(fp);
        return INVALID_FLOOR_CONTENT;
    }
    free_2d_array(temp,ts->floor_length);
    fclose(fp);
    return VALID_SOLUTION;
}
int save_tiling_solution(char *filename, tiling_solution *ts)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "file could not be open\n");
        return 0;
    }
    if(ts->floor_content == NULL)
        fprintf(stderr,"floor content is NULL\n");
    fprintf(fp, "%d\n", ts->floor_length);
    fprintf(fp, "%d,%d\n", ts->row, ts->column);
    for (int i = 0; i < ts->floor_length ; i++)
    {
        for (int j = 0; j < ts->floor_length; j++)
        {
            fputc(ts->floor_content[i][j], fp);
        }
        fputc('\n',fp);
    }
    fclose(fp);
    return 1;
}
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
static bool is_floor_length_valid(FILE *fp,tiling_solution *ts)
{
    fseek(fp, 0L, SEEK_SET);
    long floor_length = 0;
    int ch = fgetc(fp);

    if (!check_for_leading(ch))
    {
        fprintf(stderr, "Wrong for floor length\n");
        return false;
    }

    fseek(fp, -1L, SEEK_CUR); // go back

    // check for correct format
    errno = 0;
    int n_c = fscanf(fp, "%ld", &floor_length);

    if ((n_c == 0) || (errno != 0) || (floor_length > INT_MAX) || (floor_length < INT_MIN))
    {
        fprintf(stderr, "fscanf wrong for floor length\n");
        return false;
    }

    // check again where fscanf stop
    if (n_c == 1 && (ch = fgetc(fp)) == '\n')
    {
        fprintf(stderr, "Successfully dealt with the invalid character issue.\n");
    }
    else
    {
        fprintf(stderr, "Encounter a invalid input for floor length\n");
        return false;
    }

    // check for power of 2 or out of bound
    if (floor_length < 1 || ((floor_length & (floor_length - 1)) != 0))
    {
        fprintf(stderr, "floor length not a power of 2 number\n");
        return false;
    }

    //check for the file in the floor length and argv same
    if(floor_length != ts->floor_length)
    {
        fprintf(stderr,"Floor length don't match\n");
        return false;
    }

    return true;
}
static bool are_coordinates_valid(FILE *fp,tiling_solution *ts)
{
    fseek(fp, 0L, SEEK_SET);
    long x, y;
    int floor_length;
    int re;
    // go to next line and get floor length
    if ((re = fscanf(fp, "%d\n", &floor_length)) != 1)
        return false;
    long pos = ftell(fp);

    int ch = fgetc(fp);
    if(ch == EOF)
        return false;
    if(!(isdigit(ch)))
    {
        fprintf(stderr,"Coordinate Not a digit\n");
        return false;
    }
    if(ch == '0')
    {
        int temp = fgetc(fp);
        if(temp != ',')
        {
            fprintf(stderr,"Leading zero for first char\n");
            return false;
        }
    }
    else
        fseek(fp,1L,SEEK_CUR);
    fprintf(stderr,"My current pos after dertermine the first char= %ld\n",ftell(fp));

    //check for the second char
    int ch2 = fgetc(fp);
    fprintf(stderr,"My current pos = %ld\n",ftell(fp));
    if(ch2 == EOF)
        return false;
    if(!isdigit(ch2))
    {
        fprintf(stderr,"Coordinate Not a digit\n");
        return false;
    }
    if(ch2 == '0')
    {
        if(fgetc(fp) != '\n')
        {
            fprintf(stderr,"leading zero for the 2nd char\n");
            return false;
        }
    }
    fseek(fp,pos,SEEK_SET);
    fprintf(stderr,"My current pos = %ld\n",ftell(fp));

    errno = 0;

    int n_c = fscanf(fp, "%ld,%ld", &x, &y);

    fprintf(stderr,"My current pos = %ld\n",ftell(fp));

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
        fprintf(stderr, "Encounter a invalid input of coordinate\n");
        return false;
    }

    if (x > floor_length || y > floor_length)
        return false;

    if(x != ts->row || y != ts->column)
    {
        fprintf(stderr,"Col or row don't match\n");
        return false;
    }
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
static bool is_file_size_valid(FILE *fp)
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
static bool is_floor_content_valid(FILE *fp, char **temp, tiling_solution *ts)
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
                if (flag || (i != row) || (j != col))
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

    fseek(fp, 0L, SEEK_SET);
    fseek(fp, pos, SEEK_SET);
    get_array(fp, ts);
    copy_array(temp, ts);

    // to see if the content is valid:

    for (int i = 0; i < ts->floor_length; i++)
    {
        for (int j = 0; j < ts->floor_length; j++)
        {
            if(temp[i][j] == 'x')
                continue;
            // four cases:
            if (ts->floor_content[i][j] == '3')
            {
                //check if the shape fit
                if (ts->floor_content[i][j + 1] == '3' && ts->floor_content[i + 1][j] == '3')
                {
                    if ((temp[i][j] != 'x') && (temp[i][j + 1] != 'x') && (temp[i + 1][j] != 'x'))
                    {
                        // mark these off
                        temp[i][j] = 'x';
                        temp[i][j + 1] = 'x';
                        temp[i + 1][j] = 'x';
                        continue;
                    }
                }
                else
                {
                    fprintf(stderr, "Tile 3 is wrong\n");
                    return false;
                }
            }
            if (ts->floor_content[i][j] == '2')
            {
                if (ts->floor_content[i][j + 1] == '2' && ts->floor_content[i + 1][j + 1] == '2')
                {
                    if(j + 1 >= ts->floor_length || i + 1 >= ts->floor_length)
                        break;
                    if (temp[i][j] != 'x' && temp[i][j + 1] != 'x' && temp[i + 1][j + 1] != 'x')
                    {
                        temp[i][j] = 'x';
                        temp[i][j + 1] = 'x';
                        temp[i + 1][j + 1] = 'x';

                        continue;
                    }
                    if (temp[i][j] == 'x')
                        continue;
                }
                else
                {
                    fprintf(stderr, "Tile 2 is wrong\n");
                    return false;
                }
            }
            if (ts->floor_content[i][j] == '1')
            {
                if (ts->floor_content[i + 1][j] == '1' && ts->floor_content[i + 1][j + 1] == '1')
                {
                    if(i + 1 > ts -> floor_length || j + 1 > ts->floor_length)
                        break;
                    if (temp[i][j] != 'x' && temp[i + 1][j] != 'x' && temp[i + 1][j + 1] != 'x')
                    {
                        temp[i][j] = 'x';
                        temp[i + 1][j] = 'x';
                        temp[i + 1][j + 1] = 'x';
                        continue;
                    }
                    if (temp[i][j] == 'x')
                    {
                        continue;
                    }
                }
                else
                {
                    fprintf(stderr, "Tile 1 is wrong\n");
                    return false;
                }
            }
            if (ts->floor_content[i][j] == '0')
            {
                if (ts->floor_content[i + 1][j - 1] == '0' && ts->floor_content[i + 1][j] == '0')
                {
                    if(i + 1 == floor_length || j - 1 < 0)
                        break;
                    if (temp[i][j] != 'x' && temp[i + 1][j - 1] != 'x' && temp[i + 1][j] != 'x')
                    {
                        temp[i][j] = 'x';
                        temp[i + 1][j - 1] = 'x';
                        temp[i + 1][j] = 'x';
                        continue;
                    }
                    if (temp[i][j] == 'x')
                    {
                        j += 1;
                        continue;
                    }
                }
                else
                {
                    fprintf(stderr, "Tile 0 is wrong\n");
                    return false;
                }
            }
            if(ts->floor_content[i][j] == '4')
                continue;
        }
    }
    return true;
}
static void get_array(FILE *fp, tiling_solution *ts)
{
    for (int i = 0; i < ts->floor_length; i++)
    {
        for (int j = 0; j < ts->floor_length; j++)
        {
            (ts->floor_content)[i][j] = fgetc(fp);
        }
        fgetc(fp);
    }
}
static void copy_array(char **temp, tiling_solution *ts)
{
    for (int i = 0; i < ts->floor_length; i++)
    {
        for (int j = 0; j < ts->floor_length; j++)
        {
            temp[i][j] = (ts->floor_content)[i][j];
        }
    }
}
