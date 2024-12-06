Code taken from https://github.com/mengyao/complete-striped-smith-waterman-library

# Compiling

make

# Running for dna

```
./ssw_test 1k.fa query.fa
./ssw_test 10k.fa query.fa
./ssw_test 100k.fa query.fa
./ssw_test 1M.fa query.fa
./ssw_test 10M.fa query.fa
./ssw_test Homo_sapiens.GRCh38.dna_rm.chromosome.22.fa query.fa
```

# Running for protein

```
./ssw_test ../smith-waterman-test-data/protein-input/protein-ref.fa ../smith-waterman-test-data/protein-input/protein-reads100.fa
./ssw_test ../smith-waterman-test-data/protein-input/protein-ref.fa ../smith-waterman-test-data/protein-input/protein-reads1000.fa
./ssw_test ../smith-waterman-test-data/protein-input/protein-ref.fa ../smith-waterman-test-data/protein-input/protein-reads10000.fa
```
