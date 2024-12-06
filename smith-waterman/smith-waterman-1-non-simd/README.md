# Compiling for dna

```
g++ smith-waterman-dna.cpp -std=c++17 -pedantic -Wall -Wextra -o smith_waterman_dna
```

# Running for dna

```
./smith_waterman_dna ../smith-waterman-test-data/dna-input/1k.fa ../smith-waterman-test-data/dna-input/query.fa
./smith_waterman_dna ../smith-waterman-test-data/dna-input/10k.fa ../smith-waterman-test-data/dna-input/query.fa
./smith_waterman_dna ../smith-waterman-test-data/dna-input/100k.fa ../smith-waterman-test-data/dna-input/query.fa
./smith_waterman_dna ../smith-waterman-test-data/dna-input/1M.fa ../smith-waterman-test-data/dna-input/query.fa
./smith_waterman_dna ../smith-waterman-test-data/dna-input/10M.fa ../smith-waterman-test-data/dna-input/query.fa
./smith_waterman_dna ../smith-waterman-test-data/dna-input/Homo_sapiens.GRCh38.dna_rm.chromosome.22.fa ../smith-waterman-test-data/dna-input/query.fa
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
