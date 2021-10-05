#!/bin/bash

# Count the number of write of each file
count_write_a=$(cat trace_a.data | cut -d" " -f3 | grep -i "1" | wc -l)
count_write_b=$(cat trace_b.data | cut -d" " -f3 | grep -i "1" | wc -l)
count_write_c=$(cat trace_c.data | cut -d" " -f3 | grep -i "1" | wc -l)

# Variable
list_of_files=("trace_a.data" "trace_b.data" "trace_b.data")
array=(${count_write_a} ${count_write_b} ${count_write_c})
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
echo ${list_of_files[index]} " " ${max} "write"
