def insertion_sort(A):
    n = len(A)
    # Duyệt từ phần tử thứ 2 (chỉ số 1) đến cuối mảng
    for i in range(1, n):
        key = A[i]
        j = i - 1    
        # Dời các phần tử trong đoạn A[0..i-1] lớn hơn key sang phải 1 vị trí
        while j >= 0 and A[j] > key:
            A[j + 1] = A[j]
            j -= 1           
        # Đặt key vào vị trí thích hợp
        A[j + 1] = key
    return A
# Dãy thực nghiệm theo đề bài
A = [8, 3, 5, 1, 9, 2]
print("Dãy ban đầu:", A)
insertion_sort(A)
print("Dãy sau khi sắp xếp chèn:", A)