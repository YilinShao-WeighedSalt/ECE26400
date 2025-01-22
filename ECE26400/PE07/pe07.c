#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "answer07.h"

int main(int argc, char **argv)
{
    if (argc <= 2)
    {
        fprintf(stderr, "Not enouth argument\n");
        return EXIT_FAILURE;
    }

    char *input_file = argv[argc - 2];
    char *output_file = argv[argc - 1];
    BMP_image *image = read_BMP_image(input_file);
    if (image == NULL)
        return EXIT_FAILURE;
    BMP_image *reflectedimage = image;
    for (int i = 1; i < argc - 2; i++)
    {
        int vrefl = 0;
        int hrefl = 0;
        if (strcmp(argv[i], "-v") == 0)
        {
            vrefl = true;
        }
        else if (strcmp(argv[i], "-h") == 0)
        {
            hrefl = true;
        }
        else
        {
            fprintf(stderr, "Invalid option\n");
            free_BMP_image(reflectedimage);
            return EXIT_FAILURE;
        }
        BMP_image *new_image = reflect_BMP_image(reflectedimage, hrefl, vrefl);
        if (new_image == NULL)
        {
            if (reflectedimage != image)
                free_BMP_image(reflectedimage);
            return EXIT_FAILURE;
        }
        if (reflectedimage != image)
            free_BMP_image(reflectedimage);
        reflectedimage = new_image;
    }

    if (!write_BMP_image(output_file, reflectedimage))
    {
        if (reflectedimage != image)
            free_BMP_image(reflectedimage);
        return EXIT_FAILURE;
    }
    if (reflectedimage != image)
        free_BMP_image(reflectedimage);
    free_BMP_image(image);
    return EXIT_SUCCESS;
}