#include <iostream>
#include <sstream>
#include <string>

// Thu tu tham so: n, nguon, trung_gian, dich.
int ha_noi(int n, char a, char b, char c) {
    if (n == 0) return 0;
    int trai = ha_noi(n - 1, a, c, b);
    std::cout << "Dia " << n << ": " << a << " -> " << c << "\n";
    int phai = ha_noi(n - 1, b, a, c);
    return trai + 1 + phai;
}

int main() {
    std::cout << "MSSV: N24DCDT059 | Ma ca: 1\n";
    std::cout << "Nhap n (1..8):\n";
    std::string dong;
    std::getline(std::cin, dong);
    std::istringstream bo_doc(dong);
    int n;
    char du;
    if (!(bo_doc >> n) || (bo_doc >> du) || n < 1 || n > 8) {
        std::cout << "Du lieu khong hop le.\n";
        return 0;
    }
    int dem = ha_noi(n, 'A', 'B', 'C');
    std::cout << "Tong so nuoc di: " << dem << "\n";
    return 0;
}
