#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

void readFASTA(const string& filename, vector<string>& sequences) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Cannot open file " << filename << endl;
    }

    string line, current_sequence;
    while (getline(infile, line)) {
        // Ignore lines starting with '>'
        if (line.empty()) continue;
        if (line[0] == '>') {
            // If a sequence has been accumulated, store it
            if (!current_sequence.empty()) {
                sequences.push_back(current_sequence);
                current_sequence.clear();
            }
        } else {
            // Append line to the current sequence
            current_sequence += line;
        }
    }

    // Add the last sequence if any
    if (!current_sequence.empty()) {
        sequences.push_back(current_sequence);
    }

    infile.close();
}

int scoreCell(char aa1, char aa2, int match_score, int mismatch_penalty) {
    if (islower(aa1) || islower(aa2) || aa1 == '.' || aa2 == '.') {
      return 0;  // Ignore these comparisons
    } else if (aa1 == aa2) {
      return match_score;  // Exact match
    } else {
      return mismatch_penalty;  // Mismatch
    }
}

void smithWaterman(const string& seq1, const string& seq2, 
                   int match_score, int mismatch_penalty, int gap_penalty) {
    int m = seq1.size();
    int n = seq2.size();

    vector<vector<int>> score(m + 1, vector<int>(n + 1, 0));

    int max_score = 0;
    pair<int, int> max_pos = {0, 0};

    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        int match = score[i - 1][j - 1] + scoreCell(seq1[i - 1], seq2[j - 1], match_score, mismatch_penalty);
        int del = score[i - 1][j] + gap_penalty;
        int ins = score[i][j - 1] + gap_penalty;
        score[i][j] = max({0, match, del, ins});

        if (score[i][j] > max_score) {
            max_score = score[i][j];
            max_pos = {i, j};
        }
      }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <reads_file> <ref_file>" << std::endl;
        return 1;
    }

    string reads_file = argv[1];
    string ref_file = argv[2];

    vector<string> reads;
    vector<string> refs;

    readFASTA(reads_file, reads);
    readFASTA(ref_file, refs);

    cout << reads.size() << " " << refs.size() << endl;

    int match_score = 2;
    int mismatch_penalty = -4;
    int gap_penalty = -6;

    auto start = high_resolution_clock::now();

    for (auto& read : reads) {
      for (auto& ref : refs) {
        smithWaterman(read, ref, match_score, mismatch_penalty, gap_penalty);
      }
    }

    auto end = high_resolution_clock::now();

    // Calculate duration
    auto duration = duration_cast<microseconds>(end - start);

    cout << "Time taken: " << duration.count() << " microseconds." << endl;

    int reads_total_length = 0;
    for (auto& r : reads) {
      reads_total_length += r.size();
    }
    cout << reads_total_length / reads.size() << endl;

    int refs_total_length = 0;
    for (auto& r : refs) {
      refs_total_length += r.size();
    }
    cout << refs_total_length / refs.size() << endl;

    return 0;
}