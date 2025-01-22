#include "aux02.h"
#include <math.h>
double unknown_function_1(double x)
{
    return sin(pow(x,2)) + cos(pow(x,2)) + tan(x) + x;
}

double unknown_function_2(double x)
{
    return cos(x);
}

double unknown_function_3(double x)
{
    return sin(cos(pow(x, 2)));
}
