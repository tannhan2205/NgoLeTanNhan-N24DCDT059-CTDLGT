#include <iostream>
#include <algorithm>

// Hàm hỗ trợ in mảng
void printArray(const int a[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
}

// 1. Sắp xếp đổi chỗ trực tiếp (Exchange Sort)
void exchangeSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[i]) {
                std::swap(a[i], a[j]);
            }
        }
    }
}

// 2. Sắp xếp lựa chọn trực tiếp (Selection Sort)
void selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(a[i], a[min_idx]);
        }
    }
}

// 3. Sắp xếp chèn trực tiếp (Insertion Sort)
void insertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int x = a[i];
        int pos = i - 1;
        while (pos >= 0 && a[pos] > x) {
            a[pos + 1] = a[pos];
            pos--;
        }
        a[pos + 1] = x;
    }
}

// 4. Sắp xếp nổi bọt có dừng sớm (Bubble Sort)
void bubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = n - 1; j > i; j--) {
            if (a[j] < a[j - 1]) {
                std::swap(a[j], a[j - 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // Dừng sớm nếu không có lượt tráo đổi nào
    }
}

int main() {
    const int n = 6;
    int original[] = {8, 3, 5, 1, 9, 2};

    std::cout << "Day ban dau: ";
    printArray(original, n);
    std::cout << "-----------------------------------\n";

    // Chạy thử Exchange Sort
    int a1[n];
    std::copy(original, original + n, a1);
    exchangeSort(a1, n);
    std::cout << "1. Exchange Sort:  ";
    printArray(a1, n);

    // Chạy thử Selection Sort
    int a2[n];
    std::copy(original, original + n, a2);
    selectionSort(a2, n);
    std::cout << "2. Selection Sort: ";
    printArray(a2, n);

    // Chạy thử Insertion Sort
    int a3[n];
    std::copy(original, original + n, a3);
    insertionSort(a3, n);
    std::cout << "3. Insertion Sort: ";
    printArray(a3, n);

    // Chạy thử Bubble Sort
    int a4[n];
    std::copy(original, original + n, a4);
    bubbleSort(a4, n);
    std::cout << "4. Bubble Sort:    ";
    printArray(a4, n);

    return 0;
}