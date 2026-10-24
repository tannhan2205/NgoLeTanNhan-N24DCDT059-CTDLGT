 #include <iostream>
#include <vector>

using namespace std;

int n;
int node_count = 0;
int solution_count = 0;
vector<int> X;
vector<int> first_solution;
vector<bool> col, diag1, diag2;

void backtrack(int i) {
    node_count++; // Mỗi lần gọi hàm đệ quy tính một nút
    
    for (int j = 1; j <= n; j++) {
        if (!col[j] && !diag1[i - j + n] && !diag2[i + j]) {
            X[i] = j;
            col[j] = diag1[i - j + n] = diag2[i + j] = true;

            if (i == n) {
                solution_count++;
                if (first_solution.empty()) {
                    first_solution = vector<int>(X.begin() + 1, X.end());
                }
            } else {
                backtrack(i + 1);
            }

            col[j] = diag1[i - j + n] = diag2[i + j] = false;
        }
    }
}

int main() {
    cout << "Nhap n: ";
    cin >> n;

    X.resize(n + 1);
    col.assign(n + 1, false);
    diag1.assign(2 * n + 1, false);
    diag2.assign(2 * n + 1, false);

    backtrack(1);

    cout << "So nut da duyet: " << node_count << endl;
    cout << "So loi giai: " << solution_count << endl;

    if (!first_solution.empty()) {
        cout << "\nBan co loi giai dau tien:\n";
        for (int r = 0; r < n; r++) {
            for (int c = 1; c <= n; c++) {
                if (c == first_solution[r]) cout << "Q ";
                else cout << ". ";
            }
            cout << "\n";
        }
    }
    return 0;
}
