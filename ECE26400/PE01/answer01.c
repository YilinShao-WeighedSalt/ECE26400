#include "answer01.h"

/* Return the smallest partial sum of the array */
/* int array[] = { 1, 4, -1, 6, -5, 4} */
/* the (i,j)-th partial sum is the sum from array[i] through array[j], i<=j */
/* the (0,0)-(0,5)-th partial sums are 1, 5, 4, 10, 5, 9 */
/* the (1,1)-(1,5)-th partial sums are 4, 3, 9, 4, 8 */
/* the (2,2)-(2,5)-th partial sums are -1, 5, 0, 4 */
/* the (3,3)-(3,5)-th partial sums are 6, 1, 5 */
/* the (4,4)-(4,5)-th partial sums are -5, -1 */
/* the (5,5)-th partial sum is 4 */
/* the smallest partial sum of the array is therefore -5 */
/* if the len is 0, the smallest partial sum is 0 */
/* you may call this function only when the array is non-NULL */
/* you may assume that none of the partial sums will cause underflow/overflow */

int smallest_partial_sum(int *array, int len)
{
   int i, j;

   if (len == 0)
   {
      return 0;
   }
   else
   {
      int min_sum = array[0];
      for (i = 0; i < len; i++)
      {
         int sum = 0;
         for (j = i; j < len; j++)
         {
            sum += array[j];
            if (sum < min_sum)
            {
               min_sum = sum;
            }
         }
      }
      return min_sum;
   }
}

/* Return the largest difference of the array */
/* int array[] = { 1, 4, -1, 6, -5, 4} */
/* the largest difference is 6 - (-5) = 11 */
/* if the len is 0, the largest difference is 0 */
/* if the len is 1, the largest difference is also 0 */
/* you may call this function only when the array is non-NULL */
/* you may assume that the largest difference will not cause an overflow */

int largest_difference(int *array, int len)
{
   // int diff = 0;

   if (len == 0 || len == 1)
   {
      return 0;
   }

   int max_val = array[0];
   int min_val = array[0];

   for (int i = 1; i < len; i++)
   {
      if (array[i] > max_val)
      {
         max_val = array[i];
      }
      if (array[i] < min_val)
      {
         min_val = array[i];
      }
   }

   return max_val - min_val;
   // else
   // {
   //    // sort
   //    for (int i = 0; i < len - 1; i++)
   //    {
   //       for (int j = 0; j < len - i - 1; j++)
   //       {
   //          if (array[j] > array[j + 1])
   //          {
   //             int temp = array[j];
   //             array[j] = array[j + 1];
   //             array[j + 1] = temp;
   //          }
   //       }
   //    }
   //    diff = array[len - 1] - array[0];
   //    return diff;
   // }
}
