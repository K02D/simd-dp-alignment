#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <fstream>
#include <string>
#include <chrono>

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
            headerSkipped = true;
        } else {
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

class EditDistance {
public:
    std::pair<int, std::string> align(const std::string& seq1, const std::string& seq2) {
        int m = seq1.length();
        int n = seq2.length();

        // edit distance matrix
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

        // initialize first column and row
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = i;
        }
        for (int j = 0; j <= n; ++j) {
            dp[0][j] = j;
        }

        // fill DP matrix
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                // no operation if chatacters match
                if (seq1[i-1] == seq2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                }
                else {
                    // min of insert, delete, or substitution operations
                    dp[i][j] = 1 + std::min({
                        dp[i-1][j],     // deletion
                        dp[i][j-1],     // insertion
                        dp[i-1][j-1]    // replacement
                    });
                }
            }
        }
    
        std::string alignment = reconstructAlignment(seq1, seq2, dp, m, n);
        return {dp[m][n], alignment};
    }

private:
    // helper function to generate alignment representation
    std::string reconstructAlignment(const std::string& seq1, const std::string& seq2, std::vector<std::vector<int>>& dp, int m, int n) {
        std::string alignment;
        int i = m, j = n;
        while (i > 0 && j > 0) {
            if (seq1[i-1] == seq2[j-1]) {
                alignment = "|" + alignment;
                i--; j--;
            }
            else {
                // determine which operation was selected
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

        // handle remaining characters if any
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

    std::string seq1_file = argv[1];
    std::string seq2_file = argv[2];
    std::string seq1 = readFastaFile(seq1_file);
    std::string seq2 = readFastaFile(seq2_file);

    auto start = std::chrono::high_resolution_clock::now();
    auto [score, alignment] = ed.align(seq1, seq2);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Time taken: " << duration.count() << " microseconds." << std::endl;
    // std::cout << "Alignment Score: " << score << std::endl;
    // std::cout << "Alignment Path: " << alignment << std::endl;

    return 0;
}