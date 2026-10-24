#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int liet_ke(int n) {
    std::vector<int> x(n, 0);
    int dem = 0;
    int k = 1, dem_dat = 0;
    while (true) {
        int so_bit_1 = 0;
        for (int v : x) so_bit_1 += v;
        if (so_bit_1 == k) {
            for (int v : x) std::cout << v;
            std::cout << "\n";
            ++dem_dat;
        }
        ++dem;
        int i = n - 1;
        while (i >= 0 && x[i] == 1) {
            x[i] = 0;  // Xoa cac bit 1 lien tiep o duoi.
            --i;
        }
        if (i < 0) break;
        x[i] = 1;
    }
    std::cout << "So xau dat: " << dem_dat << "\n";
    return dem;
}

int main() {
    std::cout << "MSSV: N24DCDT059 | Ma ca: 1\n";
    std::cout << "Nhap n (1..10):\n";
    std::string dong;
    std::getline(std::cin, dong);
    std::istringstream bo_doc(dong);
    int n;
    char du;
    if (!(bo_doc >> n) || (bo_doc >> du) || n < 1 || n > 10) {
        std::cout << "Du lieu khong hop le.\n";
        return 0;
    }
    int dem = liet_ke(n);
    std::cout << "Tong so xau da duyet: " << dem << "\n";
    return 0;
}