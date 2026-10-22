/**
 * CHƯƠNG TRÌNH CHÍNH (DEMO & NHẬP TỪ BÀN PHÍM)
 * Đề tài DT053: Đường đi có tổng nhỏ nhất trên lưới
 * Sinh viên: Ngô Lê Tấn Nhân - MSSV: N24DCDT059
 */

#include "DuongDiNhoNhat.hpp"
#include <iostream>
#include <iomanip>

using namespace DT053;

void in_ma_tran(const MaTran& C) {
    std::cout << "Ma tran C:\n";
    for (const auto& row : C) {
        std::cout << "  ";
        for (int val : row) {
            std::cout << std::setw(3) << val << " ";
        }
        std::cout << "\n";
    }
}

void in_bang_quy_hoach_dong(const std::vector<std::vector<long long>>& f) {
    std::cout << "Bang quy hoach dong f[i][j]:\n";
    for (const auto& row : f) {
        std::cout << "  ";
        for (long long val : row) {
            std::cout << std::setw(4) << val << " ";
        }
        std::cout << "\n";
    }
}

void in_ket_qua(const KetQuaDuongDi& kq) {
    std::cout << "tong=" << kq.tong_chi_phi << "; duong=[";
    for (size_t i = 0; i < kq.duong_di.size(); ++i) {
        std::cout << "(" << kq.duong_di[i].first << ", " << kq.duong_di[i].second << ")";
        if (i + 1 < kq.duong_di.size()) std::cout << ", ";
    }
    std::cout << "]\n";
}

int main(int argc, char* argv[]) {
    std::cout << "===============================================================\n";
    std::cout << "  HOC VIEN CONG NGHE BUU CHINH VIEN THONG - CO SO TAI TP.HCM   \n";
    std::cout << "  MON: CAU TRUC DU LIEU VA GIAI THUAT (INT13185 - NHOM 03)     \n";
    std::cout << "  DE TAI DT053: DUONG DI CO TONG NHO NHAT TREN LUOI            \n";
    std::cout << "  Sinh vien: Ngo Le Tan Nhan - MSSV: N24DCDT059 - Lop: D24CQDT01-N\n";
    std::cout << "===============================================================\n\n";

    if (argc > 1 && std::string(argv[1]) == "--vd1") {
        std::cout << "--- [CHAY VI DU 1] ---\n";
        MaTran C = {
            {1, 3, 1},
            {1, 5, 1},
            {4, 2, 1}
        };
        in_ma_tran(C);
        auto kq = duong_di_nho_nhat(C);
        std::cout << "\nKet qua:\n";
        in_bang_quy_hoach_dong(kq.f);
        std::cout << "Dap an theo mau:\n";
        in_ket_qua(kq);
        return 0;
    }

    if (argc > 1 && std::string(argv[1]) == "--vd2") {
        std::cout << "--- [CHAY VI DU 2] ---\n";
        MaTran C = {
            {2, 4, 1}
        };
        in_ma_tran(C);
        auto kq = duong_di_nho_nhat(C);
        std::cout << "\nKet qua:\n";
        in_bang_quy_hoach_dong(kq.f);
        std::cout << "Dap an theo mau:\n";
        in_ket_qua(kq);
        return 0;
    }

    std::cout << "Chon che do chay:\n";
    std::cout << "  1. Chay Vi du 1 (C = [1 3 1; 1 5 1; 4 2 1])\n";
    std::cout << "  2. Chay Vi du 2 (C = [2 4 1])\n";
    std::cout << "  3. Nhap ma tran tuy y tu ban phim\n";
    std::cout << "Nhap lua chon (1/2/3): ";

    int choice = 1;
    if (!(std::cin >> choice)) {
        choice = 1;
    }

    if (choice == 1) {
        MaTran C = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
        in_ma_tran(C);
        auto kq = duong_di_nho_nhat(C);
        std::cout << "\n";
        in_bang_quy_hoach_dong(kq.f);
        in_ket_qua(kq);
    } else if (choice == 2) {
        MaTran C = {{2, 4, 1}};
        in_ma_tran(C);
        auto kq = duong_di_nho_nhat(C);
        std::cout << "\n";
        in_bang_quy_hoach_dong(kq.f);
        in_ket_qua(kq);
    } else {
        int m, n;
        std::cout << "Nhap so hang m (1 <= m <= 10): ";
        std::cin >> m;
        std::cout << "Nhap so cot n (1 <= n <= 10): ";
        std::cin >> n;

        MaTran C(m, std::vector<int>(n));
        std::cout << "Nhap cac phan tu ma tran (" << m << "x" << n << ", cac so nguyen 0..99):\n";
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> C[i][j];
            }
        }

        try {
            auto kq = duong_di_nho_nhat(C);
            std::cout << "\n--- KET QUA ---\n";
            in_ma_tran(C);
            in_bang_quy_hoach_dong(kq.f);
            in_ket_qua(kq);

            long long opt = tinh_tong_nho_nhat_toi_uu_bo_nho(C);
            std::cout << "(Kiem tra ban toi uu bo nho 1 hang: tong = " << opt << ")\n";
        } catch (const std::exception& ex) {
            std::cerr << "Loi xay ra: " << ex.what() << "\n";
        }
    }

    return 0;
}
