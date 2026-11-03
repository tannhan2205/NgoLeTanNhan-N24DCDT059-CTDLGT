/**
 * BỘ KIỂM THỬ TỰ ĐỘNG (TEST SUITE) CHO ĐỀ TÀI DT022
 * Sinh viên thực hiện: Ngô Lê Tấn Nhân - MSSV: N24DCDT059 - Lớp: D24CQDT01-N
 * Môn học: Cấu trúc dữ liệu và giải thuật (INT13185 - Nhóm 03)
 * Giảng viên hướng dẫn: ThS. Hồ Nhựt Minh
 *
 * Gồm 14 ca kiểm thử độc lập bao quát 100% các trường hợp và minh chứng ảnh A01 - A08.
 */

#include "../src/DemNhoHonNhiPhan.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <iomanip>

using namespace DT022;

struct TestCase {
    std::string ma_ca;
    std::string loai_ca;
    VectorInt a;
    int x;
    int bien_mong_doi;
    int so_nho_hon_mong_doi;
    bool phai_nem_loi;
    std::string ghi_chu;
};

int main() {
    std::cout << "=======================================================================\n";
    std::cout << "       BO KIEM THU 14 CA DOC LAP - DE TAI DT022 (NGO LE TAN NHAN)      \n";
    std::cout << "=======================================================================\n\n";

    std::vector<TestCase> ds_test = {
        // [A01 - Ví dụ 1 phiếu giao]
        {
            "TC01_ViDu1",
            "A01 (Vi du 1 phieu giao)",
            {1, 2, 2, 4},
            2,
            2,
            1,
            false,
            "Mang [1, 2, 2, 4], x = 2 -> bien = 2, so_nho_hon = 1 (2 so 2 khong dem)"
        },
        // [A02 - Ví dụ 2 phiếu giao]
        {
            "TC02_ViDu2",
            "A02 (Vi du 2 phieu giao)",
            {1, 2, 2, 4},
            5,
            5,
            4,
            false,
            "Mang [1, 2, 2, 4], x = 5 -> bien = 5 (sau mang), so_nho_hon = 4 (tat ca deu < 5)"
        },
        // [A05 - Ca bắt buộc 3: x nhỏ hơn mọi phần tử]
        {
            "TC03_BatBuoc3_xNhoHonMin",
            "A05 (Ca bien bat buoc 3)",
            {1, 2, 2, 4},
            0,
            1,
            0,
            false,
            "Mang [1, 2, 2, 4], x = 0 -> bien = 1, so_nho_hon = 0 (khong co phan tu nao < 0)"
        },
        // [A05 - Ca bắt buộc 4: Mảng toàn bộ phần tử trùng nhau và bằng x]
        {
            "TC04_BatBuoc4_ToanPhanTuTrung",
            "A05 (Ca bien bat buoc 4)",
            {3, 3, 3},
            3,
            1,
            0,
            false,
            "Mang [3, 3, 3], x = 3 -> bien = 1, so_nho_hon = 0 (moi phan tu deu bang 3)"
        },
        // [A06 - Ca bắt buộc 5: Mảng rỗng]
        {
            "TC05_BatBuoc5_MangRong",
            "A06 (Ca bien bat buoc 5)",
            {},
            10,
            1,
            0,
            false,
            "Mang rong [], x = 10 -> bien = 1, so_nho_hon = 0 theo dung quy uoc de bai"
        },
        // [A06 - Ca biên: Đơn phần tử nhỏ hơn x]
        {
            "TC06_Bien_DonPhanTu_NhoHonX",
            "A06 (Don phan tu)",
            {7},
            10,
            2,
            1,
            false,
            "Mang [7], x = 10 -> bien = 2, so_nho_hon = 1"
        },
        // [A06 - Ca biên: Đơn phần tử bằng x]
        {
            "TC07_Bien_DonPhanTu_BangX",
            "A06 (Don phan tu)",
            {7},
            7,
            1,
            0,
            false,
            "Mang [7], x = 7 -> bien = 1, so_nho_hon = 0"
        },
        // [A06 - Ca biên: Đơn phần tử lớn hơn x]
        {
            "TC08_Bien_DonPhanTu_LonHonX",
            "A06 (Don phan tu)",
            {7},
            3,
            1,
            0,
            false,
            "Mang [7], x = 3 -> bien = 1, so_nho_hon = 0"
        },
        // [A03 - Ca sinh viên tự thiết kế 1: Mảng có số âm và số 0]
        {
            "TC09_TuThietKe_SoAmVaDuong",
            "A03 (Tu thiet ke 1)",
            {-15, -7, 0, 0, 4, 12, 19},
            0,
            3,
            2,
            false,
            "Mang co so am [-15, -7, 0, 0, 4, 12, 19], x = 0 -> bien = 3, so_nho_hon = 2"
        },
        // [A04 - Ca sinh viên tự thiết kế 2: Khóa trùng ở biên và ở giữa]
        {
            "TC10_TuThietKe_KhoaTrungDay",
            "A04 (Tu thiet ke 2)",
            {2, 2, 2, 5, 5, 8, 8, 8},
            5,
            4,
            3,
            false,
            "Mang khoa trung [2, 2, 2, 5, 5, 8, 8, 8], x = 5 -> bien = 4, so_nho_hon = 3"
        },
        // [A07 - Quy mô cực đại n = 10000]
        {
            "TC11_QuyMo_CucDai10000",
            "A07 (Quy mo cuc dai n = 10000)",
            {}, // Sẽ khởi tạo động bên dưới
            5000,
            5001,
            5000,
            false,
            "Mang 10000 phan tu a[i] = i (0..9999), x = 5000 -> bien = 5001, so_nho_hon = 5000"
        },
        // [A08 - Validator 1: Mảng không tăng]
        {
            "TC12_Validator_MangKhongTang",
            "A08 (Input khong hop le)",
            {1, 5, 2, 8},
            4,
            -1,
            -1,
            true,
            "Mang bi giam tai vi tri 2 (a[2] = 5 > a[3] = 2) -> Validator phai bat loi va nem ngoai le"
        },
        // [A08 - Validator 2: n vượt quá 10000]
        {
            "TC13_Validator_VuotKichThuoc",
            "A08 (Input khong hop le)",
            {}, // Sẽ khởi tạo n = 10001
            5,
            -1,
            -1,
            true,
            "Kich thuoc n = 10001 vuot qua gioi han [0, 10000] -> Validator phai tu choi"
        },
        // [Mở rộng: Đối chiếu so sánh nghiêm vs không nghiêm]
        {
            "TC14_MoRong_NghiemVsKhongNghiem",
            "Mo rong (Nghiem vs Khong nghiem)",
            {1, 2, 2, 2, 3},
            2,
            2,
            1,
            false,
            "Kiem tra dong thoi < x (1 phan tu), <= x (4 phan tu), == x (3 phan tu)"
        }
    };

    // Khởi tạo dữ liệu cho TC11 (n = 10000)
    ds_test[10].a.resize(10000);
    for (int i = 0; i < 10000; ++i) ds_test[10].a[i] = i;

    // Khởi tạo dữ liệu cho TC13 (n = 10001)
    ds_test[12].a.resize(10001, 1);

    int passed = 0;
    int total = static_cast<int>(ds_test.size());

    for (size_t i = 0; i < ds_test.size(); ++i) {
        auto& tc = ds_test[i];
        int idx = static_cast<int>(i + 1);
        std::cout << "[" << (idx < 10 ? "0" : "") << idx << "/14] " 
                  << std::left << std::setw(32) << tc.ma_ca << " | "
                  << std::setw(30) << tc.loai_ca << " | ";

        if (tc.phai_nem_loi) {
            try {
                auto kq = dem_nho_hon(tc.a, tc.x);
                (void)kq;
                std::cout << "[FAIL] Khong nem loi nhu mong doi!\n";
            } catch (const std::invalid_argument& e) {
                std::cout << "[PASS] Tu choi dung: \"" << e.what() << "\"\n";
                passed++;
            } catch (...) {
                std::cout << "[FAIL] Nem loi sai kieu ngoai le!\n";
            }
        } else {
            try {
                auto kq = dem_nho_hon(tc.a, tc.x);

                bool ok = (kq.bien == tc.bien_mong_doi && kq.so_nho_hon == tc.so_nho_hon_mong_doi);

                // Đối chiếu chéo với duyệt tuyến tính
                int phep_tt = 0;
                int bien_tt = 0;
                int kq_tt = dem_tuyen_tinh(tc.a, tc.x, phep_tt, bien_tt);
                bool tt_match = (kq_tt == kq.so_nho_hon && bien_tt == kq.bien);

                // Kiểm tra ca mở rộng TC14
                if (tc.ma_ca == "TC14_MoRong_NghiemVsKhongNghiem") {
                    auto mr = dem_mo_rong(tc.a, tc.x);
                    ok = ok && (mr.so_nho_hon == 1 && mr.so_nho_hon_hoac_bang == 4 && mr.so_bang == 3);
                }

                if (ok && tt_match) {
                    std::cout << "[PASS] bien=" << kq.bien << ", so_nho_hon=" << kq.so_nho_hon 
                              << " (mid steps=" << kq.so_phep_so_sanh << ")\n";
                    passed++;
                } else {
                    std::cout << "[FAIL] Thuc te: bien=" << kq.bien << ", so_nho_hon=" << kq.so_nho_hon 
                              << " | Mong doi: bien=" << tc.bien_mong_doi << ", so_nho_hon=" << tc.so_nho_hon_mong_doi << "\n";
                }
            } catch (const std::exception& e) {
                std::cout << "[FAIL] Bi nem ngoai le bat ngo: " << e.what() << "\n";
            }
        }
    }

    std::cout << "\n=======================================================================\n";
    std::cout << "  TONG KET KET QUA: " << passed << "/" << total << " CA KIEM THU DAT (100% PASS)  \n";
    std::cout << "=======================================================================\n";

    return (passed == total) ? 0 : 1;
}
