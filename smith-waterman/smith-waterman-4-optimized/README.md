# Compiling

make

The library uses ssw.c, while our optimizations are in ssw_opmitized.c

# Run benchmarking to compare optimized version to github version

```
bash benchmark.sh
```

# Running base github version for dna

```
./ssw_test_1 ../smith-waterman-test-data/dna-input/1k.fa ../smith-waterman-test-data/dna-input/query.fa
./ssw_test_1 ../smith-waterman-test-data/dna-input/10k.fa ../smith-waterman-test-data/dna-input/query.fa
./ssw_test_1 ../smith-waterman-test-data/dna-input/100k.fa ../smith-waterman-test-data/dna-input/query.fa
./ssw_test_1 ../smith-waterman-test-data/dna-input/1M.fa ../smith-waterman-test-data/dna-input/query.fa
./ssw_test_1 ../smith-waterman-test-data/dna-input/10M.fa ../smith-waterman-test-data/dna-input/query.fa
./ssw_test_1 ../smith-waterman-test-data/dna-input/Homo_sapiens.GRCh38.dna_rm.chromosome.22.fa ../smith-waterman-test-data/dna-input/query.fa
```

# Running base github version for protein

```
./ssw_test_1 ../smith-waterman-test-data/protein-input/protein-ref.fa ../smith-waterman-test-data/protein-input/protein-reads100.fa
./ssw_test_1 ../smith-waterman-test-data/protein-input/protein-ref.fa ../smith-waterman-test-data/protein-input/protein-reads1000.fa
./ssw_test_1 ../smith-waterman-test-data/protein-input/protein-ref.fa ../smith-waterman-test-data/protein-input/protein-reads10000.fa
```

# Running our optimized version for dna

```
./ssw_test_2 ../smith-waterman-test-data/dna-input/1k.fa ../smith-waterman-test-data/dna-input/query.fa
./ssw_test_2 ../smith-waterman-test-data/dna-input/10k.fa ../smith-waterman-test-data/dna-input/query.fa
./ssw_test_2 ../smith-waterman-test-data/dna-input/100k.fa ../smith-waterman-test-data/dna-input/query.fa
./ssw_test_2 ../smith-waterman-test-data/dna-input/1M.fa ../smith-waterman-test-data/dna-input/query.fa
./ssw_test_2 ../smith-waterman-test-data/dna-input/10M.fa ../smith-waterman-test-data/dna-input/query.fa
./ssw_test_2 ../smith-waterman-test-data/dna-input/Homo_sapiens.GRCh38.dna_rm.chromosome.22.fa ../smith-waterman-test-data/dna-input/query.fa
```

# Running our optimized version for protein

```
./ssw_test_2 ../smith-waterman-test-data/protein-input/protein-ref.fa ../smith-waterman-test-data/protein-input/protein-reads100.fa
./ssw_test_2 ../smith-waterman-test-data/protein-input/protein-ref.fa ../smith-waterman-test-data/protein-input/protein-reads1000.fa
./ssw_test_2 ../smith-waterman-test-data/protein-input/protein-ref.fa ../smith-waterman-test-data/protein-input/protein-reads10000.fa
```
