# Compiling for dna

```
g++ -std=c++17 -march=armv8-a+simd smith-waterman-dna-simd.cpp -o smith_waterman_dna_simd
```

# Running for dna


```
./smith_waterman_dna_simd ../smith-waterman-test-data/dna-input/1k.fa ../smith-waterman-test-data/dna-input/query.fa
./smith_waterman_dna_simd ../smith-waterman-test-data/dna-input/10k.fa ../smith-waterman-test-data/dna-input/query.fa
./smith_waterman_dna_simd ../smith-waterman-test-data/dna-input/100k.fa ../smith-waterman-test-data/dna-input/query.fa
./smith_waterman_dna_simd ../smith-waterman-test-data/dna-input/1M.fa ../smith-waterman-test-data/dna-input/query.fa
./smith_waterman_dna_simd ../smith-waterman-test-data/dna-input/10M.fa ../smith-waterman-test-data/dna-input/query.fa
./smith_waterman_dna_simd ../smith-waterman-test-data/dna-input/Homo_sapiens.GRCh38.dna_rm.chromosome.22.fa ../smith-waterman-test-data/dna-input/query.fa
```

# Compiling for protein

```
g++ -std=c++17 -march=armv8-a+simd smith-waterman-protein-simd.cpp -o smith_waterman_protein_simd
```

# Running for protein

```
./smith_waterman_protein_simd ../smith-waterman-test-data/protein-input/protein-ref.fa ../smith-waterman-test-data/protein-input/protein-reads100.fa
./smith_waterman_protein_simd ../smith-waterman-test-data/protein-input/protein-ref.fa ../smith-waterman-test-data/protein-input/protein-reads1000.fa
./smith_waterman_protein_simd ../smith-waterman-test-data/protein-input/protein-ref.fa ../smith-waterman-test-data/protein-input/protein-reads10000.fa
```
