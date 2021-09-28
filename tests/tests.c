#include <assert.h>

#include "stats.h"
#include "tests.h"

void test_arithmetic_mean(void)
{
  // Basic case
  double basic[10] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
  assert(arithmetic_mean(basic, 10) == 5.5);

  // Negative case
  double negative[10] =
    { 1.0, 2.0, 3.0, 4.0, 5.0, -2.0, -3.0, -4.0, -5.0, -6.0 };
  assert(arithmetic_mean(negative, 10) == -0.5);

  // Size null
  double null[1] = { 1.0 };
  assert(arithmetic_mean(null, 0) == 0.0);
}

void test_geometric_mean(void)
{
  // Basic case
  double basic[5] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
  assert((geometric_mean(basic, 5) - 2.605171e+00) < EPSILON);

  // Negative case
  double negative[5] = { -2.0, -1.0, 1.0, 2.0, 3.0 };
  assert((geometric_mean(negative, 5) - 1.643752e+00) < EPSILON);

  // Size null
  double null[1] = { 1.0 };
  assert(geometric_mean(null, 0) == 0.0);
}

void test_harmonic_mean(void)
{
  // Basic case
  double basic[5] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
  assert((harmonic_mean(basic, 5) - 2.189781e+00) < EPSILON);

  // Negative case
  double negative[5] = { -2.0, -1.0, 1.0, 2.0, 3.0 };
  assert((harmonic_mean(negative, 5) - 1.500000e+01) < EPSILON);

  // Size null
  double null[1] = { 1.0 };
  assert(harmonic_mean(null, 0) == 0.0);
}

void test_variance(void)
{
  //
  double mean = 0.0;

  // Basic case
  double basic[5] = { 1.0, 2.0, 3.0, 4.0, 5.0 };

  // With arithmetic mean
  mean = arithmetic_mean(basic, 5);
  assert(variance(basic, 5, mean) == 2.5);

  // With geometric mean
  mean = geometric_mean(basic, 5);
  assert((variance(basic, 5, mean) - 2.694862e+00) < EPSILON);

  // With harmonic mean
  mean = harmonic_mean(basic, 5);
  assert((variance(basic, 5, mean) - 3.320568e+00) < EPSILON);

  // Negative case
  double negative[5] = { -2.0, -1.0, 1.0, 2.0, 3.0 };

  // With arithmetic mean
  mean = arithmetic_mean(negative, 5);
  assert((variance(negative, 5, mean) - 4.300000e+00) < EPSILON);

  // With geometric mean
  mean = geometric_mean(negative, 5);
  assert((variance(negative, 5, mean) - 5.661772e+00) < EPSILON);

  // With harmonic mean
  mean = harmonic_mean(negative, 5);
  assert((variance(negative, 5, mean) - 2.635000e+02) < EPSILON);

  // Size null
  double null[1] = { 1.0 };
  assert(variance(null, 0, mean) == 0.0);
}

void test_standard_deviation(void)
{
  // one case
  double array[5] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
  double mean = arithmetic_mean(array, 5);
  assert((standard_deviation(array, 5, mean) - 1.581139e+00) < EPSILON);
}

void test_coeff_variation(void)
{
  // one case
  double array[5] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
  double mean = arithmetic_mean(array, 5);
  double var = variance(array, 5, mean);
  assert((coeff_variation(var, mean) - 8.333333e-01) < EPSILON);
}

void test_median(void)
{
  // Basic case
  double basic[5] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
  assert(median(basic, 5) == 3.0);

  // Negative case
  double negative[5] = { -2.0, -1.0, 1.0, 2.0, 3.0 };
  assert(median(negative, 5) == 1.0);

  // Even case
  double even[6] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
  assert(median(even, 5) == 3.0);

  // Odd case
  double odd[5] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
  assert(median(odd, 5) == 3.0);

  // Not sort case
  double not_sort[5] = { 5.0, -1.0, 6.0, 1.0, -4.0 };
  assert(median(not_sort, 5) == 1.0);
}

void test_mode(void)
{
  // Basic case
  double basic[5] = { 1.0, 2.0, 1.0, 2.0, 2.0 };
  assert(mode(basic, 5) == 2.0);
}
