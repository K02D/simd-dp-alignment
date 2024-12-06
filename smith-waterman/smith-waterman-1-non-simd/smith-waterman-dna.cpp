#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

#include <chrono>

using namespace std;
using namespace chrono;

string readFastaFile(const string &filename)
{
    ifstream file(filename);
    string line, sequence;

    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return "";
    }

    // Skip the first header line (it starts with '>')
    bool headerSkipped = false;
    while (getline(file, line))
    {
        if (line.empty())
        {
            continue; // Skip empty lines
        }

        if (line[0] == '>')
        {
            headerSkipped = true;
        }
        else
        {
            sequence += line;
        }
    }

    file.close();

    if (!headerSkipped)
    {
        cerr << "No header found in the FASTA file!" << endl;
        return "";
    }

    return sequence;
}

int scoreCell(char base1, char base2, int match_score, int mismatch_penalty)
{
    if (base1 == 'N' || base2 == 'N')
    {
        return match_score; // Treat N as a match to any base
    }
    else if (base1 == base2)
    {
        return match_score; // Exact match
    }
    else
    {
        return mismatch_penalty; // Mismatch
    }
}

void smithWaterman(const string &seq1, const string &seq2,
                   int match_score, int mismatch_penalty, int gap_penalty)
{
    int m = seq1.size();
    int n = seq2.size();

    cout << "m = " << m << endl;
    cout << "n = " << n << endl;

    vector<vector<int>> score(m + 1, vector<int>(n + 1, 0));

    int max_score = 0;
    pair<int, int> max_pos = {0, 0};

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            int match = score[i - 1][j - 1] + scoreCell(seq1[i - 1], seq2[j - 1], match_score, mismatch_penalty);
            int del = score[i - 1][j] + gap_penalty;
            int ins = score[i][j - 1] + gap_penalty;
            score[i][j] = max({0, match, del, ins});

            if (score[i][j] > max_score)
            {
                max_score = score[i][j];
                max_pos = {i, j};
            }
        }
    }

    int i = max_pos.first;
    int j = max_pos.second;

    cout << "Optimal Alignment Score : " << max_score << endl;
    cout << "Target End: " << i << endl;
    cout << "Query End: " << j << endl;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <seq1_file> <seq2_file>" << std::endl;
        return 1;
    }

    string seq1_file = argv[1];
    string seq2_file = argv[2];

    string seq1 = readFastaFile(seq1_file);
    string seq2 = readFastaFile(seq2_file);

    cout << seq1.size() << " " << seq2.size() << endl;

    int match_score = 2;
    int mismatch_penalty = -4;
    int gap_penalty = -6;

    auto start = high_resolution_clock::now();

    smithWaterman(seq1, seq2, match_score, mismatch_penalty, gap_penalty);

    auto end = high_resolution_clock::now();

    // Calculate duration
    auto duration = duration_cast<microseconds>(end - start);

    cout << "Time taken: " << duration.count() << " microseconds." << endl;

    return 0;
}
