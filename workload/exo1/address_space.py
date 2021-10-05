#!/bin/python

import numpy as np

array_a = np.loadtxt("trace_a.data")
array_b = np.loadtxt("trace_b.data")
array_c = np.loadtxt("trace_c.data")

min_a=0.0
min_b=0.0
min_c=0.0

max_a=0.0
max_b=0.0
max_c=0.0

count_a=0.0
count_b=0.0
count_c=0.0

for i in range(25000):
    count_a += array_a[i][4]

    if (array_a[i][3] < min_a):
        min_a = array_a[i][3]

    if (array_a[i][3] + array_a[i][4] > max_a):
        max_a = array_a[i][3] + array_a[i][4]

    count_b += array_b[i][4]

    if (array_b[i][3] < min_b):
        min_b = array_b[i][3]

    if (array_b[i][3] + array_b[i][4] > max_b):
        max_b = array_b[i][3] + array_b[i][4]

    count_c += array_c[i][4]

    if (array_c[i][3] < min_c):
        min_c = array_c[i][3]

    if (array_c[i][3] + array_c[i][4] > max_c):
        max_c = array_c[i][3] + array_c[i][4]


#
index=0
my_max=0.0
addr_space=[max_a - min_a, max_b - min_b, max_c - min_c]
min_max=[[min_a, max_a], [min_b, max_b], [min_c, max_c]]

for i in range(len(addr_space)):
    if (addr_space[i] > my_max):
        my_max=addr_space[i]
        index=i

list_of_files=["trace_a.data", "trace_b.data", "trace_c.data"]

for i in range(len(addr_space)):
    print("{}: {} to {} address space".format(list_of_files[i], min_max[i][0], min_max[i][1]))

print()
print("Longest address space:")
print("{}: {} to {} address space".format(list_of_files[index], min_max[index][0], min_max[index][1]))
