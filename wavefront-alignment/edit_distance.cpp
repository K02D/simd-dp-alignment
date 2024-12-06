#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include <limits>
#include <fstream>
#include <string>

#include <chrono>

using namespace std;
using namespace chrono;

string readFastaFile(const string& filename) {
    ifstream file(filename);
    string line, sequence;
    
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return "";
    }

    // Skip the first header line (it starts with '>')
    bool headerSkipped = false;
    while (getline(file, line)) {
        if (line.empty()) {
            continue; // Skip empty lines
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
        cerr << "No header found in the FASTA file!" << endl;
        return "";
    }

    return sequence;
}

class EditDistance {
public:
    // Compute edit distance between two strings
    std::pair<int, std::string> align(const std::string& seq1, const std::string& seq2) {
        int m = seq1.length();
        int n = seq2.length();

        // Create a matrix to store edit distances
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

        // Initialize first row and column
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = i;
        }
        for (int j = 0; j <= n; ++j) {
            dp[0][j] = j;
        }

        // Fill the dynamic programming table
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                // If characters are the same, no operation needed
                if (seq1[i-1] == seq2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                }
                else {
                    // Minimum of insert, delete, or replace operations
                    dp[i][j] = 1 + std::min({
                        dp[i-1][j],     // deletion
                        dp[i][j-1],     // insertion
                        dp[i-1][j-1]    // replacement
                    });
                }
            }
        }

        // Reconstruct alignment path
        std::string alignment = reconstructAlignment(seq1, seq2);

        // Return distance and alignment path
        return {dp[m][n], alignment};
    }

private:
    // Reconstruct alignment path
    std::string reconstructAlignment(const std::string& seq1, const std::string& seq2) {
        int m = seq1.length();
        int n = seq2.length();

        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        
        // Initialize first row and column
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = i;
        }
        for (int j = 0; j <= n; ++j) {
            dp[0][j] = j;
        }

        // Fill the dynamic programming table
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (seq1[i-1] == seq2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                }
                else {
                    dp[i][j] = 1 + std::min({
                        dp[i-1][j],     // deletion
                        dp[i][j-1],     // insertion
                        dp[i-1][j-1]    // replacement
                    });
                }
            }
        }

        // Traceback to generate alignment representation
        std::string alignment;
        int i = m, j = n;
        while (i > 0 && j > 0) {
            if (seq1[i-1] == seq2[j-1]) {
                alignment = "|" + alignment;
                i--; j--;
            }
            else {
                // Check which operation was used
                int current = dp[i][j];
                int del = dp[i-1][j] + 1;
                int ins = dp[i][j-1] + 1;
                int rep = dp[i-1][j-1] + 1;

                if (current == rep) {
                    alignment = "*" + alignment;
                    i--; j--;
                }
                else if (current == del) {
                    alignment = "+" + alignment;
                    i--;
                }
                else {
                    alignment = "-" + alignment;
                    j--;
                }
            }
        }

        // Handle remaining characters if any
        while (i > 0) {
            alignment = "+" + alignment;
            i--;
        }
        while (j > 0) {
            alignment = "-" + alignment;
            j--;
        }

        return alignment;
    }
};

int main(int argc, char* argv[]) {
    EditDistance ed;

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <seq1_file> <seq2_file>" << std::endl;
        return 1;
    }

    string seq1_file = argv[1];
    string seq2_file = argv[2];

    string seq1 = readFastaFile(seq1_file);
    string seq2 = readFastaFile(seq2_file);

    // Example 1
    // std::string seq1 = "GCTATGCCACGC";
    // std::string seq2 = "GCGTATGCACGC";

    auto start = high_resolution_clock::now();


    auto [score, alignment] = ed.align(seq1, seq2);

    auto end = high_resolution_clock::now();

    // Calculate duration
    auto duration = duration_cast<microseconds>(end - start);

    cout << "Time taken: " << duration.count() << " microseconds." << endl;


    // std::cout << "Sequence 1: " << seq1 << std::endl;
    // std::cout << "Sequence 2: " << seq2 << std::endl;
    // std::cout << "Alignment Score: " << score << std::endl;
    // std::cout << "Alignment Path: " << alignment << std::endl;

    // Example 2
    // seq1 = "sunday";
    // seq2 = "saturday";

    // std::tie(score, alignment) = ed.align(seq1, seq2);

    // std::cout << "\nSequence 1: " << seq1 << std::endl;
    // std::cout << "Sequence 2: " << seq2 << std::endl;
    // std::cout << "Alignment Score: " << score << std::endl;
    // std::cout << "Alignment Path: " << alignment << std::endl;

    return 0;
}