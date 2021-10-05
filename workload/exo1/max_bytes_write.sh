#!/bin/bash

#
bytes_a=0 # $(cat trace_a.data | cut -d" " -f5)
while read line; do tmp=$(echo line | cut -d" " -f5) ; bytes_a=$((bytes_a + tmp)); done < trace_a.data
echo "here"

count_a=0
count_b=0
count_c=0

for b in "${bytes_a[@]}" ; do
    count_a=$((count_a + b))
done

for b in "${bytes_b[@]}" ; do
    count_b=$((count_b + b))
done

for b in "${bytes_c[@]}" ; do
    count_c=$((count_c + b))
done

# Variable
list_of_files=("trace_a.data" "trace_b.data" "trace_b.data")
array=(${count_a} ${count_b} ${count_c})
max=${array[0]}
index=0

# Compute the max
for a in "${array[@]}" ; do
    if ((a > max)) ; then
        max=${a}
        index=$((index + 1))
    fi
done

# Print result
echo ${list_of_files[index]} " " ${max} "bytes write"
