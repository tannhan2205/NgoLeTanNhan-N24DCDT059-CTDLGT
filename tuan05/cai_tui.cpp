#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

void knapsack01() {
    vector<string> items = {"A", "B", "C", "D", "E"};
    vector<int> w = {2, 3, 4, 5, 7};
    vector<int> v = {3, 7, 9, 12, 16};
    int W = 11;
    int n = items.size();

    // Khởi tạo bảng f kích thước (n+1) x (W+1) bằng 0
    vector<vector<int>> f(n + 1, vector<int>(W + 1, 0));

    // Điền bảng quy hoạch động
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= W; ++j) {
            if (w[i - 1] > j) {
                f[i][j] = f[i - 1][j];
            } else {
                f[i][j] = max(f[i - 1][j], f[i - 1][j - w[i - 1]] + v[i - 1]);
            }
        }
    }

    // 1. In toàn bộ bảng f (72 ô kể cả hàng 0 và cột 0)
    cout << "=== BANG f QUY HOACH DONG (6 HANG x 12 COT) ===\n";
    cout << left << setw(10) << "f[i][j]";
    for (int j = 0; j <= W; ++j) {
        cout << setw(4) << j;
    }
    cout << "\n----------------------------------------------------------\n";

    for (int i = 0; i <= n; ++i) {
        string label = (i == 0) ? "i=0" : "i=" + to_string(i) + " (" + items[i - 1] + ")";
        cout << left << setw(10) << label;
        for (int j = 0; j <= W; ++j) {
            cout << setw(4) << f[i][j];
        }
        cout << "\n";
    }

    // 2. Truy vết từ ô f[n][W] ngược lên f[0][.]
    vector<string> selected_items;
    int i = n, j = W;
    while (i > 0 && j > 0) {
        if (f[i][j] != f[i - 1][j]) {
            selected_items.push_back(items[i - 1]);
            j -= w[i - 1];
        }
        i--;
    }
    reverse(selected_items.begin(), selected_items.end());

    // 3. In kết quả cuối cùng
    cout << "\nGia tri lon nhat f[5][11]: " << f[n][W] << endl;
    cout << "Tap do vat duoc chon: ";
    for (const string& item : selected_items) {
        cout << item << " ";
    }
    cout << endl;
}

int main() {
    knapsack01();
    return 0;
}