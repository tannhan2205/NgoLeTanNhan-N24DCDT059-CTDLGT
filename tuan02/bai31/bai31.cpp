#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

int main() {
    // Tối ưu tốc độ đọc dữ liệu với 10^6 số
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if (!(cin >> n) || n <= 0) return 0;

    long long tong = 0;
    int nho_nhat, lon_nhat;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x; // Đọc trực tiếp từng số, không lưu mảng
        tong += x;
        if (i == 0) {
            nho_nhat = x;
            lon_nhat = x;
        } else {
            if (x < nho_nhat) nho_nhat = x;
            if (x > lon_nhat) lon_nhat = x;
        }
    }
    double tbc = (double)tong / n;
    cout << tong << " " << fixed << setprecision(4) << tbc << " " << nho_nhat << " " << lon_nhat << "\n";
    return 0;
}