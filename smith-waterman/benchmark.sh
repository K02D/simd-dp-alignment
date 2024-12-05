#!/bin/bash

make

# Number of trials
NUM_TRIALS=2

# Arrays to store the CPU times and memory deltas
times_1=()
memory_deltas_1=()
times_2=()
memory_deltas_2=()

for test in ssw_test_2 ssw_test_1; do
    echo "Running benchmark for $test"
    for i in $(seq 1 $NUM_TRIALS); do
        # Run the command and capture its output
        output=$(./$test Homo_sapiens.GRCh38.dna_rm.chromosome.15.fa query.fa s 2>&1)

        # Extract the CPU time using grep and awk
        time=$(echo "$output" | grep "CPU time:" | awk '{print $3}')

        # Extract the memory delta using grep and awk
        memory_delta=$(echo "$output" | grep "Memory Usage Delta" | awk '{print $7}')
        # echo "Memory usage delta: $memory_delta MB"

        if [ "$test" == "ssw_test_1" ]; then
            times_1+=($time)
            memory_deltas_1+=($memory_delta)
        else
            times_2+=($time)
            memory_deltas_2+=($memory_delta)
        fi

        # Add a blank line between runs
        echo ""
    done
done

# Function to calculate sum and average
calculate_sum_and_avg() {
    local arr=("$@")
    local sum=0
    for val in "${arr[@]}"; do
        sum=$(echo "$sum + $val" | bc)
    done
    local avg=$(echo "scale=6; $sum / $NUM_TRIALS" | bc)
    echo "$sum $avg"
}

# Calculate and print results for ssw_test_1
echo "Results for ssw_test_1 (base):"
read sum_time avg_time <<< $(calculate_sum_and_avg "${times_1[@]}")
read sum_memory avg_memory <<< $(calculate_sum_and_avg "${memory_deltas_1[@]}")
echo "Total CPU time: $sum_time seconds"
echo "Average CPU time: $avg_time seconds"
echo ""
echo "Total memory delta: $sum_memory MB"
echo "Average memory delta: $avg_memory MB"
echo ""

# Calculate and print results for ssw_test_2
echo "Results for ssw_test_2 (optimized):"
read sum_time avg_time <<< $(calculate_sum_and_avg "${times_2[@]}")
read sum_memory avg_memory <<< $(calculate_sum_and_avg "${memory_deltas_2[@]}")
echo "Total CPU time: $sum_time seconds"
echo "Average CPU time: $avg_time seconds"
echo ""
echo "Total memory delta: $sum_memory MB"
echo "Average memory delta: $avg_memory MB"