#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>

#include "bit_pattern.h"

static void check_for_inf_nan(float f);

int main(int argc, char **argv)
{
   // sizes of char, short, int, long, long long

   fprintf(stdout, "sizes of char, short, int, long, and long long\n\n");

   char c;
   unsigned char uc;
   short s;
   unsigned short us;
   int i;
   unsigned int ui;
   long l;
   unsigned long ul;
   long long ll;
   unsigned long long ull;
   fprintf(stdout, "%zd %zd %zd %zd %zd %zd %zd %zd %zd %zd\n", sizeof(c), sizeof(uc),
           sizeof(s), sizeof(us), sizeof(i), sizeof(ui), sizeof(l), sizeof(ul),
           sizeof(ll), sizeof(ull));

   // addresses are 8 bytes on a 64-bit machine

   fprintf(stdout, "sizes of addresses\n\n");

   char *caddr = &c;
   long *laddr = &l;
   fprintf(stdout, "%zd %zd %p %p\n", sizeof(caddr), sizeof(laddr), (void *)caddr, (void *)laddr);

   // sizes of float, double, long double

   fprintf(stdout, "sizes of float, double, long double\n\n");

   float f;
   double d;
   long double ld;
   fprintf(stdout, "%zd %zd %zd\n", sizeof(f), sizeof(d), sizeof(ld));
   fprintf(stdout, "%p %p %p\n", (void *)&f, (void *)&d, (void *)&ld);

   f = 6.75f;
   fprintf(stdout, "%.30f\n", f);
   print_a_byte_array(&f, sizeof(f));

   float fa, fb, fc;
   fa = 0.0f;
   fb = 1.0f;
   fc = fa/fb;
   fprintf(stdout, "%.30f / %.30f = %.30f\n", fa, fb, fc);
   print_a_byte_array(&fa, sizeof(fa));
   print_a_byte_array(&fb, sizeof(fb));
   print_a_byte_array(&fc, sizeof(fc));

   // check for infinity or not a number

   check_for_inf_nan(fc);

   // introducing infinity

   fc = fb/fa;
   fprintf(stdout, "%.30f / %.30f = %.30f\n", fb, fa, fc);
   print_a_byte_array(&fc, sizeof(fc));

   check_for_inf_nan(fc);

   // negating infinity gives us negative infinity

   fprintf(stdout, "-%.30f = %.30f\n", fc, -fc);
   fc = -fc;                            
   print_a_byte_array(&fc, sizeof(fc));
   check_for_inf_nan(fc);

   // introducing not a number nan

   fprintf(stdout, "%.30f - %.30f = %.30f\n", fc, fc, fc - fc);
   fc = fc - fc;
   print_a_byte_array(&fc, sizeof(fc));
   check_for_inf_nan(fc);

   // introducing floating point error

   float fd, fe, ff;

   fd = 3.14159265358979323846f;  // PI

   fe = 0.0f;

   ff = fd/(100000.0f);               // divide PI by 100000

   for (i = 0; i < 100000; i++) {
      fe = fe + ff;
   }
   fprintf(stdout, "3.14159265358979323846 %.30f %.30f %.30f\n", fd, fe, ff*100000.0f);
   print_a_byte_array(&fd, sizeof(fd));
   print_a_byte_array(&fe, sizeof(fe));

   fd = FLT_MAX;
   fe = 1.0e38;
   ff = fd + fe;
   fprintf(stdout, "%.30e + %.30e = %.30e\n", fd, fe, ff);
   print_a_byte_array(&fd, sizeof(fd));
   print_a_byte_array(&fe, sizeof(fe));
   print_a_byte_array(&ff, sizeof(ff));
   check_for_inf_nan(ff);

   return EXIT_SUCCESS;
}

static void check_for_inf_nan(float f)
{
   if (isinf(f)) {
      fprintf(stdout, "%.30f is infinity (positive or negative)\n", f);
   } else {
      fprintf(stdout, "%.30f is not infinity (positive or negative)\n", f);
   }

   if (isnan(f)) {
      fprintf(stdout, "%.30f is not a number (positive or negative)\n", f);
   } else {
      fprintf(stdout, "%.30f is not nan (positive or negative)\n", f);
   }
}

