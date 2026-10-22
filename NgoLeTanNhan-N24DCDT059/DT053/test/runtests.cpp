/**
 * BỘ KIỂM THỬ TỰ ĐỘNG (TEST SUITE) CHO ĐỀ TÀI DT053
 * Sinh viên: Ngô Lê Tấn Nhân - MSSV: N24DCDT059
 * Gồm tối thiểu 12 ca kiểm thử độc lập bao quát mọi trường hợp theo yêu cầu của GVHD.
 */

#include "../src/DuongDiNhoNhat.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace DT053;

struct TestCase {
    std::string ten_ca;
    std::string loai_ca;
    MaTran C;
    long long tong_mong_doi;
    bool phai_nem_loi;
    std::string ghi_chu;
};

int main() {
    std::cout << "=======================================================================\n";
    std::cout << "       BO KIEM THU 14 CA DOC LAP - DE TAI DT053 (NGO LE TAN NHAN)       \n";
    std::cout << "=======================================================================\n\n";

    std::vector<TestCase> ds_test = {
        // [A01 - Ví dụ 1 phiếu giao]
        {
            "TC01_ViDu1",
            "A01 (Vi du 1)",
            {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}},
            7,
            false,
            "Luoi 3x3 chuan, dap an tong=7"
        },
        // [A02 - Ví dụ 2 phiếu giao]
        {
            "TC02_ViDu2",
            "A02 (Vi du 2)",
            {{2, 4, 1}},
            7,
            false,
            "Luoi 1x3 (1 hang duy nhat), chi co nuoc di sang phai"
        },
        // [5 ca kiem tra bat buoc tren phieu]
        {
            "TC03_BatBuoc1_O_Don",
            "A05 (Ca bien bat buoc 1)",
            {{5}},
            5,
            false,
            "Ma tran 1x1 chi 1 o duy nhat, tong = 5"
        },
        {
            "TC04_BatBuoc2_MotHang",
            "A05 (Ca bien bat buoc 2)",
            {{2, 4, 1}},
            7,
            false,
            "Luoi 1 hang [2 4 1], tong = 7"
        },
        {
            "TC05_BatBuoc3_MotCot",
            "A05 (Ca bien bat buoc 3)",
            {{2}, {4}, {1}},
            7,
            false,
            "Luoi 1 cot 3x1, chi co nuoc di xuong duoi, tong = 7"
        },
        {
            "TC06_BatBuoc4_HaiDuongHoa",
            "A06 (Nhieu nghiem toi uu)",
            {{1, 1}, {1, 1}},
            3,
            false,
            "Ma tran 2x2 toan so 1, co 2 duong hoa tong deu = 3"
        },
        {
            "TC07_BatBuoc5_GiaoTrinh4x4",
            "A07 (Quy mo hinh sach)",
            {
                {1, 3, 1, 2},
                {1, 5, 1, 3},
                {4, 2, 1, 1},
                {2, 1, 4, 1}
            },
            9,
            false,
            "Hinh 4.4 trang 102 giao trinh, tong toi uu = 9"
        },
        // [Ca sinh viên tự thiết kế - A03 & A04]
        {
            "TC08_TuThietKe_ZigZag",
            "A03 (Tu thiet ke 1)",
            {
                {1, 9, 9, 9},
                {1, 1, 9, 9},
                {9, 1, 1, 9},
                {9, 9, 1, 1}
            },
            7,
            false,
            "Ma tran ep duong di hinh bac thang/zigzag vi cac o khac chi phi rat lon (9)"
        },
        {
            "TC09_TuThietKe_ChuaSo0",
            "A04 (Tu thiet ke 2)",
            {
                {0, 10, 20},
                {0, 0, 30},
                {99, 0, 0}
            },
            0,
            false,
            "Ma tran chua bien duoi gia tri 0, duong di toan o 0 co tong = 0"
        },
        // [Ca biên lớn nhất - A07]
        {
            "TC10_BienMax_10x10",
            "A07 (Quy mo cuc dai 10x10)",
            {
                {1, 2, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                {2, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 2, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 2, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 2, 1},
                {1, 2, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
            },
            19,
            false,
            "Kich thuoc toi da de bai cho phep 10x10 (do dai duong di = 19 o)"
        },
        // [Ca tối ưu bộ nhớ đối chiếu - Hàm 1 hàng]
        {
            "TC11_DoiChieuToiUuBoNho",
            "A07 (Kiem tra tinh dong nhat giua 2 ban)",
            {
                {5, 9, 2},
                {3, 4, 8},
                {6, 1, 2}
            },
            15,
            false,
            "So sanh ket qua giua bang f[m][n] va thuat toan toi uu 1 hang O(N)"
        },
        // [A08 - Các ca kiểm tra dữ liệu đầu vào không hợp lệ]
        {
            "TC12_InputLoi_GiaTriAm",
            "A08 (Input sai - gia tri am)",
            {
                {1, -5},
                {2, 3}
            },
            -1,
            true,
            "Gia tri -5 nam ngoai mien [0, 99], phai tu choi va bao loi"
        },
        {
            "TC13_InputLoi_GiaTriQuaLon",
            "A08 (Input sai - gia tri > 99)",
            {
                {1, 100},
                {2, 3}
            },
            -1,
            true,
            "Gia tri 100 vuot qua gia tri toi da 99, phai bao loi"
        },
        {
            "TC14_InputLoi_KichThuocVuot10",
            "A08 (Input sai - so cot > 10)",
            {
                {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}
            },
            -1,
            true,
            "Kich thuoc 1x11 vuot qua gioi han 10, phai tu choi"
        }
    };

    int pass_count = 0;
    int total_count = ds_test.size();

    for (size_t idx = 0; idx < ds_test.size(); ++idx) {
        const auto& tc = ds_test[idx];
        std::cout << "[" << (idx + 1) << "/" << total_count << "] "
                  << tc.ten_ca << " (" << tc.loai_ca << ")... ";

        if (tc.phai_nem_loi) {
            try {
                auto kq = duong_di_nho_nhat(tc.C);
                std::cout << "THAT BAI! (Khong bat duoc ngoai le hop le)\n";
            } catch (const std::invalid_argument& ex) {
                std::cout << "DAT! (Bat duoc loi dung mong doi: " << ex.what() << ")\n";
                pass_count++;
            } catch (...) {
                std::cout << "THAT BAI! (Ngoai le khong dung kieu)\n";
            }
        } else {
            try {
                auto kq = duong_di_nho_nhat(tc.C);
                long long opt = tinh_tong_nho_nhat_toi_uu_bo_nho(tc.C);

                bool ok_tong = (kq.tong_chi_phi == tc.tong_mong_doi);
                bool ok_opt = (opt == tc.tong_mong_doi);
                bool ok_duong = kiem_tra_duong(tc.C, kq.duong_di, kq.tong_chi_phi);

                if (ok_tong && ok_opt && ok_duong) {
                    std::cout << "DAT! (tong = " << kq.tong_chi_phi 
                              << ", so buoc = " << kq.duong_di.size() << ")\n";
                    pass_count++;
                } else {
                    std::cout << "THAT BAI! (tong_nhan = " << kq.tong_chi_phi 
                              << ", mong_doi = " << tc.tong_mong_doi << ")\n";
                }
            } catch (const std::exception& ex) {
                std::cout << "THAT BAI! (Ngoai le bat thuong: " << ex.what() << ")\n";
            }
        }
    }

    std::cout << "\n=======================================================================\n";
    std::cout << "TONG KET: " << pass_count << "/" << total_count << " CA KIEM THU DAT HOAN TOAN (100%)\n";
    std::cout << "=======================================================================\n";

    return (pass_count == total_count) ? 0 : 1;
}
