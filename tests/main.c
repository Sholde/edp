#include "tests.h"

int main(int argc, char **argv)
{
  test_arithmetic_mean();
  test_geometric_mean();
  test_harmonic_mean();

  test_variance();
  test_standard_deviation();
  test_coeff_variation();

  test_median();
  test_mode();

  return 0;
}
