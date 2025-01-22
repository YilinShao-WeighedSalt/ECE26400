#include <stdlib.h>
#include <string.h>

#include "answer04.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Not enouth argument\n");
        return EXIT_FAILURE;
    }
    int inp_length = strlen(argv[1]);
    if (!(inp_length > 4 && argv[1][inp_length - 4] == '.' && argv[1][inp_length - 3] == 'b' && argv[1][inp_length - 2] == 'm' && argv[1][inp_length - 1] == 'p'))
    {
        fprintf(stderr, "Invalid input file format\n");
        return EXIT_FAILURE;
    }

    // Validate that output file has .bmp extension
    int out_length = strlen(argv[2]);
    if (!(out_length > 4 && argv[2][out_length - 4] == '.' && argv[2][out_length - 3] == 'b' && argv[2][out_length - 2] == 'm' && argv[2][out_length - 1] == 'p'))
    {
        fprintf(stderr, "Invalid output file format\n");
        return EXIT_FAILURE;
    }
    BMP_image *image = read_BMP_image(argv[1]);
    if (image == NULL)
    {
        fprintf(stderr, "Invalid intput file\n");
        return EXIT_FAILURE;
    }

    BMP_image *new_image;
    if (image->header.bits == 24)
    {
        new_image = convert_24_to_16_BMP_image(image);
        if (new_image == NULL)
        {
            fprintf(stderr, "Conversion Failed\n");
            free_BMP_image(image);
            return EXIT_FAILURE;
        }
    }
    else if (image->header.bits == 16)
    {
        new_image = convert_16_to_24_BMP_image(image);
        if (new_image == NULL)
        {
            fprintf(stderr, "Conversion Failed\n");
            free_BMP_image(image);
            return EXIT_FAILURE;
        }
    }
    else
    {
        fprintf(stderr, "bit is not matched:%d\n", image->header.bits);
        free_BMP_image(image);
        return EXIT_FAILURE;
    }
    if (!write_BMP_image(argv[2], new_image))
    {
        free(image);
        free_BMP_image(new_image);
        return EXIT_FAILURE;
    }
    free_BMP_image(image);
    free_BMP_image(new_image);
    return EXIT_SUCCESS;
}