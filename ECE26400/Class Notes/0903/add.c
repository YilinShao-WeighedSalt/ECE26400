#include <stdio.h>
#include "add.h"

void add(long i, long j, long *result)
{
   result[0] = i + j;
   i = i+1;
   j = j-2;
}
