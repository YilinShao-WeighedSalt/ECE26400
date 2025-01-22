// to understand argc and argv
// to understand call stack

#include <stdlib.h>
#include <stdio.h>

//int main(int argc, char *argv[])
int main(int argc, char **argv)
{
/*
   int i;
   for (i = 0; i < argc; i++) {
      fprintf(stdout, "argv[%d]: %s\n", i, argv[i]);
   }
*/
   // a recursive version
   if (argc == 0) {
      return EXIT_SUCCESS;
   }
   main(argc-1, argv);
   fprintf(stdout, "argv[%d]: %s\n", argc-1, argv[argc-1]);
   return EXIT_SUCCESS;
}

























