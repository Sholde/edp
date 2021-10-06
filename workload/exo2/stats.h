#ifndef _STATS_H_
#define _STATS_H_

#define ALIGNED 64

typedef unsigned long long u64;

u64 arithmetic_mean(u64 *array, u64 size);

double variance(u64 *array, u64 size, u64 mean);
double standard_deviation(u64 *array, u64 size, u64 mean);
double coeff_variation(double stddev, u64 mean);

u64 median(u64 *array, u64 size);
u64 mode(u64 *array, u64 size);

#endif // _STATS_H_
