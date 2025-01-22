#include "answer03.h"
#include "aux03.h"

// the function performs numerical integration of the function
// double function_to_be_integrated(double) over the
// bounded interval lower_limit to upper_limit
//
// The bounded interval is divided into n_intervals contiguous uniform intervals
//
// The mid-point rule is used to perform the integration for each interval
// In the mid-point rule, the integration is approximated by using the
// area of a rectangle, where the height of the rectange is obtained by
// function_to_be_integrated(mid-point of the interval).  The width of
// the rectangle is (upper_limit - lower_limit)/n_intervals
// Note that width could be negative if upper_limit < lower_limit
//
// The integral is the sum of the integration over all intervals
//
// The caller function has to make sure that n_intervals >= 1
// Therefore, this function may assume that n_intervals >= 1
//
double mid_point_numerical_integration(double lower_limit, double upper_limit, int n_intervals)
{
   double integral = 0.0;
   int i;
   double mid = 0;
   double lower_limit_t = lower_limit;
   double upper_limit_t = upper_limit;

   for (i = 1; i <= n_intervals; i++)
   {
      if (i != n_intervals)
      {
         upper_limit_t = lower_limit + i * (upper_limit - lower_limit) / n_intervals;
         mid = (upper_limit_t + lower_limit_t) / 2.0;
         integral += (upper_limit_t - lower_limit_t) * function_to_be_integrated(mid);
         lower_limit_t = upper_limit_t;
      }
      else
      {
         mid = (upper_limit + lower_limit_t) / 2.0;
         integral += (upper_limit - lower_limit_t) * function_to_be_integrated(mid);
      }
   }
   return integral;
}

// the function performs numerical integration of the function
// double function_to_be_integrated(double) over the
// bounded interval lower_limit to upper_limit
//
// The bounded interval is divided into n_intervals contiguous uniform intervals
//
// The trapezoidal rule is used to perform the integration for each interval
// in the trapezoidal rule, the integration is approximated by the area of
// a trapezoid, where the heights of the parallel boundaries of the trapezoid
// are obtained by
// function_to_be_integrated(left boundary of the interval) and
// function_to_be_integrated(right boundary of the interval).
// The width of the trapezoid is (upper_limit - lower_limit)/n_intervals
// Note that width could be negative if upper_limit < lower_limit
// the area of a trapezoid is the average of the two heights multiplied by
// the width
//
// The integral is the sum of the integration over all intervals
//
// The caller function has to make sure that n_intervals >= 1
// Therefore, this function may assume that n_intervals >= 1
//
double trapezoidal_numerical_integration(double lower_limit, double upper_limit, int n_intervals)
{
   double integral = 0.0;
   int i;
   double h = 0;
   double lower_limit_t = lower_limit;
   double upper_limit_t = upper_limit;

   for (i = 1; i <= n_intervals; i++)
   {
      if (i != n_intervals)
      {
         upper_limit_t = lower_limit + i * (upper_limit - lower_limit) / n_intervals;
         h = (function_to_be_integrated(upper_limit_t) + function_to_be_integrated(lower_limit_t)) / 2.0;
         integral += (upper_limit_t - lower_limit_t) * h;
         lower_limit_t = upper_limit_t;
      }
      else
      {
         h = (function_to_be_integrated(upper_limit) + function_to_be_integrated(lower_limit_t)) / 2.0;
         integral += (upper_limit - lower_limit_t) * h;
      }
   }
   return integral;
}
