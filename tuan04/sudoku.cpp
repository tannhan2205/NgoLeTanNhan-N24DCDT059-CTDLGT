#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <string>

using namespace std;

const int board_initial[9][9] = {
    {0, 0, 0, 0, 0, 6, 0, 0, 0},
    {0, 8, 1, 0, 5, 0, 4, 0, 0},
    {0, 0, 9, 0, 0, 7, 0, 5, 8},
    {0, 0, 0, 0, 9, 0, 0, 0, 0},
    {0, 0, 6, 0, 0, 1, 0, 0, 7},
    {7, 4, 0, 0, 0, 0, 2, 0, 1},
    {0, 0, 0, 1, 3, 0, 0, 0, 4},
    {0, 0, 0, 0, 2, 9, 0, 0, 0},
    {9, 0, 0, 0, 0, 8, 0, 6, 0}
};

bool isValid(int board[9][9], int r, int c, int val) {
    for (int i = 0; i < 9; i++) {
        if (board[r][i] == val || board[i][c] == val) return false;
    }
    int br = 3 * (r / 3);
    int bc = 3 * (c / 3);
    for (int i = br; i < br + 3; i++) {
        for (int j = bc; j < bc + 3; j++) {
            if (board[i][j] == val) return false;
        }
    }
    return true;
}

vector<int> getCandidates(int board[9][9], int r, int c) {
    vector<bool> used(10, false);
    for (int i = 0; i < 9; i++) {
        if (board[r][i] != 0) used[board[r][i]] = true;
        if (board[i][c] != 0) used[board[i][c]] = true;
    }
    int br = 3 * (r / 3);
    int bc = 3 * (c / 3);
    for (int i = br; i < br + 3; i++) {
        for (int j = bc; j < bc + 3; j++) {
            if (board[i][j] != 0) used[board[i][j]] = true;
        }
    }
    vector<int> cands;
    for (int val = 1; val <= 9; val++) {
        if (!used[val]) cands.push_back(val);
    }
    return cands;
}

// --- 1. QUET TUAN TU ---
long long calls_seq = 0;

bool solveSequential(int board[9][9]) {
    calls_seq++;
    int empty_r = -1, empty_c = -1;
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (board[r][c] == 0) {
                empty_r = r;
                empty_c = c;
                break;
            }
        }
        if (empty_r != -1) break;
    }

    if (empty_r == -1) return true;

    for (int val = 1; val <= 9; val++) {
        if (isValid(board, empty_r, empty_c, val)) {
            board[empty_r][empty_c] = val;
            if (solveSequential(board)) return true;
            board[empty_r][empty_c] = 0;
        }
    }
    return false;
}

// --- 2. HEURISTIC MRV ---
long long calls_mrv = 0;

bool solveMRV(int board[9][9]) {
    calls_mrv++;
    int min_cands = 10;
    int best_r = -1, best_c = -1;
    vector<int> best_candidates;

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (board[r][c] == 0) {
                vector<int> cands = getCandidates(board, r, c);
                if ((int)cands.size() < min_cands) {
                    min_cands = cands.size();
                    best_r = r;
                    best_c = c;
                    best_candidates = cands;
                    if (min_cands == 0) return false;
                }
            }
        }
    }

    if (best_r == -1) return true;

    for (int val : best_candidates) {
        board[best_r][best_c] = val;
        if (solveMRV(board)) return true;
        board[best_r][best_c] = 0;
    }
    return false;
}

int main() {
    int board_seq[9][9];
    int board_mrv[9][9];

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            board_seq[r][c] = board_initial[r][c];
            board_mrv[r][c] = board_initial[r][c];
        }
    }

    calls_seq = 0;
    auto start = chrono::high_resolution_clock::now();
    solveSequential(board_seq);
    auto end = chrono::high_resolution_clock::now();
    double time_seq = chrono::duration<double, milli>(end - start).count();

    calls_mrv = 0;
    start = chrono::high_resolution_clock::now();
    solveMRV(board_mrv);
    end = chrono::high_resolution_clock::now();
    double time_mrv = chrono::duration<double, milli>(end - start).count();

    bool same = true;
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (board_seq[r][c] != board_mrv[r][c]) {
                same = false;
                break;
            }
        }
    }

    string same_str = same ? "Co" : "Khong";

    cout << "=================================================================\n";
    cout << left << setw(35) << "Dai luong" << " | "
         << setw(12) << "Quet tuan tu" << " | "
         << setw(10) << "MRV" << "\n";
    cout << "-----------------------------------------------------------------\n";
    cout << left << setw(35) << "So loi goi ham de quy" << " | "
         << setw(12) << calls_seq << " | "
         << setw(10) << calls_mrv << "\n";
    cout << left << setw(35) << "Thoi gian chay (ms)" << " | "
         << setw(12) << fixed << setprecision(3) << time_seq << " | "
         << setw(10) << fixed << setprecision(3) << time_mrv << "\n";
    cout << left << setw(35) << "Loi giai tim duoc co giong nhau?" << " | "
         << setw(12) << same_str << " | "
         << setw(10) << same_str << "\n";
    cout << "=================================================================\n";

    return 0;
}