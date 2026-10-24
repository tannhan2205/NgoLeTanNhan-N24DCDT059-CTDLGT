#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int liet_ke(int n) {
    std::vector<int> x(n, 0);
    int dem = 0;
    while (true) {
        for (int v : x) std::cout << v;
        std::cout << "\n";
        ++dem;
        int i = n - 1;
        while (i >= 0 && x[i] == 1) {
            x[i] = 0;  // Xoa cac bit 1 lien tiep o duoi.
            --i;
        }
        if (i < 0) break;
        x[i] = 1;
    }
    return dem;
}

int main() {
    std::cout << "MSSV: DIEN_MSSV | Ma ca: DIEN_MA_CA\n";
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
    std::cout << "Tong so xau: " << dem << "\n";
    return 0;
}
