#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <fstream>
#include <string>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <numeric>

std::string readFastaFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line, sequence;
    
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return "";
    }

    // skip header line ( starts with '>')
    bool headerSkipped = false;
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        if (line[0] == '>') {
            // Skip header line
            headerSkipped = true;
        } else {
            // Append sequence to string
            sequence += line;
        }
    }

    file.close();
    
    if (!headerSkipped) {
        std::cerr << "No header found" << std::endl;
        return "";
    }

    return sequence;
}

std::string mutate_sequence(const std::string& sequence, double mutation_rate) {
    if (mutation_rate < 0.0 || mutation_rate > 1.0) {
        throw std::invalid_argument("Mutation rate must be between 0 and 1.");
    }

    std::string mutated = sequence;
    int num_mutations = static_cast<int>(sequence.size() * mutation_rate);
    
    // select positions to mutate randomly
    std::vector<int> positions(sequence.size());
    std::iota(positions.begin(), positions.end(), 0);
    std::random_shuffle(positions.begin(), positions.end());

    const char bases[] = {'A', 'C', 'G', 'T'}; // mutate to ACGT
    for (int i = 0; i < num_mutations; ++i) {
        int pos = positions[i];
        char original = mutated[pos];
        char new_char;

        do {
            new_char = bases[std::rand() % 4]; // randomly pick from ACGT
        } while (new_char == original); // ensure base got changed

        mutated[pos] = new_char;
    }

    return mutated;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <orig_seq_file> <mutation_percent> <output_seq_file>" << std::endl;
        return 1;
    }

    std::string orig_seq_file = argv[1];
    std::string output_seq_file = argv[3];

    double mutation_rate = std::stod(argv[2]) / 100;
    std::string seq1 = readFastaFile(orig_seq_file);
    std::string new_sequence = mutate_sequence(seq1, mutation_rate);
    std::ofstream outfile(output_seq_file);

    if (outfile.is_open()) {
      outfile << ">" << std::endl; // so readFastaFile works correctly when aligning this sequence file
      outfile << new_sequence;
      outfile.close();
    } else {
      std::cerr << "Error opening the file for writing.\n";
    }

    return 0;
}




  
