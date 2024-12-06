# Compiling for dna

```
g++ -std=c++17 -march=armv8-a+simd smith-waterman-dna-simd.cpp -o smith_waterman_dna_simd
```

# Running for dna

```
./smith_waterman_dna_simd 1k.fa query.fa
./smith_waterman_dna_simd 10k.fa query.fa
./smith_waterman_dna_simd 100k.fa query.fa
./smith_waterman_dna_simd 1M.fa query.fa
./smith_waterman_dna_simd 10M.fa query.fa
./smith_waterman_dna_simd Homo_sapiens.GRCh38.dna_rm.chromosome.22.fa query.fa
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
