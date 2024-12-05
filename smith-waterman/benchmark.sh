#!/bin/bash

# Number of trials
NUM_TRIALS=5

# Arrays to store the CPU times and memory deltas
times=()
memory_deltas=()

for i in $(seq 1 $NUM_TRIALS); do
    echo "Run $i:"
    # Run the command and capture its output
    output=$(./ssw_test Homo_sapiens.GRCh38.dna_rm.chromosome.22.fa query.fa s 2>&1)

    # Extract the CPU time using grep and awk
    time=$(echo "$output" | grep "CPU time:" | awk '{print $3}')
    echo "CPU time: $time seconds"
    times+=($time)

    # Extract the memory delta using grep and awk
    memory_delta=$(echo "$output" | grep "Memory Usage Delta" | awk '{print $7}')
    echo "Memory usage delta: $memory_delta MB"
    memory_deltas+=($memory_delta)

    # Add a blank line between runs
    echo ""
done

# Calculate the sum and average of CPU times
sum_time=0
for t in "${times[@]}"; do
    sum_time=$(echo "$sum_time + $t" | bc)
done
avg_time=$(echo "scale=6; $sum_time / $NUM_TRIALS" | bc)

# Calculate the sum and average of memory deltas
sum_memory=0
for m in "${memory_deltas[@]}"; do
    sum_memory=$(echo "$sum_memory + $m" | bc)
done
avg_memory=$(echo "scale=6; $sum_memory / $NUM_TRIALS" | bc)

# Print results
echo "Total CPU time: $sum_time seconds"
echo "Average CPU time: $avg_time seconds"
# add a new line here
echo ""
echo "Total memory delta: $sum_memory MB"
echo "Average memory delta: $avg_memory MB"