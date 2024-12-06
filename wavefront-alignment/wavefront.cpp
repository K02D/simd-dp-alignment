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

class WavefrontAlignment {
private:
    // scoring constants for edit distance (everything is 1)
    const int MATCH_SCORE = 0;
    const int MISMATCH_SCORE = 1;
    const int GAP_SCORE = 1;

    // traceback direction enum
    enum class Direction {
        NONE,
        MATCH,
        INSERT,
        DELETE
    };

public:
    // wavefront alignment function
    std::pair<int, std::string> align(const std::string& seq1, const std::string& seq2) {
        int m = seq1.length();
        int n = seq2.length();

        // dp matrix for scoring
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        // traceback matrix
        std::vector<std::vector<Direction>> trace(m + 1, std::vector<Direction>(n + 1, Direction::NONE));

        // initialize first column and row
        for (int i = 1; i <= m; ++i) {
            dp[i][0] = i * GAP_SCORE;
            trace[i][0] = Direction::DELETE;
        }
        for (int j = 1; j <= n; ++j) {
            dp[0][j] = j * GAP_SCORE;
            trace[0][j] = Direction::INSERT;
        }

        // fill DP matrix
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                // calculate match/mismatch score
                int matchScore = dp[i-1][j-1] + (seq1[i-1] == seq2[j-1] ? MATCH_SCORE : MISMATCH_SCORE);
                
                // calculate insertion and deletion scores
                int insertScore = dp[i][j-1] + GAP_SCORE;
                int deleteScore = dp[i-1][j] + GAP_SCORE;

                // select the minimum of the three
                if (matchScore <= insertScore && matchScore <= deleteScore) {
                    dp[i][j] = matchScore;
                    trace[i][j] = Direction::MATCH;
                } else if (insertScore <= deleteScore) {
                    dp[i][j] = insertScore;
                    trace[i][j] = Direction::INSERT;
                } else {
                    dp[i][j] = deleteScore;
                    trace[i][j] = Direction::DELETE;
                }
            }
        }

        // Reconstruct the alignment from trace
        std::string alignment = reconstructAlignment(seq1, seq2, trace);
        return {dp[m][n], alignment};
    }

private:
    // helper function reconstructs alignment path
    std::string reconstructAlignment(const std::string& seq1, const std::string& seq2, 
                                     const std::vector<std::vector<Direction>>& trace) {
        std::string alignment;
        int i = seq1.length(), j = seq2.length();

        while (i > 0 || j > 0) {
            switch (trace[i][j]) {
                case Direction::MATCH:
                    alignment = (seq1[i-1] == seq2[j-1] ? "|" : "*") + alignment;
                    i--; j--;
                    break;
                case Direction::INSERT:
                    alignment = "-" + alignment;
                    j--;
                    break;
                case Direction::DELETE:
                    alignment = "+" + alignment;
                    i--;
                    break;
                default:
                    break;
            }
        }
        return alignment;
    }
};

int main(int argc, char* argv[]) {
    WavefrontAlignment wa;
    
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <seq1_file> <seq2_file>" << std::endl;
        return 1;
    }

    std::string seq1_file = argv[1];
    std::string seq2_file = argv[2];
    std::string seq1 = readFastaFile(seq1_file);
    std::string seq2 = readFastaFile(seq2_file);

    auto start = std::chrono::high_resolution_clock::now();
    auto [score, alignment] = wa.align(seq1, seq2);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Time taken: " << duration.count() << " microseconds." << std::endl;
    std::cout << "Alignment Score: " << score << std::endl;
    // std::cout << "Alignment Path: " << alignment << std::endl;
    return 0;
}