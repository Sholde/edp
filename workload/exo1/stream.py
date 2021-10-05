#!/bin/python

import numpy as np

array_a = np.loadtxt("trace_a.data")
array_b = np.loadtxt("trace_b.data")
array_c = np.loadtxt("trace_c.data")

count_a=0
count_b=0
count_c=0

tmp_count_a=0
tmp_count_b=0
tmp_count_c=0

flux_a=0
flux_b=0
flux_c=0

tmp_flux_a=0
tmp_flux_b=0
tmp_flux_c=0

for i in range(25000):
    if (array_a[i][2] == 0):
        tmp_count_a += array_a[i][4]
        tmp_flux_a += 1
    else:
        if (count_a < tmp_count_a):
            count_a = tmp_count_a
            flux_a = tmp_flux_a

        tmp_count_a = 0
        tmp_flux_a = 0

    if (array_b[i][2] == 0):
        tmp_count_b += array_b[i][4]
        tmp_flux_b += 1
    else:
        if (count_b < tmp_count_b):
            count_b = tmp_count_b
            flux_b = tmp_flux_b

        tmp_count_b = 0
        tmp_flux_b = 0

    if (array_c[i][2] == 0):
        tmp_count_c += array_c[i][4]
        tmp_flux_c += 1
    else:
        if (count_c < tmp_count_c):
            count_c = tmp_count_c
            flux_c = tmp_flux_c

        tmp_count_c = 0
        tmp_flux_c = 0

if (count_a < tmp_count_a):
    count_a = tmp_count_a
if (count_b < tmp_count_b):
    count_b = tmp_count_b
if (count_c < tmp_count_c):
    count_c = tmp_count_c
if (flux_a < tmp_flux_a):
    flux_a = tmp_flux_a
if (flux_b < tmp_flux_b):
    flux_b = tmp_flux_b
if (flux_c < tmp_flux_c):
    flux_c = tmp_flux_c

list_of_files=["trace_a.data", "trace_b.data", "trace_c.data"]
count=[count_a, count_b, count_c]
flux=[flux_a, flux_b, flux_c]

for i in range(len(list_of_files)):
    print("{}: {} size and {} read stream".format(list_of_files[i], count[i], flux[i]))
