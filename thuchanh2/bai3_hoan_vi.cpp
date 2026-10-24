#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int thu(int i, int n, std::vector<int>& x,
        std::vector<bool>& da_dung) {
    if (i == n) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) std::cout << " ";
            std::cout << x[j];
        }
        std::cout << "\n";
        return 1;
    }
    int dem = 0;
    for (int v = 1; v <= n; ++v) {
        if (!da_dung[v]) {
            x[i] = v;
            da_dung[v] = true;
            dem += thu(i + 1, n, x, da_dung);
            da_dung[v] = false;  // Hoan tac.
        }
    }
    return dem;
}

int liet_ke(int n) {
    std::vector<int> x(n, 0);
    std::vector<bool> da_dung(n + 1, false);
    return thu(0, n, x, da_dung);
}

int main() {
    std::cout << "MSSV: N24DCDT059 | Ma ca: 1\n";
    std::cout << "Nhap n (1..7):\n";
    std::string dong;
    std::getline(std::cin, dong);
    std::istringstream bo_doc(dong);
    int n;
    char du;
    if (!(bo_doc >> n) || (bo_doc >> du) || n < 1 || n > 7) {
        std::cout << "Du lieu khong hop le.\n";
        return 0;
    }
    int dem = liet_ke(n);
    std::cout << "Tong so hoan vi: " << dem << "\n";
    return 0;
}
