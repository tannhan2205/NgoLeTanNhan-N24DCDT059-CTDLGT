#include <iostream>
using namespace std;
// Hàm sắp xếp chèn
void insertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];  // Lưu giá trị phần tử cần chèn
        int j = i - 1;   // Đặt vị trí xét từ phần tử ngay bên trái
        // Dời các phần tử lớn hơn key sang phải 1 ô
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        // Chèn key vào vị trí trống phù hợp
        a[j + 1] = key;
    }
}
int main() {
    int a[] = {8, 3, 5, 1, 9, 2};
    int n = 6; 
    insertionSort(a, n);
    // In mảng kết quả
    cout << "Day sau khi sap xep: ";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    return 0;
}
