#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Hàm tìm cặp phần tử có tổng bằng S bằng kỹ thuật Hai con trỏ
bool findPairWithSum(vector<int>& arr, int S, pair<int, int>& result) {
    // Bước 1: Sắp xếp mảng tăng dần - O(n log n)
    sort(arr.begin(), arr.end());

    // Bước 2: Khởi tạo hai con trỏ
    int left = 0;
    int right = arr.size() - 1;

    // Bước 3: Duyệt mảng bằng hai con trỏ - O(n)
    while (left < right) {
        int current_sum = arr[left] + arr[right];

        if (current_sum == S) {
            result = {arr[left], arr[right]};
            return true; // Tìm thấy cặp hợp lệ
        } 
        else if (current_sum < S) {
            // Tổng nhỏ hơn S: loại bỏ arr[left] khỏi các ứng viên tiềm năng
            left++;
        } 
        else {
            // Tổng lớn hơn S: loại bỏ arr[right] khỏi các ứng viên tiềm năng
            right--;
        }
    }

    return false; // Không tìm thấy cặp nào có tổng bằng S
}

int main() {
    vector<int> arr = {8, 4, 1, 6, 9, 3, 5, 2};
    int S = 10;

    pair<int, int> result;
    if (findPairWithSum(arr, S, result)) {
        cout << "Tim thay cap co tong bang " << S << ": (" 
             << result.first << ", " << result.second << ")\n";
    } else {
        cout << "Khong tim thay cap co tong bang " << S << "\n";
    }

    return 0;
}