#pragma once
/**
 * ĐỀ TÀI DT022: ĐẾM SỐ PHẦN TỬ NHỎ HƠN X BẰNG TÌM KIẾM NHỊ PHÂN
 * Học phần: Cấu trúc dữ liệu và giải thuật (INT13185) - Nhóm 03
 * Sinh viên thực hiện: Ngô Lê Tấn Nhân
 * MSSV: N24DCDT059
 * Lớp: D24CQDT01-N
 * Giảng viên hướng dẫn: ThS. Hồ Nhựt Minh
 * Học viện Công nghệ Bưu chính Viễn thông - Cơ sở tại TP. Hồ Chí Minh
 *
 * Giáo trình tham khảo: INT1306 - Chương 2, Mục 2.6.2; mục 2.8 bài 22; trang in 50–52, 61.
 */

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <chrono>

namespace DT022 {

using VectorInt = std::vector<int>;

/**
 * Cấu trúc lưu thông tin từng bước lần vết tìm kiếm nhị phân (1-based index theo quy ước giáo trình)
 */
struct BuocLanVet {
    int buoc;               // Thứ tự bước lặp (1, 2, ...)
    int left;               // Biên trái hiện tại (1-based)
    int right;              // Biên phải hiện tại (1-based)
    int mid;                // Chỉ số giữa (1-based)
    int gia_tri_mid;        // Giá trị phần tử a[mid]
    bool dieu_kien_ge;      // True nếu a[mid] >= x, False nếu a[mid] < x
    int bien_tam;           // Vị trí biên đầu tiên thỏa mãn hiện tại
    std::string hanh_dong;  // Mô tả hành động chuyển nhánh
};

/**
 * Cấu trúc chứa kết quả giải thuật:
 * - bien: Vị trí đầu tiên có a[i] >= x (1-based; nếu không có quy ước là n + 1)
 * - so_nho_hon: Số phần tử có giá trị < x (bằng bien - 1)
 * - so_phep_so_sanh: Số lần xét mid trong vòng lặp nhị phân
 * - lan_vet: Danh sách các bước lần vết chi tiết
 */
struct KetQuaDem {
    int bien;
    int so_nho_hon;
    int so_phep_so_sanh;
    std::vector<BuocLanVet> lan_vet;
};

/**
 * Cấu trúc chứa kết quả mở rộng (Phân biệt nghiêm < x vs không nghiêm <= x)
 */
struct KetQuaMoRong {
    int bien_ge;                // Vị trí đầu tiên a[i] >= x (Lower bound, 1-based)
    int so_nho_hon;             // Số phần tử < x
    int bien_gt;                // Vị trí đầu tiên a[i] > x (Upper bound, 1-based)
    int so_nho_hon_hoac_bang;   // Số phần tử <= x
    int so_bang;                // Số phần tử đúng bằng x (so_nho_hon_hoac_bang - so_nho_hon)
};

/**
 * Kiểm tra tính hợp lệ của dữ liệu đầu vào theo yêu cầu đề bài:
 * - Kích thước n trong khoảng [0, 10000]
 * - Mảng phải được sắp xếp tăng không giảm: a[i] <= a[i+1]
 */
inline bool kiem_tra_hop_le_mang(const VectorInt& a, std::string& thong_bao_loi) {
    int n = static_cast<int>(a.size());
    if (n < 0 || n > 10000) {
        thong_bao_loi = "Loi: So luong phan tu n phai trong khoang [0, 10000]. Gia tri hien tai: " + std::to_string(n);
        return false;
    }
    for (int i = 0; i < n - 1; ++i) {
        if (a[i] > a[i + 1]) {
            thong_bao_loi = "Loi: Mang chua duoc sap xep tang khong giam tai vi tri " + 
                            std::to_string(i + 1) + " (a[" + std::to_string(i + 1) + "] = " + 
                            std::to_string(a[i]) + " > a[" + std::to_string(i + 2) + "] = " + 
                            std::to_string(a[i + 1]) + ").";
            return false;
        }
    }
    return true;
}

/**
 * Hàm 1: vi_tri_dau_ge(a, x, [trace])
 * Tìm vị trí đầu tiên trong mảng a có giá trị không nhỏ hơn x (a[i] >= x).
 * Quy ước:
 * - Chỉ số trả về là 1-based (1..n).
 * - Nếu không có phần tử nào >= x (mọi phần tử đều < x), quy ước trả về n + 1.
 * - Mảng rỗng (n = 0) trả về 1.
 *
 * Nguyên lý nhị phân:
 * - Khởi tạo left = 1, right = n, bien = n + 1.
 * - Khi left <= right:
 *     mid = left + (right - left) / 2
 *     Nếu a[mid - 1] >= x:
 *         bien = mid (ghi nhận ứng viên)
 *         right = mid - 1 (tiếp tục tìm về nửa trái xem có vị trí nào nhỏ hơn nữa không)
 *     Ngược lại (a[mid - 1] < x):
 *         left = mid + 1 (mọi phần tử từ left đến mid đều < x, loại bỏ nửa trái)
 */
inline int vi_tri_dau_ge(const VectorInt& a, int x, std::vector<BuocLanVet>* trace = nullptr, int* p_count = nullptr) {
    int n = static_cast<int>(a.size());
    int left = 1;
    int right = n;
    int bien = n + 1;
    int step = 0;

    while (left <= right) {
        step++;
        int mid = left + (right - left) / 2;
        int val = a[mid - 1]; // Chuyển sang 0-based để truy cập mảng C++
        bool ge = (val >= x);

        BuocLanVet b;
        b.buoc = step;
        b.left = left;
        b.right = right;
        b.mid = mid;
        b.gia_tri_mid = val;
        b.dieu_kien_ge = ge;

        if (ge) {
            bien = mid;
            b.bien_tam = bien;
            b.hanh_dong = "a[" + std::to_string(mid) + "] = " + std::to_string(val) + " >= " + std::to_string(x) + 
                          " -> Ghi nhan bien = " + std::to_string(bien) + ", thu hep sang trai [1, " + std::to_string(mid - 1) + "]";
            right = mid - 1;
        } else {
            b.bien_tam = bien;
            b.hanh_dong = "a[" + std::to_string(mid) + "] = " + std::to_string(val) + " < " + std::to_string(x) + 
                          " -> Thu hep sang phai [" + std::to_string(mid + 1) + ", " + std::to_string(right) + "]";
            left = mid + 1;
        }

        if (trace) {
            trace->push_back(b);
        }
    }

    if (p_count) {
        *p_count = step;
    }
    return bien;
}

/**
 * Hàm 2: dem_nho_hon(a, x, kiem_tra_mang)
 * Đếm số phần tử nhỏ hơn x bằng tìm kiếm nhị phân.
 * Định lý: Trong mảng đã sắp tăng không giảm, nếu ranh giới đầu tiên có a[i] >= x là vị trí 'bien'
 * (theo 1-based index), thì mọi phần tử từ vị trí 1 đến bien - 1 đều thỏa mãn a[i] < x.
 * Do đó số phần tử < x chính xác là bien - 1.
 *
 * Lưu ý phân tích độ phức tạp (Bảng 3.4):
 * - Pha kiểm tra tính hợp lệ mảng (kiem_tra_hop_le_mang): O(n) thời gian, O(1) không gian.
 * - Pha tìm kiếm nhị phân cốt lõi (vi_tri_dau_ge): O(log n) thời gian, O(1) không gian.
 * - Có thể bật/tắt kiem_tra_mang (mặc định = true để đảm bảo an toàn dữ liệu).
 */
inline KetQuaDem dem_nho_hon(const VectorInt& a, int x, bool kiem_tra_mang = true) {
    if (kiem_tra_mang) {
        std::string err;
        if (!kiem_tra_hop_le_mang(a, err)) {
            throw std::invalid_argument(err);
        }
    }

    std::vector<BuocLanVet> trace;
    int phep_so_sanh = 0;
    int bien = vi_tri_dau_ge(a, x, &trace, &phep_so_sanh);
    int so_nho_hon = bien - 1;

    return {bien, so_nho_hon, phep_so_sanh, trace};
}

/**
 * Hàm 3: dem_tuyen_tinh(a, x)
 * Thuật toán vét cạn / duyệt tuần tự O(n) dùng để đối chiếu độc lập và kiểm chứng tính đúng đắn.
 */
inline int dem_tuyen_tinh(const VectorInt& a, int x, int& so_so_sanh, int& bien_tuyen_tinh) {
    int n = static_cast<int>(a.size());
    so_so_sanh = 0;
    bien_tuyen_tinh = n + 1;

    for (int i = 0; i < n; ++i) {
        so_so_sanh++;
        if (a[i] >= x) {
            bien_tuyen_tinh = i + 1; // 1-based index
            return i;                // Số phần tử trước vị trí i chính là i
        }
    }
    return n; // Mọi phần tử đều < x
}

/**
 * Hàm 4: vi_tri_dau_gt(a, x) - Mở rộng Upper Bound
 * Tìm vị trí đầu tiên có a[i] > x (1-based).
 * Dùng để phân biệt bất đẳng thức nghiêm (< x) với không nghiêm (<= x).
 */
inline int vi_tri_dau_gt(const VectorInt& a, int x) {
    int n = static_cast<int>(a.size());
    int left = 1;
    int right = n;
    int bien = n + 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (a[mid - 1] > x) {
            bien = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return bien;
}

/**
 * Hàm 5: dem_mo_rong(a, x)
 * Trả về phân tích đa diện:
 * - Số phần tử < x
 * - Số phần tử <= x
 * - Số phần tử đúng bằng x
 */
inline KetQuaMoRong dem_mo_rong(const VectorInt& a, int x, bool kiem_tra_mang = true) {
    if (kiem_tra_mang) {
        std::string err;
        if (!kiem_tra_hop_le_mang(a, err)) {
            throw std::invalid_argument(err);
        }
    }
    int bien_ge = vi_tri_dau_ge(a, x);
    int so_nho_hon = bien_ge - 1;

    int bien_gt = vi_tri_dau_gt(a, x);
    int so_nho_hon_hoac_bang = bien_gt - 1;

    int so_bang = so_nho_hon_hoac_bang - so_nho_hon;
    return {bien_ge, so_nho_hon, bien_gt, so_nho_hon_hoac_bang, so_bang};
}

/**
 * Hàm 6: khao_sat_hieu_nang(n, x)
 * Tạo dữ liệu thực nghiệm theo quy mô n và so sánh số bước của Nhị phân vs Tuyến tính.
 */
struct KetQuaKhaoSat {
    int n;
    int x;
    int phep_so_sanh_bs;
    int phep_so_sanh_linear;
    double thoi_gian_bs_us;     // microseconds
    double thoi_gian_linear_us; // microseconds
};

inline KetQuaKhaoSat khao_sat_quy_mo(int n, int x) {
    VectorInt a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = i * 2; // Mảng tăng dần chẵn: 0, 2, 4, ...
    }

    // Đo tìm kiếm nhị phân
    auto t1 = std::chrono::high_resolution_clock::now();
    int count_bs = 0;
    vi_tri_dau_ge(a, x, nullptr, &count_bs);
    auto t2 = std::chrono::high_resolution_clock::now();
    double time_bs = std::chrono::duration<double, std::micro>(t2 - t1).count();

    // Đo tìm kiếm tuyến tính
    int count_linear = 0;
    int bien_linear = 0;
    auto t3 = std::chrono::high_resolution_clock::now();
    dem_tuyen_tinh(a, x, count_linear, bien_linear);
    auto t4 = std::chrono::high_resolution_clock::now();
    double time_linear = std::chrono::duration<double, std::micro>(t4 - t3).count();

    return {n, x, count_bs, count_linear, time_bs, time_linear};
}

} // namespace DT022
