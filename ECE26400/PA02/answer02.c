#include <math.h>

#include "answer02.h"

// Given intg_arg, this function performs numerical integration of
// the function intg_arg.func_to_be_integrated over the range
// intg_arg.lower_limit to intg_arg.upper_limit
//
// The bounded interval is divided into intg_arg.n_intervals contiguous
// uniform intervals
//
// The Simpson's rule is used to perform the integration for each interval
//
// The integral is the sum of the integration over all intervals
//
// The caller function has to make sure that intg_arg.n_intervals >= 1
// Therefore, this function may assume that intg_arg.n_intervals >= 1
//
double simpson_numerical_integration(integrand intg_arg)
{
   double integral = 0.0;
   double lower_limit_t = intg_arg.lower_limit;
   double upper_limit_t;
   double mid = 0;
   double width = (intg_arg.upper_limit - intg_arg.lower_limit) / intg_arg.n_intervals;
   double (*f)(double) = intg_arg.func_to_be_integrated;

   // fprintf(stderr, "upper_limit = %f, lower_limit = %f, n = %d.\n", intg_arg.upper_limit, lower_limit_t, intg_arg.n_intervals);
   for (int i = 1; i <= intg_arg.n_intervals; i++)
   {
      upper_limit_t = lower_limit_t + width;
      mid = (lower_limit_t + upper_limit_t) / 2.0;
      integral += (width / 6) * (f(lower_limit_t) + 4 * f(mid) + f(upper_limit_t));
      lower_limit_t = upper_limit_t;
   }
   return integral;
}

// Given intg_arg, this function performs numerical integration over the
// range of intg_arg.lower_limit to intg_arg.upper_limit of f(x):
//
// f(x) = intg_arg.func_to_be_integrated(x) * cos_sin((n * M_PI * x)/L),
//
// where 2L = intg_arg.upper_limit - intg_arg.lower_limit = period
//
// The bounded interval is divided into intg_arg.n_intervals contiguous
// uniform intervals
//
// The Simpson's rule is used to perform the integration for each interval
//
// The integral is the sum of the integration over all intervals
//
// The caller function has to make sure that intg_arg.n_intervals >= 1
// Therefore, this function may assume that intg_arg.n_intervals >= 1
//
// The caller function should also pass in n >= 0
//
// The caller function should also pass in cos or sin for the function
// cos_sin.
//
double simpson_numerical_integration_for_fourier(integrand intg_arg, int n, double (*cos_sin)(double))
{
   double integral = 0.0;
   double lower_limit_t = intg_arg.lower_limit;
   double upper_limit_t;
   double mid = 0;
   double width = (intg_arg.upper_limit - intg_arg.lower_limit) / intg_arg.n_intervals;
   double (*f)(double) = intg_arg.func_to_be_integrated;
   double L = (intg_arg.upper_limit - intg_arg.lower_limit) / 2;
   //    fprintf(stderr, "upper_limit = %f, lower_limit = %f, n = %d.\n", intg_arg.upper_limit, lower_limit_t, intg_arg.n_intervals);
   for (int i = 1; i <= intg_arg.n_intervals; i++)
   {
      upper_limit_t = lower_limit_t + width;
      mid = (lower_limit_t + upper_limit_t) / 2.0;
      integral += (width / 6) * (f(lower_limit_t) * cos_sin(n * M_PI * lower_limit_t / L) + 4 * f(mid) * cos_sin(n * M_PI * mid / L) + f(upper_limit_t) * cos_sin(n * M_PI * upper_limit_t / L));
      lower_limit_t = upper_limit_t;
   }
   return integral;
}

// Given fourier_arg, this function computes
// Fourier coefficients a_0, a_1, ..., a_{fourier_arg.n_terms-1} and stores
// them as fourier_arg.a_i[0], fourier_arg.a_i[1], and so on, and
// b_1, ..., b_{fourier_arg.n_terms-1} and stores them as fourier_arg.b_i[1],
// fourier_arg.b_i[2], and so on.
//
// The period is defined to be
//    fourier_arg.intg.upper_limit - fourier_arg.intg.lower_limit
//
// The function simpson_numerical_integration is used in the process of
// computing a_0.  fourier_arg.intg should be passed to the function.
//
// The function simpson_numerical_integration_for_fourier is used in the
// process of computing a_1, ... and b_1, ...
// fourier_arg.intg should be passed, appropriate n >= 0, and either sin or
// cos function should also be passed.
//
// The caller function should pass into this function fourier_arg.n_terms >= 1
//
// The caller function should also allocate space to store the coefficients
// a_0, a_1, ..., b_1, ...
//
// The caller function should ensure that the period is not 0.
//
void compute_fourier_coefficients(fourier fourier_arg)
{
   double L = (fourier_arg.intg.upper_limit - fourier_arg.intg.lower_limit) / 2;

   fourier_arg.a_i[0] = (1 / L) * simpson_numerical_integration(fourier_arg.intg);
   for (int i = 1; i <= fourier_arg.n_terms - 1; i++)
   {
      fourier_arg.a_i[i] = (1 / L) * simpson_numerical_integration_for_fourier(fourier_arg.intg, i, cos);
      fourier_arg.b_i[i] = (1 / L) * simpson_numerical_integration_for_fourier(fourier_arg.intg, i, sin);
   }
   return;
}
