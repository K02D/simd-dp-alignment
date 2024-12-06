# Generate executables for input data generation, WaveFront alignment, and Smith-Waterman edit distance

```
make
```
OR
```
make wavefront
make edit_distance
make data_generation
```


# Generate input sequence files
Command format:
```
 ./data_generation <orig_seq_file> <mutation_percent> <output_seq_file>
```
Example commands:
```
./data_generation dna-input/10k.fa 0 dna-input-mutated/10k-0.fa
./data_generation dna-input/10k.fa 25 dna-input-mutated/10k-25.fa
./data_generation dna-input/100k.fa 15 dna-input-mutated/100k-15.fa
```

# Running WaveFront Alignment
```
./wavefront <seq1_file> <seq2_file>
```
Examples
```
./wavefront dna-input/1k.fa dna-input-mutated/1k-0.fa
./wavefront dna-input/10k.fa dna-input-mutated/10k-25.fa 
./wavefront dna-input/10k.fa dna-input-mutated/10k-50.fa 
```

# Running Smith-Waterman based edit distance
```
./edit_distance <seq1_file> <seq2_file>
```
Examples
```
./edit_distance dna-input/1k.fa dna-input-mutated/1k-0.fa
./edit_distance dna-input/10k.fa dna-input-mutated/10k-25.fa 
./edit_distance dna-input/10k.fa dna-input-mutated/10k-50.fa 
```
