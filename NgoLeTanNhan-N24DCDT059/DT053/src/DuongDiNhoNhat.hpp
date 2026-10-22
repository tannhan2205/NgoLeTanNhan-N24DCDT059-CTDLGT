#pragma once
/**
 * ĐỀ TÀI DT053: ĐƯỜNG ĐI CÓ TỔNG NHỎ NHẤT TRÊN LƯỚI
 * Học phần: Cấu trúc dữ liệu và giải thuật (INT13185) - Nhóm 03
 * Sinh viên thực hiện: Ngô Lê Tấn Nhân
 * MSSV: N24DCDT059
 * Lớp: D24CQDT01-N
 * Giảng viên hướng dẫn: ThS. Hồ Nhựt Minh
 */

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <string>

namespace DT053 {

// Định nghĩa kiểu dữ liệu cho tọa độ (1-indexed theo quy ước giáo trình: hàng, cột)
using ToaDo = std::pair<int, int>;
using MaTran = std::vector<std::vector<int>>;

/**
 * Cấu trúc chứa kết quả giải thuật:
 * - tong_chi_phi: Tổng chi phí nhỏ nhất từ (1, 1) đến (m, n)
 * - duong_di: Danh sách các tọa độ (1-indexed) từ (1, 1) đến (m, n)
 * - f: Bảng phương án quy hoạch động kích thước m x n
 */
struct KetQuaDuongDi {
    long long tong_chi_phi;
    std::vector<ToaDo> duong_di;
    std::vector<std::vector<long long>> f;
};

/**
 * Kiểm tra tính hợp lệ của ma trận đầu vào theo yêu cầu đề bài:
 * - Kích thước m, n từ 1 đến 10
 * - Giá trị mỗi ô là số nguyên từ 0 đến 99
 */
inline bool kiem_tra_hop_le_ma_tran(const MaTran& C, std::string& thong_bao_loi) {
    int m = C.size();
    if (m < 1 || m > 10) {
        thong_bao_loi = "Loi: So hang m phai trong khoang [1, 10]. Gia tri hien tai: " + std::to_string(m);
        return false;
    }
    int n = C[0].size();
    if (n < 1 || n > 10) {
        thong_bao_loi = "Loi: So cot n phai trong khoang [1, 10]. Gia tri hien tai: " + std::to_string(n);
        return false;
    }
    for (int i = 0; i < m; ++i) {
        if ((int)C[i].size() != n) {
            thong_bao_loi = "Loi: Cac hang khong dong deu so cot.";
            return false;
        }
        for (int j = 0; j < n; ++j) {
            if (C[i][j] < 0 || C[i][j] > 99) {
                thong_bao_loi = "Loi: Gia tri tai o (" + std::to_string(i + 1) + ", " + std::to_string(j + 1) + 
                                ") ngoai mien [0, 99]: " + std::to_string(C[i][j]);
                return false;
            }
        }
    }
    return true;
}

/**
 * Hàm 1: duong_di_nho_nhat(C)
 * Áp dụng quy hoạch động giải bài toán:
 * 1. Đặt f[i][j] là tổng nhỏ nhất từ ô đầu (1, 1) tới ô (i, j); gán f[0][0] = C[0][0].
 * 2. Điền hàng đầu bằng cộng từ trái, cột đầu bằng cộng từ trên.
 * 3. Với các ô còn lại, lấy nhỏ nhất của ô trên và ô trái rồi cộng chi phí ô hiện tại.
 */
inline std::vector<std::vector<long long>> tinh_bang_quy_hoach_dong(const MaTran& C) {
    int m = C.size();
    int n = C[0].size();
    std::vector<std::vector<long long>> f(m, std::vector<long long>(n, 0));

    // Bước 1: Khởi tạo ô xuất phát (1, 1) tương ứng chỉ số 0, 0
    f[0][0] = C[0][0];

    // Bước 2a: Điền hàng đầu bằng cộng dồn từ trái sang
    for (int j = 1; j < n; ++j) {
        f[0][j] = f[0][j - 1] + C[0][j];
    }

    // Bước 2b: Điền cột đầu bằng cộng dồn từ trên xuống
    for (int i = 1; i < m; ++i) {
        f[i][0] = f[i - 1][0] + C[i][0];
    }

    // Bước 3: Điền các ô còn lại f[i][j] = min(f[i-1][j], f[i][j-1]) + C[i][j]
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            f[i][j] = std::min(f[i - 1][j], f[i][j - 1]) + C[i][j];
        }
    }

    return f;
}

/**
 * Hàm 2: truy_vet_luoi(C, f)
 * Bước 4: Truy ngược từ ô đích (m, n) về (1, 1), sau đó đảo ngược để được đường từ đầu tới cuối.
 */
inline std::vector<ToaDo> truy_vet_luoi(const MaTran& C, const std::vector<std::vector<long long>>& f) {
    int m = C.size();
    int n = C[0].size();
    std::vector<ToaDo> duong;

    int i = m - 1;
    int j = n - 1;

    // Xuất phát từ ô đích
    duong.push_back({i + 1, j + 1});

    while (i > 0 || j > 0) {
        if (i == 0) {
            // Đang ở hàng đầu tiên -> chỉ có thể đi từ bên trái sang
            j--;
        } else if (j == 0) {
            // Đang ở cột đầu tiên -> chỉ có thể đi từ trên xuống
            i--;
        } else {
            // So sánh f[i-1][j] và f[i][j-1], đi từ ô có chi phí tích lũy nhỏ hơn
            if (f[i - 1][j] <= f[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
        duong.push_back({i + 1, j + 1});
    }

    // Đảo ngược đường đi để có thứ tự từ (1, 1) tới (m, n)
    std::reverse(duong.begin(), duong.end());
    return duong;
}

/**
 * Hàm 3: kiem_tra_duong(C, duong)
 * Bước 5: Kiểm tra tính hợp lệ của đường đi:
 * - Bắt đầu tại (1, 1) và kết thúc tại (m, n)
 * - Mọi bước chuyển chỉ là sang phải hoặc xuống dưới
 * - Tính lại tổng chi phí trên đường đi và đối chiếu với chi phí tối ưu f[m-1][n-1]
 */
inline bool kiem_tra_duong(const MaTran& C, const std::vector<ToaDo>& duong, long long tong_ky_vong) {
    int m = C.size();
    int n = C[0].size();

    if (duong.empty()) return false;
    if (duong.front() != ToaDo(1, 1)) return false;
    if (duong.back() != ToaDo(m, n)) return false;

    long long tong_thuc_te = C[0][0];

    for (size_t k = 1; k < duong.size(); ++k) {
        int r_prev = duong[k - 1].first;
        int c_prev = duong[k - 1].second;
        int r_curr = duong[k].first;
        int c_curr = duong[k].second;

        bool sang_phai = (r_curr == r_prev && c_curr == c_prev + 1);
        bool xuong_duoi = (r_curr == r_prev + 1 && c_curr == c_prev);

        // Chỉ chấp nhận 2 bước đi: sang phải hoặc xuống dưới
        if (!sang_phai && !xuong_duoi) {
            return false;
        }

        tong_thuc_te += C[r_curr - 1][c_curr - 1];
    }

    return (tong_thuc_te == tong_ky_vong);
}

/**
 * Hàm giải bài toán hoàn chỉnh: duong_di_nho_nhat(C)
 */
inline KetQuaDuongDi duong_di_nho_nhat(const MaTran& C) {
    std::string err;
    if (!kiem_tra_hop_le_ma_tran(C, err)) {
        throw std::invalid_argument(err);
    }
    auto f = tinh_bang_quy_hoach_dong(C);
    int m = C.size();
    int n = C[0].size();
    long long tong = f[m - 1][n - 1];
    auto duong = truy_vet_luoi(C, f);

    if (!kiem_tra_duong(C, duong, tong)) {
        throw std::runtime_error("Loi: Duong di truy vet khong khop voi tong chi phi toi uu!");
    }

    return {tong, duong, f};
}

/**
 * Yêu cầu mở rộng (Tùy chọn): Tối ưu bộ nhớ O(N) chỉ bằng 1 hàng
 * Giúp tiết kiệm bộ nhớ từ O(M*N) xuống O(min(M, N)) khi chỉ cần tính tổng chi phí nhỏ nhất.
 */
inline long long tinh_tong_nho_nhat_toi_uu_bo_nho(const MaTran& C) {
    std::string err;
    if (!kiem_tra_hop_le_ma_tran(C, err)) {
        throw std::invalid_argument(err);
    }
    int m = C.size();
    int n = C[0].size();
    std::vector<long long> dp(n, 0);

    dp[0] = C[0][0];
    for (int j = 1; j < n; ++j) {
        dp[j] = dp[j - 1] + C[0][j];
    }

    for (int i = 1; i < m; ++i) {
        dp[0] += C[i][0];
        for (int j = 1; j < n; ++j) {
            dp[j] = std::min(dp[j], dp[j - 1]) + C[i][j];
        }
    }

    return dp[n - 1];
}

} // namespace DT053
