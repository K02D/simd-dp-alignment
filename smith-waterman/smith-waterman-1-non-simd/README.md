# Compiling for dna

```
g++ smith-waterman-dna.cpp -std=c++17 -pedantic -Wall -Wextra -o smith_waterman_dna
```

# Running for dna

```
./smith_waterman_dna 1k.fa query.fa
./smith_waterman_dna 10k.fa query.fa
./smith_waterman_dna 100k.fa query.fa
./smith_waterman_dna 1M.fa query.fa
./smith_waterman_dna 10M.fa query.fa
./smith_waterman_dna Homo_sapiens.GRCh38.dna_rm.chromosome.22.fa query.fa
```

# Compiling for protein

```
g++ smith-waterman-protein.cpp -std=c++17 -pedantic -Wall -Wextra -o smith_waterman_protein
```

# Running for protein

```
./smith_waterman_protein ../smith-waterman-test-data/protein-input/protein-ref.fa ../smith-waterman-test-data/protein-input/protein-reads100.fa
./smith_waterman_protein ../smith-waterman-test-data/protein-input/protein-ref.fa ../smith-waterman-test-data/protein-input/protein-reads1000.fa
./smith_waterman_protein ../smith-waterman-test-data/protein-input/protein-ref.fa ../smith-waterman-test-data/protein-input/protein-reads10000.fa
```
