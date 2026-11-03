/**
 * CHƯƠNG TRÌNH CHÍNH (DEMO & NHẬP TỪ BÀN PHÍM)
 * Đề tài DT022: Đếm số phần tử nhỏ hơn x bằng tìm kiếm nhị phân
 * Sinh viên thực hiện: Ngô Lê Tấn Nhân - MSSV: N24DCDT059 - Lớp: D24CQDT01-N
 * Môn học: Cấu trúc dữ liệu và giải thuật (INT13185 - Nhóm 03)
 * Giảng viên hướng dẫn: ThS. Hồ Nhựt Minh
 */

#include "DemNhoHonNhiPhan.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace DT022;

void in_banner() {
    std::cout << "=======================================================================\n";
    std::cout << "      HOC VIEN CONG NGHE BUU CHINH VIEN THONG - CO SO TAI TP.HCM       \n";
    std::cout << "      MON HOC: CAU TRUC DU LIEU VA GIAI THUAT (INT13185 - NHOM 03)     \n";
    std::cout << "  DE TAI DT022: DEM SO PHAN TU NHO HON X BANG TIM KIEM NHI PHAN         \n";
    std::cout << "  Sinh vien: Ngo Le Tan Nhan - MSSV: N24DCDT059 - Lop: D24CQDT01-N     \n";
    std::cout << "  Giang vien huong dan: ThS. Ho Nhut Minh                              \n";
    std::cout << "=======================================================================\n\n";
}

void in_mang(const VectorInt& a) {
    std::cout << "Mang a (n = " << a.size() << "): [";
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i];
        if (i + 1 < a.size()) std::cout << ", ";
    }
    std::cout << "]\n";
}

void in_bang_lan_vet(const std::vector<BuocLanVet>& trace, int x) {
    if (trace.empty()) {
        std::cout << "  (Mang rong, khong thuc hien buoc chia nhi phan nao)\n";
        return;
    }
    std::cout << "\n--- BANG LAN VET CHI TIET CAC BUOC NHI PHAN (Khoa x = " << x << ") ---\n";
    std::cout << "+------+-------+--------+-----+--------+---------------+----------+------------------------------------------------+\n";
    std::cout << "| Buoc | Left  | Right  | Mid | a[Mid] | a[Mid] >= x ? | Bien tam | Hanh dong chuyen nhanh                         |\n";
    std::cout << "+------+-------+--------+-----+--------+---------------+----------+------------------------------------------------+\n";

    for (const auto& b : trace) {
        std::cout << "| " << std::setw(4) << b.buoc << " | "
                  << std::setw(5) << b.left << " | "
                  << std::setw(6) << b.right << " | "
                  << std::setw(3) << b.mid << " | "
                  << std::setw(6) << b.gia_tri_mid << " | "
                  << std::setw(13) << (b.dieu_kien_ge ? "DUNG (>=)" : "SAI (<)") << " | "
                  << std::setw(8) << b.bien_tam << " | "
                  << std::left << std::setw(46) << b.hanh_dong << std::right << " |\n";
    }
    std::cout << "+------+-------+--------+-----+--------+---------------+----------+------------------------------------------------+\n";
}

void in_ket_qua(const KetQuaDem& kq, int x, const std::string& giai_thich = "") {
    std::cout << "\n>>> KET QUA GIAI THUAT:\n";
    std::cout << "    so_nho_hon=" << kq.so_nho_hon << "; bien=" << kq.bien << "\n";
    std::cout << "    So phep so sanh (so lan chia mid): " << kq.so_phep_so_sanh << "\n";
    if (!giai_thich.empty()) {
        std::cout << "    Giai thich: " << giai_thich << "\n";
    }
}

int main(int argc, char* argv[]) {
    // 1. Chạy tham số dòng lệnh CLI trực tiếp theo chuẩn A01, A02
    if (argc > 1 && std::string(argv[1]) == "--vd1") {
        in_banner();
        std::cout << "--- [CHAY VI DU 1 PHIEU GIAO] ---\n";
        VectorInt a = {1, 2, 2, 4};
        int x = 2;
        in_mang(a);
        std::cout << "Khoa can dem: x = " << x << "\n";
        auto kq = dem_nho_hon(a, x);
        in_bang_lan_vet(kq.lan_vet, x);
        in_ket_qua(kq, x, "Hai phan tu bang 2 khong duoc dem.");
        return 0;
    }

    if (argc > 1 && std::string(argv[1]) == "--vd2") {
        in_banner();
        std::cout << "--- [CHAY VI DU 2 PHIEU GIAO] ---\n";
        VectorInt a = {1, 2, 2, 4};
        int x = 5;
        in_mang(a);
        std::cout << "Khoa can dem: x = " << x << "\n";
        auto kq = dem_nho_hon(a, x);
        in_bang_lan_vet(kq.lan_vet, x);
        in_ket_qua(kq, x, "Moi phan tu nho hon 5; bien o sau mang (bien = n + 1 = 5).");
        return 0;
    }

    // 2. Chế độ tương tác dòng lệnh
    in_banner();
    std::cout << "Chon che do hoat dong:\n";
    std::cout << "  1. Chay Vi du 1 phieu giao (a = [1, 2, 2, 4], x = 2)\n";
    std::cout << "  2. Chay Vi du 2 phieu giao (a = [1, 2, 2, 4], x = 5)\n";
    std::cout << "  3. Nhap mang moi va khoa x tuy y tu ban phim\n";
    std::cout << "  4. [MO RONG] So sanh bat dang thuc nghiem (< x) vs khong nghiem (<= x) & dem khoa trung\n";
    std::cout << "  5. [KHAO SAT] Do so phep so sanh O(log n) vs O(n) tren cac quy mo n = 5, 50, 500, 5000\n";
    std::cout << "Nhap lua chon cua ban (1-5): ";

    int choice = 1;
    if (!(std::cin >> choice)) {
        choice = 1;
    }

    std::cout << "\n";

    if (choice == 1) {
        std::cout << "--- [VI DU 1 PHIEU GIAO] ---\n";
        VectorInt a = {1, 2, 2, 4};
        int x = 2;
        in_mang(a);
        std::cout << "Khoa x = " << x << "\n";
        auto kq = dem_nho_hon(a, x);
        in_bang_lan_vet(kq.lan_vet, x);
        in_ket_qua(kq, x, "Hai phan tu bang 2 khong duoc dem.");
    } else if (choice == 2) {
        std::cout << "--- [VI DU 2 PHIEU GIAO] ---\n";
        VectorInt a = {1, 2, 2, 4};
        int x = 5;
        in_mang(a);
        std::cout << "Khoa x = " << x << "\n";
        auto kq = dem_nho_hon(a, x);
        in_bang_lan_vet(kq.lan_vet, x);
        in_ket_qua(kq, x, "Moi phan tu nho hon 5; bien o sau mang (bien = 5).");
    } else if (choice == 3) {
        std::cout << "--- [NHAP DU LIEU TU BAN PHIM] ---\n";
        std::cout << "Nhap so luong phan tu n (0 <= n <= 10000): ";
        int n;
        if (!(std::cin >> n)) {
            std::cout << "Loi: n phai la so nguyen.\n";
            return 1;
        }

        // Kiem tra hop le n truoc khi cap phat vector de tranh crash khi n < 0 hoac n > 10000
        if (n < 0 || n > 10000) {
            std::cout << "\n[!] TU CHOI INPUT: So luong phan tu n phai trong khoang [0, 10000]. Gia tri nhap: " << n << "\n";
            return 1;
        }

        VectorInt a(n);
        if (n > 0) {
            std::cout << "Nhap " << n << " phan tu da sap tang khong giam (cach nhau boi dau cach):\n";
            for (int i = 0; i < n; ++i) {
                if (!(std::cin >> a[i])) {
                    std::cout << "Loi: Phan tu thu " << (i + 1) << " khong phai la so nguyen hop le.\n";
                    return 1;
                }
            }
        }

        std::cout << "Nhap gia tri khoa can dem x: ";
        int x;
        if (!(std::cin >> x)) {
            std::cout << "Loi: Khoa x phai la so nguyen hop le.\n";
            return 1;
        }

        std::string err;
        if (!kiem_tra_hop_le_mang(a, err)) {
            std::cout << "\n[!] TU CHOI INPUT: " << err << "\n";
            return 1;
        }

        in_mang(a);
        std::cout << "Khoa can dem: x = " << x << "\n";

        auto kq = dem_nho_hon(a, x);
        in_bang_lan_vet(kq.lan_vet, x);
        in_ket_qua(kq, x);

        // Đối chiếu với tìm kiếm tuyến tính
        int phep_so_sanh_tt = 0;
        int bien_tt = 0;
        int kq_tt = dem_tuyen_tinh(a, x, phep_so_sanh_tt, bien_tt);

        std::cout << "\n--- DOI CHIEU DOC LAP BANG QUET TUYEN TINH O(N) ---\n";
        std::cout << "    Ket qua tuyen tinh: so_nho_hon = " << kq_tt << ", bien = " << bien_tt << "\n";
        std::cout << "    So phep so sanh tuyen tinh: " << phep_so_sanh_tt << " so voi Nhi phan: " << kq.so_phep_so_sanh << "\n";
        if (kq_tt == kq.so_nho_hon && bien_tt == kq.bien) {
            std::cout << "    => XAC NHAN: Hai thuat toan hoan toan dong thuan 100%!\n";
        } else {
            std::cout << "    => CANH BAO: Phat hien su bat nhat giua hai thuat toan!\n";
        }
    } else if (choice == 4) {
        std::cout << "--- [MO RONG: PHAN BIET NGHIEM (<) VS KHONG NGHIEM (<=)] ---\n";
        std::cout << "Mang mau co khoa trung: a = [1, 2, 2, 2, 4, 5, 5, 8], khoa x = 2\n";
        VectorInt a = {1, 2, 2, 2, 4, 5, 5, 8};
        int x = 2;
        in_mang(a);
        auto kq = dem_mo_rong(a, x);

        std::cout << "\nPhan tich ket qua tren cung mot mang va khoa x = " << x << ":\n";
        std::cout << "1. Vi tri dau tien a[i] >= x (Lower bound): bien_ge = " << kq.bien_ge << "\n";
        std::cout << "   -> So phan tu < x: " << kq.so_nho_hon << "\n";
        std::cout << "2. Vi tri dau tien a[i] > x (Upper bound): bien_gt = " << kq.bien_gt << "\n";
        std::cout << "   -> So phan tu <= x: " << kq.so_nho_hon_hoac_bang << "\n";
        std::cout << "3. Tuan suat xuat hien dung bang x: " << kq.so_bang << " phan tu.\n";
        std::cout << "\nKet luan:\n";
        std::cout << "- De dem < x: dung dieu kien ranh gioi a[mid] >= x de thu hep phai ve [1, mid - 1].\n";
        std::cout << "- De dem <= x: dung dieu kien ranh gioi a[mid] > x de thu hep phai ve [1, mid - 1].\n";
    } else if (choice == 5) {
        std::cout << "--- [KHAO SAT THUC NGHIEM DO PHUC TAP THEO QUY MO N] ---\n";
        std::cout << "Do so phep xet mid tren mang tang chan a[i] = i * 2, khoa x = n (nam giua mang):\n\n";
        std::cout << "+---------+-------+--------------------+------------------------+-------------------+-----------------------+\n";
        std::cout << "| Quy mo n| Khoa x| Phep so sanh BS    | Phep so sanh Tuyen tinh| Thoi gian BS (us) | Thoi gian TT (us)     |\n";
        std::cout << "+---------+-------+--------------------+------------------------+-------------------+-----------------------+\n";

        std::vector<int> cac_n = {5, 50, 500, 5000};
        std::vector<KetQuaKhaoSat> ds_kq;
        for (int n : cac_n) {
            auto ks = khao_sat_quy_mo(n, n);
            ds_kq.push_back(ks);
            std::cout << "| " << std::setw(7) << ks.n << " | "
                      << std::setw(5) << ks.x << " | "
                      << std::setw(18) << ks.phep_so_sanh_bs << " | "
                      << std::setw(22) << ks.phep_so_sanh_linear << " | "
                      << std::setw(17) << std::fixed << std::setprecision(2) << ks.thoi_gian_bs_us << " | "
                      << std::setw(21) << std::fixed << std::setprecision(2) << ks.thoi_gian_linear_us << " |\n";
        }
        std::cout << "+---------+-------+--------------------+------------------------+-------------------+-----------------------+\n";
        std::cout << "\nNhan xet:\n";
        std::cout << "- Voi n tang tu " << ds_kq.front().n << " den " << ds_kq.back().n 
                  << " (gap " << (ds_kq.back().n / ds_kq.front().n) << " lan), so phep so sanh cua Binary Search chi tang tu " 
                  << ds_kq.front().phep_so_sanh_bs << " len " << ds_kq.back().phep_so_sanh_bs 
                  << " phep (luon <= ceil(log2(n)) + 1).\n";
        std::cout << "- Trong khi do, tim kiem tuyen tinh tang tuyen tinh tu " 
                  << ds_kq.front().phep_so_sanh_linear << " len " << ds_kq.back().phep_so_sanh_linear 
                  << " phep so sanh (gap hon " << (ds_kq.back().phep_so_sanh_linear / ds_kq.front().phep_so_sanh_linear) << " lan).\n";
        std::cout << "- Dieu nay chung minh ro rang uu the vuot troi cua O(log n) so voi O(n).\n";
    }

    return 0;
}
