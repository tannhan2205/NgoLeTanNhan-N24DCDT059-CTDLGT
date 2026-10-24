#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Day con tang dai nhat (quy hoach dong): f[i] = do dai day con tang dai nhat ket thuc dung tai a[i].
const std::vector<int> A = {3, 10, 2, 1, 20, 4, 6, 21, 8};

int day_con_tang(const std::vector<int>& a, std::vector<int>& day) {
    int n = a.size();
    std::vector<int> f(n, 1);     // co so: moi phan tu tu no la mot day con dai 1
    std::vector<int> tu(n, -1);   // tu[i] = chi so dung truoc i trong day con; -1 la khong co
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (a[j] < a[i] && f[j] + 1 > f[i]) {
                f[i] = f[j] + 1;
                tu[i] = j;
            }
        }
        std::cout << "i = " << i + 1 << ": a = " << a[i] << ", f = " << f[i] << ", tu = ";
        if (tu[i] == -1) std::cout << "khong\n"; else std::cout << tu[i] + 1 << "\n";
    }
    int k = 0;
    for (int i = 0; i < n; ++i) if (f[i] > f[k]) k = i;   // vi tri dau tien dat max
    int do_dai = f[k];
    for (int t = k; t != -1; t = tu[t]) day.push_back(a[t]);  // truy vet nguoc theo tu
    std::reverse(day.begin(), day.end());
    return do_dai;
}

int main() {
    std::cout << "MSSV: N24DCDT059 | Ma ca: 1\n";
    std::cout << "Nhap n (1.." << A.size() << "), so phan tu dau tien cua day duoc xet:\n";
    std::string dong;
    std::getline(std::cin, dong);
    std::istringstream bo_doc(dong);
    int n;
    char du;
    if (!(bo_doc >> n) || (bo_doc >> du) || n < 1 || n > (int)A.size()) {
        std::cout << "Du lieu khong hop le.\n";
        return 0;
    }
    std::vector<int> a(A.begin(), A.begin() + n);
    std::cout << "Day xet:";
    for (int v : a) std::cout << " " << v;
    std::cout << "\n";
    std::vector<int> day;
    int do_dai = day_con_tang(a, day);
    std::cout << "Do dai day con tang dai nhat: " << do_dai << "\n";
    std::cout << "Mot day con tang dai nhat:";
    for (int v : day) std::cout << " " << v;
    std::cout << "\n";
    return 0;
}
