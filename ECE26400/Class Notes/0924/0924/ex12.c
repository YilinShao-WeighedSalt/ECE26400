#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static void fscanf_demo(FILE *fptr, char *fmt_str)
{
   char *p1, *p2;
   p1 = p2 = NULL;
   errno = 0;
   fprintf(stdout, "%s\n", fmt_str);

   int n = fscanf(fptr, fmt_str, &p1, &p2);
   fprintf(stdout, "file position: %ld\n", ftell(fptr));
   if (n == 2) {
      fprintf(stdout, "converted 2: %s %s\n", p1, p2);
      free(p1);
      free(p2);
   } else if (n == 1) {
      fprintf(stdout, "converted 1: %s\n", p1);
      free(p1);
   } else {
      fprintf(stdout, "nothing converted\n");
   }
   if (errno != 0) {
      fprintf(stdout, "fscanf set errno %d\n", errno);
   }
   fprintf(stdout, "\n");
}

int main(int argc, char **argv)
{
   fprintf(stdout, "addresses: argc %p, argv %p\n", (void *)&argc, (void *)&argv);
   char str1[] = "%m[a-z]%*d%m[A-Z]";
   char *str2 = "%m[a-z] %*d %m[A-Z]";
   char str3[] = { '%', 'm', 's', '\0' };
   
   fprintf(stdout, "string lengths: str1 %zd, str2 %zd, str3 %zd\n", strlen(str1), strlen(str2), strlen(str3));
   fprintf(stdout, "sizeof: str1 %zd, str2 %zd, str3 %zd\n", sizeof(str1), sizeof(str2), sizeof(str3));
   fprintf(stdout, "addresses: str1 %p, str2 %p, str3 %p\n", (void *)&str1, (void *)&str2, (void *)&str3);
   fprintf(stdout, "addresses: str1[0] %p, str2[0] %p, str3[0] %p\n", &(str1[0]), &(str2[0]), &(str3[0]));

   if (argc != 2) {
      fprintf(stderr, "expect one filename\n");
      return EXIT_FAILURE;
   }

   char *fmt_strs[] = { str1, str2, str3 };
   FILE *fptr = fopen(argv[1], "r");
   if (fptr == NULL) {
      fprintf(stderr, "input file cannot be opened\n");
      return EXIT_FAILURE;
   }
   int i;
   for (i = 0; i < sizeof(fmt_strs)/sizeof(fmt_strs[0]); i++) {
      fprintf(stdout, "format string: %s\n\n", fmt_strs[i]);
      fseek(fptr, 0L, SEEK_SET);
      fscanf_demo(fptr, fmt_strs[i]);
   }

   fclose(fptr);

/*
   char c1, c2;
   scanf("%c %hhd", &c1, (signed char *)&c2);

   fprintf(stdout, "%c %hhd %c %hhd\n", c1, c1, c2, c2);
*/

   return EXIT_SUCCESS;
}
