#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
   if (argc != 3) {
      fprintf(stderr, "expect 2 filenames\n");
      return EXIT_FAILURE;
   }
   FILE *ifp = fopen(argv[1], "r");
   if (ifp == NULL) {
      fprintf(stderr, "input file cannot be opened\n");
      return EXIT_FAILURE;
   }
   FILE *ofp = fopen(argv[2], "w");
   if (ofp == NULL) {
      fprintf(stderr, "output file cannot be opened\n");
      fprintf(stderr, "print to stdout instead\n");
      ofp = stdout;
   }

   fseek(ifp, 0L, SEEK_END); // go to end of file
   fprintf(stderr, "file size: %ld\n", ftell(ifp));

   while (ftell(ifp) != 0) {
      fseek(ifp, -1L, SEEK_CUR);
      fputc(fgetc(ifp), ofp);
      fseek(ifp, -1L, SEEK_CUR);
   }

   fclose(ifp);
   if (ofp != stdout) {
      fclose(ofp);
   }
   return EXIT_SUCCESS;
}
