#!/bin/bash

# Number of trials
NUM_TRIALS=5

# Array to store the CPU times
times=()

for i in $(seq 1 $NUM_TRIALS); do
    echo "Run $i:"
    # Run the command and capture its output
    output=$(./ssw_test Homo_sapiens.GRCh38.dna_rm.chromosome.22.fa query.fa s 2>&1)

    # Extract the CPU time using grep and awk
    # This looks for "CPU time: " and captures the number before " seconds"
    time=$(echo "$output" | grep "CPU time:" | awk '{print $3}')
    
    echo "CPU time: $time seconds"
    times+=($time)
    
    # Add a blank line between runs
    echo ""
done

# Calculate the sum
sum=0
for t in "${times[@]}"; do
    sum=$(echo "$sum + $t" | bc)
done

# Calculate the average
# Using bc for floating point arithmetic
avg=$(echo "scale=6; $sum / $NUM_TRIALS" | bc)

echo "Individual runs: ${times[*]}"
echo "Total time: $sum seconds"
echo "Average time: $avg seconds"