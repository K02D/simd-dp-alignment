Code taken from https://github.com/mengyao/complete-striped-smith-waterman-library

# Compiling

make

# Running for dna

```
./ssw_test ../smith-waterman-test-data/dna-input/1k.fa ../smith-waterman-test-data/dna-input/query.fa
./ssw_test ../smith-waterman-test-data/dna-input/10k.fa ../smith-waterman-test-data/dna-input/query.fa
./ssw_test ../smith-waterman-test-data/dna-input/100k.fa ../smith-waterman-test-data/dna-input/query.fa
./ssw_test ../smith-waterman-test-data/dna-input/1M.fa ../smith-waterman-test-data/dna-input/query.fa
./ssw_test ../smith-waterman-test-data/dna-input/10M.fa ../smith-waterman-test-data/dna-input/query.fa
./ssw_test ../smith-waterman-test-data/dna-input/Homo_sapiens.GRCh38.dna_rm.chromosome.22.fa ../smith-waterman-test-data/dna-input/query.fa
```

# Running for protein

```
./ssw_test ../smith-waterman-test-data/protein-input/protein-ref.fa ../smith-waterman-test-data/protein-input/protein-reads100.fa
./ssw_test ../smith-waterman-test-data/protein-input/protein-ref.fa ../smith-waterman-test-data/protein-input/protein-reads1000.fa
./ssw_test ../smith-waterman-test-data/protein-input/protein-ref.fa ../smith-waterman-test-data/protein-input/protein-reads10000.fa
```
