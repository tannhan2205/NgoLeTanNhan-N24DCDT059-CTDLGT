#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class TSPBranchAndBound {
private:
    vector<vector<int>> matrix;
    int n;
    int c_min;
    int best_cost;
    vector<int> best_path;
    int node_count;

    void dfs(int u, int current_cost, int level, vector<int>& path, vector<bool>& visited, bool with_pruning) {
        node_count++;

        if (level == n) {
            int total_cost = current_cost + matrix[u][0];
            if (total_cost < best_cost) {
                best_cost = total_cost;
                best_path = path;
                best_path.push_back(0);
            }
            return;
        }

        for (int v = 0; v < n; ++v) {
            if (!visited[v]) {
                int next_cost = current_cost + matrix[u][v];
                // Ham can duoi: chi phi hien tai + (so canh con lai) * c_min
                int lb = next_cost + (n - level) * c_min;

                if (!with_pruning || lb < best_cost) {
                    visited[v] = true;
                    path.push_back(v);
                    dfs(v, next_cost, level + 1, path, visited, with_pruning);
                    path.pop_back();
                    visited[v] = false;
                }
            }
        }
    }

public:
    TSPBranchAndBound(const vector<vector<int>>& mat) : matrix(mat) {
        n = matrix.size();
        c_min = INT_MAX;
        // Tim gia tri c_min (canh nho nhat khong nam tren duong cheo chinh)
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && matrix[i][j] < c_min) {
                    c_min = matrix[i][j];
                }
            }
        }
    }

    int getCMin() const { return c_min; }

    void solve(bool with_pruning) {
        best_cost = INT_MAX;
        best_path.clear();
        node_count = 0;

        vector<bool> visited(n, false);
        vector<int> path;

        visited[0] = true;
        path.push_back(0);

        dfs(0, 0, 1, path, visited, with_pruning);

        cout << (with_pruning ? "[CO CAT NHANH]" : "[KHONG CAT NHANH]") << endl;
        cout << "Chi phi toi uu: " << best_cost << endl;
        cout << "Hanh trinh toi uu: ";
        for (size_t i = 0; i < best_path.size(); ++i) {
            cout << best_path[i] << (i + 1 < best_path.size() ? " -> " : "");
        }
        cout << "\nSo nut da duyet: " << node_count << "\n\n";
    }
};

int main() {
    // Ma tran chi phi 5x5 tu de bai
    vector<vector<int>> cost_matrix = {
        {0, 10, 9, 22, 23},
        {10, 0, 16, 19, 14},
        {9, 16, 0, 7, 28},
        {22, 19, 7, 0, 8},
        {23, 14, 28, 8, 0}
    };

    TSPBranchAndBound solver(cost_matrix);
    cout << "Gia tri c_min tim duoc: " << solver.getCMin() << "\n\n";

    solver.solve(true);  // Co cat nhanh
    solver.solve(false); // Khong cat nhanh

    return 0;
}