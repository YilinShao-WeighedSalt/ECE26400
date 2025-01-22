#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
   if (argc != 4) {
      fprintf(stderr, "expect one input file, two output files\n");
      return EXIT_FAILURE;
   }
   FILE *ifp = fopen(argv[1], "r");
   if (ifp == NULL) {
      fprintf(stderr, "can't open input file\n");
      return EXIT_FAILURE;
   }
   FILE *ofp_fgetc = fopen(argv[2], "w");
   if (ofp_fgetc == NULL) {
      fprintf(stderr, "can't open first output file\n");
      fclose(ifp);
      return EXIT_FAILURE;
   }

   int ch;
   while ((ch = fgetc(ifp)) != EOF) {
      fputc(ch, ofp_fgetc);
   }
   // move 10 positions beyond the end of file

   fseek(ofp_fgetc, 10L, SEEK_END);

   // write one more char to the file, all 10 positions
   // before that written with 0

   fputc('\n', ofp_fgetc);
   fclose(ofp_fgetc); 

   FILE *ofp_fscanf = fopen(argv[3], "w");
   if (ofp_fscanf == NULL) {
      fprintf(stderr, "can't open second output file\n");
      fclose(ifp);
      return EXIT_FAILURE;
   }

   fseek(ifp, 0L, SEEK_SET);

   char c;
   while (fscanf(ifp, "%c", &c) == 1) {
      fprintf(ofp_fscanf, "%c", c);
   }
   fclose(ofp_fscanf); 

   fclose(ifp);
   return EXIT_SUCCESS;
}
