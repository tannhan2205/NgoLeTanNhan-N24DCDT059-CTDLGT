#include <iostream>
#include <vector>

using namespace std;

pair<int, int> linear_search(const vector<long long>& A, long long x) {
    int first_idx = -1;
    int search_cmps = 0;
    for (int i = 0; i < A.size(); i++) {
        search_cmps++;
        if (A[i] == x) {
            first_idx = i;
            break;
        }
    }
    return {first_idx, search_cmps};
}

long long count_pairs(int n) {
    long long pairs = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            pairs++;
        }
    }
    return pairs;
}

int main() {
    int n;
    if (!(cin >> n)) return 0;

    if (n == 0) {
        long long x;
        if (cin >> x) {}
        cout << "SUM 0\nMIN NA\nMAX NA\nFIRST -1\nSEARCH_CMPS 0\nPAIRS 0\nDOUBLINGS 0\nSCAN_VISITS 0\n";
        return 0;
    }

    vector<long long> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    long long x;
    cin >> x;

    long long sum_val = 0;
    long long min_val = A[0];
    long long max_val = A[0];
    int scan_visits = 0;

    for (int i = 0; i < n; i++) {
        sum_val += A[i];
        if (A[i] < min_val) min_val = A[i];
        if (A[i] > max_val) max_val = A[i];
        scan_visits++;
    }

    auto [first_idx, search_cmps] = linear_search(A, x);
    long long pairs = count_pairs(n);

    int doublings = 0;
    for (long long i = 1; i <= n; i *= 2) {
        doublings++;
    }

    cout << "SUM " << sum_val << "\n";
    cout << "MIN " << min_val << "\n";
    cout << "MAX " << max_val << "\n";
    cout << "FIRST " << first_idx << "\n";
    cout << "SEARCH_CMPS " << search_cmps << "\n";
    cout << "PAIRS " << pairs << "\n";
    cout << "DOUBLINGS " << doublings << "\n";
    cout << "SCAN_VISITS " << scan_visits << "\n";

    return 0;
}