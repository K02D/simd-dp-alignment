# simd-dp-alignment

Computational Genomics Final Project by Ishan Hemmige, Darren Shih, William Sun, and Kiron Deb.

## Directory structure:

```
smith-waterman/
├── smith-waterman-1-naive/ # Our Naive implementation of Smith-Waterman
├── smith-waterman-2-simd/ # Our SIMD-optimized implementation
├── smith-waterman-3-github/ # SIMD-optimized Smith-Waterman from github.com/mengyao/complete-striped-smith-waterman-library
├── smith-waterman-4-optimized/ # Further optimized Smith-Waterman, building on top of #3
└── smith-waterman-test-data/ # Test data for benchmarking Smith-Waterman implementations
├── dna-input/ # DNA sequence data
└── protein-input/ # Protein sequence data
wavefront-alignment/ # Wavefront algorithm implementations
```
