#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

struct InsertionResult {
    std::vector<int> sorted;
    long long cmps;
    long long shifts;
};

struct MergeResult {
    std::vector<int> sorted;
    long long cmps;
};

// --- 1. THUẬT TOÁN INSERTION SORT ---
InsertionResult insertion_sort(const std::vector<int>& arr) {
    std::vector<int> a = arr; // Tạo bản sao độc lập
    int n = a.size();
    long long cmps = 0;
    long long shifts = 0;

    for (int i = 1; i < n; ++i) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0) {
            cmps++; // Đếm lần so sánh A[j] với key
            if (a[j] > key) {
                a[j + 1] = a[j]; // Dịch phần tử sang phải
                shifts++;
                j--;
            } else {
                break; // Dừng khi so sánh trả về false
            }
        }
        a[j + 1] = key;
    }

    return {a, cmps, shifts};
}

// --- 2. HÀM TRỘN (MERGE) TÁCH RIÊNG ---
MergeResult merge(const std::vector<int>& left, const std::vector<int>& right) {
    std::vector<int> merged;
    merged.reserve(left.size() + right.size());
    long long cmps = 0;
    size_t i = 0, j = 0;

    // Chỉ đếm so sánh khi cả hai nửa đều còn phần tử
    while (i < left.size() && j < right.size()) {
        cmps++;
        if (left[i] <= right[j]) {
            merged.push_back(left[i]);
            i++;
        } else {
            merged.push_back(right[j]);
            j++;
        }
    }

    // Chép phần dư (không đếm so sánh)
    while (i < left.size()) {
        merged.push_back(left[i]);
        i++;
    }
    while (j < right.size()) {
        merged.push_back(right[j]);
        j++;
    }

    return {merged, cmps};
}

// --- 3. THUẬT TOÁN MERGE SORT ---
MergeResult merge_sort(const std::vector<int>& arr) {
    if (arr.size() <= 1) {
        return {arr, 0};
    }

    int mid = arr.size() / 2;
    std::vector<int> left_half(arr.begin(), arr.begin() + mid);
    std::vector<int> right_half(arr.begin() + mid, arr.end());

    MergeResult left_res = merge_sort(left_half);
    MergeResult right_res = merge_sort(right_half);

    // Gọi hàm merge để trộn 2 nửa
    MergeResult merged_res = merge(left_res.sorted, right_res.sorted);

    long long total_cmps = left_res.cmps + right_res.cmps + merged_res.cmps;
    return {merged_res.sorted, total_cmps};
}

void print_vec(const std::vector<int>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << (i + 1 < vec.size() ? ", " : "");
    }
    std::cout << "]";
}

int main() {
    std::vector<std::vector<int>> test_cases = {
        {},
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        {2, 2, 2, 2},
        {38, 27, 43, 3, 9, 82, 10}
    };

    std::cout << std::left 
              << std::setw(25) << "Dãy đầu vào" << " | "
              << std::setw(9)  << "INS CMPS"    << " | "
              << std::setw(10) << "INS SHIFTS"  << " | "
              << std::setw(10) << "MERGE CMPS"  << " | Kết quả\n";
    std::cout << std::string(80, '-') << "\n";

    for (const auto& tc : test_cases) {
        InsertionResult ins = insertion_sort(tc);
        MergeResult mrg = merge_sort(tc);

        std::cout << std::left << std::setw(25);
        print_vec(tc);
        std::cout << " | " << std::setw(9) << ins.cmps
                  << " | " << std::setw(10) << ins.shifts
                  << " | " << std::setw(10) << mrg.cmps
                  << " | ";
        print_vec(ins.sorted);
        std::cout << "\n";
    }

    return 0;
}