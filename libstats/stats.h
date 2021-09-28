#ifndef _STATS_H_
#define _STATS_H_

double arithmetic_mean(double *array, unsigned long long size);
double geometric_mean(double *array, unsigned long long size);
double harmonic_mean(double *array, unsigned long long size);

double variance(double *array, unsigned long long size, double mean);
double standard_deviation(double *array, unsigned long long size, double mean);
double coeff_variation(double stddev, double mean);

double median(double *array, unsigned long long size);
double mode(double *array, unsigned long long size);

#endif // _STATS_H_
