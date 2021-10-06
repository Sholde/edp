#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "stats.h"

// mean = (x_1 + ... + x_n) / size
u64 arithmetic_mean(u64 *array, u64 size)
{
  if (size == 0 || array == NULL)
    return 0.0;

  u64 mean = 0.0;

  for (u64 i = 0; i < size; ++i)
    mean += array[i];

  mean /= size;

  return mean;
}

// var = (1 / (n - 1)) * ((x_1 - mean)^2 + ... + (x_n - mean)^2)
double variance(u64 *array, u64 size, u64 mean)
{
  double var = (double)1.0 / (double)(size - 1);
  double sum = 0.0;

  for (u64 i = 0; i < size; ++i)
    sum += (array[i] - mean) * (array[i] - mean);

  var *= sum;

  return var;
}

// stddev = sqrt(var)
double standard_deviation(u64 *array, u64 size, u64 mean)
{
  double var = variance(array, size, mean);
  return sqrt(var);
}

// coeff = stddev / mean
double coeff_variation(double stddev, u64 mean)
{
  return stddev / mean;
}

// sort array of u64
static int sort_u64(const void *x, const void *y)
{
  return (*(u64 *)x - *(u64 *)y);
}

//
u64 median(u64 *array, u64 size)
{
  u64 *copy = aligned_alloc(ALIGNED, sizeof(u64) * size);

  for (u64 i = 0; i < size; i++)
    copy[i] = array[i];

  qsort(copy, size, sizeof(u64), sort_u64);
  u64 med = copy[(u64)(size / 2)];

  free(copy);

  return med;
}

//
u64 mode(u64 *array, u64 size)
{
  qsort(array, size, sizeof(u64), sort_u64);

  u64 old_count = 0;
  u64 new_count = 0;
  u64 value = 0.0;
  u64 old_value = 0.0;

  for (u64 i = 0; i < size; ++i)
    {
      if (array[i] == old_value)
        {
          new_count++;
          if (new_count >= old_count)
            value = array[i];
        }
      else
        {
          new_count = 1;
        }

      old_value = array[i];
    }

  return value;
}
