#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <arm_neon.h>

using namespace std;
using namespace chrono;

static inline int scoreCell(char base1, char base2, int match_score, int mismatch_penalty)
{
    if (base1 == 'N' || base2 == 'N')
    {
        return match_score;
    }
    else if (base1 == base2)
    {
        return match_score;
    }
    else
    {
        return mismatch_penalty;
    }
}

string readFastaFile(const string &filename)
{
    ifstream file(filename);
    string line, sequence;

    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return "";
    }

    bool headerSkipped = false;
    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
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

void smithWaterman_simd(const string &seq1, const string &seq2,
                        int match_score, int mismatch_penalty, int gap_penalty)
{
    int m = (int)seq1.size();
    int n = (int)seq2.size();

    cout << "m = " << m << ", n = " << n << endl;

    vector<int> score((m + 1) * (n + 1), 0);

    int max_score = 0;
    int max_i = 0, max_j = 0;

    int32x4_t v_gap = vdupq_n_s32(gap_penalty);
    int chunk = 4;
    int aligned_n = (n / chunk) * chunk;

    for (int i = 1; i <= m; i++)
    {
        int j = 1;
        for (; j + chunk - 1 <= n; j += chunk)
        {
            int idx_i_j = i * (n + 1) + j;
            int idx_im1_j = (i - 1) * (n + 1) + j;

            int32x4_t v_up = vld1q_s32(&score[idx_im1_j]);
            int left_base_idx = idx_i_j - 1;
            int32x4_t v_left = vld1q_s32(&score[left_base_idx]);

            int diag_base_idx = (i - 1) * (n + 1) + (j - 1);
            int32x4_t v_diag = vld1q_s32(&score[diag_base_idx]);

            int temp_match[4];
            for (int k = 0; k < 4; k++)
            {
                char b1 = seq1[i - 1];
                char b2 = seq2[(j - 1) + k];
                temp_match[k] = scoreCell(b1, b2, match_score, mismatch_penalty);
            }
            int32x4_t v_match_score = vld1q_s32(temp_match);

            int32x4_t v_match = vaddq_s32(v_diag, v_match_score);
            int32x4_t v_del = vaddq_s32(v_up, v_gap);
            int32x4_t v_ins = vaddq_s32(v_left, v_gap);

            int32x4_t v_zero = vdupq_n_s32(0);
            int32x4_t v_max1 = vmaxq_s32(v_match, v_del);
            int32x4_t v_max2 = vmaxq_s32(v_ins, v_zero);
            int32x4_t v_final = vmaxq_s32(v_max1, v_max2);

            vst1q_s32(&score[idx_i_j], v_final);

            int result[4];
            vst1q_s32(result, v_final);
            for (int k = 0; k < 4; k++)
            {
                if (result[k] > max_score)
                {
                    max_score = result[k];
                    max_i = i;
                    max_j = j + k;
                }
            }
        }

        for (; j <= n; j++)
        {
            int idx = i * (n + 1) + j;
            int diag_idx = (i - 1) * (n + 1) + (j - 1);
            int up_idx = (i - 1) * (n + 1) + j;
            int left_idx = i * (n + 1) + (j - 1);

            int match_val = score[diag_idx] + scoreCell(seq1[i - 1], seq2[j - 1], match_score, mismatch_penalty);
            int del_val = score[up_idx] + gap_penalty;
            int ins_val = score[left_idx] + gap_penalty;

            int val = std::max({0, match_val, del_val, ins_val});
            score[idx] = val;

            if (val > max_score)
            {
                max_score = val;
                max_i = i;
                max_j = j;
            }
        }
    }

    // cout << "Optimal Alignment Score: " << max_score << endl;
    // cout << "Target End: " << max_i << endl;
    // cout << "Query End: " << max_j << endl;
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

    smithWaterman_simd(seq1, seq2, match_score, mismatch_penalty, gap_penalty);

    auto end = high_resolution_clock::now();

    // Calculate duration
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken: " << duration.count() << " microseconds." << endl;

    return 0;
}
