echo "Starting the build process..."
make


echo "Running ssw_test with Homo_sapiens.GRCh38.dna_rm.chromosome.22.fa and query.fa..."
./ssw_test Homo_sapiens.GRCh38.dna_rm.chromosome.22.fa query.fa
