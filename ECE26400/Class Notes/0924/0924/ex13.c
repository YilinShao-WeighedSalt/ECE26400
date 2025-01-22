// assume that all lines are terminated with a newline
//
#include <stdio.h>
#include <stdlib.h>

static void destroy_array(char **array, int size)
{
   int i;
   for (i = 0; i < size; i++) {
      free(array[i]);
   }
   free(array);
}

static int count_lines(FILE *fp) 
{
   fseek(fp, 0L, SEEK_SET);
   int count = 0;
   int ch;
   while ((ch = fgetc(fp)) != EOF) {
      if (ch == '\n') 
         count++;
   }
   return count;
}

static char *form_string(char ch, FILE *fp) 
{
   long fpos = ftell(fp) - 1;
   while (ch != '\n') {
      ch = fgetc(fp);
   }
   long new_fpos = ftell(fp);
   int string_length = new_fpos - fpos;
   char *str = malloc(sizeof(*str) * string_length);
   if (str == NULL) {
      return NULL;
   }
   fseek(fp, -string_length, SEEK_CUR);
   int j = 0;
   while ((str[j] = fgetc(fp)) != '\n') {
      j++;
   }
   str[j] = '\0';
   return str;
}

static char **read_file_into_array(char *filename, int *size)
{
   *size = 0;
   FILE *fp = fopen(filename, "r");
   if (fp == NULL) {
      return NULL;
   }
   int count = count_lines(fp);

   char **array = malloc(sizeof(*array) * count);
   if (array == NULL) {
      fclose(fp);
      return NULL;
   }

   fseek(fp, 0L, SEEK_SET);
   count = 0;
   int ch;
   while ((ch = fgetc(fp)) != EOF) {
      array[count] = form_string(ch, fp);
      if (array[count] == NULL) {
         destroy_array(array, count);
         fclose(fp);
         return NULL;
      }
      count++;
   }
   *size = count;
   fclose(fp);
   return array;
}

static int write_fp_from_array(FILE *fp, char **array, int size) 
{
   for (int i = 0; i < size; i++) {
      if (fprintf(fp, "%s\n", array[i]) < 1) {
         return 0;
      }
   }
   return 1;
}

static int write_file_from_array(char *filename, char **array, int size)
{
   FILE *fp = fopen(filename, "w");
   if (fp == NULL) {
      return -1;
   }
   int status = write_fp_from_array(fp, array, size);
   fclose(fp);
   return status;
}

int main(int argc, char **argv)
{
   if (argc != 3) {
      fprintf(stderr, "expect two filenames\n");
      return EXIT_FAILURE;
   }

   int size;
   char **array = read_file_into_array(argv[1], &size);

   if (array == NULL) {
      fprintf(stderr, "can't read file or memory error\n");
      return EXIT_FAILURE;
   }
   
   int write_status = write_file_from_array(argv[2], array, size);
   
   destroy_array(array, size);

   if (write_status != 1) {
      fprintf(stderr, "can't write properly\n");
      return EXIT_FAILURE;
   }

   write_fp_from_array(stdout, argv, argc);

   return EXIT_SUCCESS;
}
