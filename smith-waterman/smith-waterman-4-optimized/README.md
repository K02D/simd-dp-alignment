# Compiling

make

# Running github version for dna

```
./ssw_test_1 1k.fa query.fa
./ssw_test_1 10k.fa query.fa
./ssw_test_1 100k.fa query.fa
./ssw_test_1 1M.fa query.fa
./ssw_test_1 10M.fa query.fa
./ssw_test_1 Homo_sapiens.GRCh38.dna_rm.chromosome.22.fa query.fa
```

# Running github version for protein

```
./ssw_test_1 reference.fa balifam100.fa
./ssw_test_1 reference.fa balifam1000.fa
./ssw_test_1 reference.fa balifam10000.fa
```

# Running our optimized version for dna

```
./ssw_test_2 1k.fa query.fa
./ssw_test_2 10k.fa query.fa
./ssw_test_2 100k.fa query.fa
./ssw_test_2 1M.fa query.fa
./ssw_test_2 10M.fa query.fa
./ssw_test_2 Homo_sapiens.GRCh38.dna_rm.chromosome.22.fa query.fa
```

# Running our optimized version for protein

```
./ssw_test_2 reference.fa balifam100.fa
./ssw_test_2 reference.fa balifam1000.fa
./ssw_test_2 reference.fa balifam10000.fa
```

# Run benchmarking to compare optimized version to github version

```
bash benchmark.sh
```
