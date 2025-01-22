#include "answer04.h"

#include <stdio.h>
// Given intg_arg, this function performs numerical integration of
// the function intg_arg.func_to_be_integrated over the bounded interval
// intg_arg.lower_limit to intg_arg.upper_limit
//
// The bounded interval is divided into intg_arg.n_intervals continguous
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

      //    fprintf(stderr, "upper_limit = %f, lower_limit = %f, n = %d.\n", intg_arg.upper_limit, lower_limit_t, intg_arg.n_intervals);
      for (int i = 1; i <= intg_arg.n_intervals; i++)
      {
            upper_limit_t = lower_limit_t + width;
            mid = (lower_limit_t + upper_limit_t) / 2.0;
            integral += (width / 6) * (f(lower_limit_t) + 4 * f(mid) + f(upper_limit_t));
            lower_limit_t = upper_limit_t;
      }

      return integral;
}
