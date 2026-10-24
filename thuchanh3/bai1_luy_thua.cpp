#include <iostream>
#include <sstream>
#include <string>

// Luy thua nhanh (chia de tri): tinh A^n mod M, in lan vet tung loi goi.
const long long A = 7;     // co so
const long long M = 1000;  // modulo
int so_goi = 0;  // so loi goi de quy (khong ke loi goi ngoai cung)
int so_le = 0;   // so buoc gap n le

long long luy_thua(long long n) {
    if (n == 0) {
        std::cout << "n = 0: co so, tra ve 1\n";
        return 1 % M;
    }
    ++so_goi;
    long long nua = luy_thua(n / 2);   // chi goi de quy MOT lan
    long long kq = nua * nua % M;
    if (n % 2 == 1) ++so_le;
    if (n % 2 == 1) kq = kq * A % M;   // n le: nhan them mot lan A
    std::cout << "n = " << n << (n % 2 == 1 ? " (le)" : " (chan)")
              << ": nua = " << nua << ", binh phuong mod M = " << nua * nua % M
              << ", tra ve " << kq << "\n";
    return kq;
}

int main() {
    std::cout << "MSSV: N24DCDT059 | Ma ca: 1\n";
    std::cout << "Nhap n (0..60):\n";
    std::string dong;
    std::getline(std::cin, dong);
    std::istringstream bo_doc(dong);
    long long n;
    char du;
    if (!(bo_doc >> n) || (bo_doc >> du) || n < 0 || n > 60) {
        std::cout << "Du lieu khong hop le.\n";
        return 0;
    }
    long long kq = luy_thua(n);
    std::cout << "Ket qua: " << A << "^" << n << " mod " << M << " = " << kq << "\n";
    std::cout << "So loi goi de quy: " << so_goi << "\n";
    std::cout << "So buoc n le: " << so_le << "\n";
    return 0;
}
