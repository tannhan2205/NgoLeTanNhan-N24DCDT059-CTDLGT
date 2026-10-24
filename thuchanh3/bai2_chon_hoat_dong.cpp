#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// Chon hoat dong (tham lam): sap xep theo tieu chi roi quet, chon neu khong chong lan.
typedef std::pair<int, int> HoatDong;  // (bat dau, ket thuc)
std::vector<HoatDong> HD = {{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 9}, {5, 9},
                            {6, 10}, {8, 11}, {8, 12}, {2, 14}, {12, 16}};

int khoa(const HoatDong& hd, int tieu_chi) {
    if (tieu_chi == 1) return hd.second;              // ket thuc som nhat
    if (tieu_chi == 2) return hd.first;               // bat dau som nhat
    return hd.second - hd.first;                      // ngan nhat
}

bool tuong_thich(const HoatDong& hd, const std::vector<HoatDong>& da_chon) {
    for (const HoatDong& c : da_chon) {
        if (hd.first < c.second && c.first < hd.second)  // chong len nhau
            return false;
    }
    return true;
}

std::vector<HoatDong> chon_hoat_dong(int tieu_chi) {
    std::vector<HoatDong> thu_tu = HD;
    std::stable_sort(thu_tu.begin(), thu_tu.end(), [tieu_chi](const HoatDong& a, const HoatDong& b) {
        return khoa(a, tieu_chi) < khoa(b, tieu_chi); });  // buoc sap xep
    std::vector<HoatDong> da_chon;
    for (const HoatDong& hd : thu_tu) {
        if (tuong_thich(hd, da_chon)) {
            da_chon.push_back(hd);
            std::cout << "Xet (" << hd.first << ", " << hd.second << ") -> CHON\n";
        } else {
            std::cout << "Xet (" << hd.first << ", " << hd.second
                      << ") -> bo, chong lan voi hoat dong da chon\n";
        }
    }
    return da_chon;
}

int main() {
    std::cout << "MSSV: N24DCDT059 | Ma ca: 1\n";
    std::cout << "Nhap tieu chi (1: ket thuc som nhat, 2: bat dau som nhat, 3: ngan nhat):\n";
    std::string dong;
    std::getline(std::cin, dong);
    std::istringstream bo_doc(dong);
    int tieu_chi;
    char du;
    if (!(bo_doc >> tieu_chi) || (bo_doc >> du) || tieu_chi < 1 || tieu_chi > 3) {
        std::cout << "Du lieu khong hop le.\n";
        return 0;
    }
    std::vector<HoatDong> da_chon = chon_hoat_dong(tieu_chi);
    std::cout << "Cac hoat dong duoc chon:";
    for (const HoatDong& hd : da_chon) std::cout << " (" << hd.first << "," << hd.second << ")";
    std::cout << "\n";
    std::cout << "So hoat dong duoc chon: " << da_chon.size() << "\n";
    return 0;
}
