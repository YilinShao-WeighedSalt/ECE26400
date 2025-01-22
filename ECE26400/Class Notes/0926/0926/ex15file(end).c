#include <stdio.h>
#include <stdlib.h>

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

static char **read_file_into_array(char *filename, int *size)
{
   *size = 0;
   FILE *fp = fopen(filename, "r");
   if (fp == NULL) {
      return NULL;
   }
   int count = count_lines(fp);

   fseek(fp, 0L, SEEK_END);
   long fsize = ftell(fp);
   char **array = malloc((sizeof(*array) * count) + (sizeof(*(array[0])) * fsize));
   if ((array == NULL) || (count == 0)) {
      fclose(fp);
      return array;
   }
   array[0] = (char *)&(array[count]);
   fseek(fp, 0L, SEEK_SET);
   if (fread(array[0], sizeof(*(array[0])), fsize, fp) != fsize) {
      free(array);
      fclose(fp);
      return NULL;
   }
   fclose(fp);

   *size = count;
   int i = 0;
   char *ptr = array[0];
   for (i = 0; i < count; i++) {
      array[i] = ptr;
      while (*ptr != '\n') {
         ptr++;
      }
      *ptr = '\0';
      ptr++;
   }
   return array;
}

static int write_fp_from_array(FILE *fp, char **array, int size)
{
   if (size <= 0) {
      return 1;
   }
   char *ptr = array[0];
   int i;
   for (i = 0; i < size; i++) {
      while (*ptr != '\0') {
         if (fputc(*ptr, fp) != *ptr) {
            return 0;
         }
         ptr++;
      }
      if (fputc('\n', fp) != '\n') {
         return 0;
      }
      ptr++;
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
   
   free(array);

   if (write_status != 1) {
      fprintf(stderr, "can't write properly\n");
      return EXIT_FAILURE;
   }

   write_fp_from_array(stdout, argv, argc);

   return EXIT_SUCCESS;
}
