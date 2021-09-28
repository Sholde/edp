#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "stats.h"

// mean = (x_1 + ... + x_n) / size
double arithmetic_mean(double *array, unsigned long long size)
{
  if (size == 0 || array == NULL)
    return 0.0;

  double mean = 0.0;

  for (unsigned long long i = 0; i < size; ++i)
    mean += array[i];

  mean /= size;

  return mean;
}

// mean = (x_1 * ... * x_n)^(1 / size)
double geometric_mean(double *array, unsigned long long size)
{
  if (size == 0 || array == NULL)
    return 0.0;

  double mean = 1.0;

  for (unsigned long long i = 0; i < size; ++i)
    mean *= array[i];

  mean = pow(mean, (double)1.0 / (double)size);

  return mean;
}

// mean = size / (1 / x_1 + ... + 1 / x_n)
double harmonic_mean(double *array, unsigned long long size)
{
  if (size == 0 || array == NULL)
    return 0.0;

  double mean = 0.0;
  double frac = 0.0;

  for (unsigned long long i = 0; i < size; ++i)
    frac += (double)1.0 / array[i];

  mean = size / frac;

  return mean;
}

// var = (1 / (n - 1)) * ((x_1 - mean)^2 + ... + (x_n - mean)^2)
double variance(double *array, unsigned long long size, double mean)
{
  double var = (double)1.0 / (double)(size - 1);
  double sum = 0.0;

  for (unsigned long long i = 0; i < size; ++i)
    sum += (array[i] - mean) * (array[i] - mean);

  var *= sum;

  return var;
}

// stddev = sqrt(var)
double standard_deviation(double *array, unsigned long long size, double mean)
{
  double var = variance(array, size, mean);
  return sqrt(var);
}

// coeff = stddev / mean
double coeff_variation(double stddev, double mean)
{
  return stddev / mean;
}

// sort array of double
static int sort_double(const void *x, const void *y)
{
  return (*(double *)x - *(double *)y);
}

//
double median(double *array, unsigned long long size)
{
  qsort(array, size, sizeof(double), sort_double);
  double med = array[(unsigned long long)(size / 2)];

  return med;
}

//
double mode(double *array, unsigned long long size)
{
  qsort(array, size, sizeof(double), sort_double);

  unsigned long long old_count = 0;
  unsigned long long new_count = 0;
  double value = 0.0;
  double old_value = 0.0;

  for (unsigned long long i = 0; i < size; ++i)
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
