#include <iostream>
#include <vector>

using namespace std;

void solve(const vector<int>& a, int x, int test_num) {
    cout << "=== TEST CASE " << test_num << " ===" << "\n";
    cout << "Array: [";
    for (size_t i = 0; i < a.size(); ++i) {
        cout << a[i] << (i + 1 < a.size() ? ", " : "");
    }
    cout << "], x = " << x << "\n";

    int n = a.size();

    if (n == 0) {
        cout << "FIRST -1\nCOUNT 0\nLOWER 0\nUPPER 0\nPROBES 0\n\n";
        return;
    }

    // Kiểm tra tính chất không giảm của mảng
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1]) {
            cout << "ERROR: array must be sorted\n\n";
            return;
        }
    }

    // lower_bound
    int probes_lower = 0;
    int low = 0, high = n;
    while (low < high) {
        int mid = low + (high - low) / 2;
        probes_lower++;
        if (a[mid] >= x) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    int lower = low;

    // upper_bound
    int probes_upper = 0;
    low = 0;
    high = n;
    while (low < high) {
        int mid = low + (high - low) / 2;
        probes_upper++;
        if (a[mid] > x) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    int upper = low;

    int count = upper - lower;
    int first = (count > 0) ? lower : -1;
    int probes = probes_lower + probes_upper;

    cout << "FIRST " << first << "\n";
    cout << "COUNT " << count << "\n";
    cout << "LOWER " << lower << "\n";
    cout << "UPPER " << upper << "\n";
    cout << "PROBES " << probes << "\n\n";
}

int main() {
    struct TestCase {
        vector<int> a;
        int x;
    };

    vector<TestCase> tests = {
        {{1, 2, 2, 5, 7, 9}, 2},   // Test gốc trong đề
        {{}, 2},                    // Dãy rỗng
        {{2, 2, 2}, 2},             // Ca trùng lặp hoàn toàn
        {{1, 2, 2, 5, 7, 9}, 4},   // x không có trong dãy (ở giữa)
        {{1, 2, 2, 5, 7, 9}, 0},   // x nhỏ hơn toàn bộ dãy
        {{1, 2, 2, 5, 7, 9}, 10},  // x lớn hơn toàn bộ dãy
        {{7, 2, 5, 2, 9, 1}, 2}    // Ca báo lỗi chưa sắp xếp
    };

    for (size_t i = 0; i < tests.size(); ++i) {
        solve(tests[i].a, tests[i].x, i + 1);
    }

    return 0;
}