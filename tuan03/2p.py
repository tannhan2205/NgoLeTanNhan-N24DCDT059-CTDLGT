def find_pair_with_sum(arr, S):
    # Bước 1: Sắp xếp mảng tăng dần - O(n log n)
    arr_sorted = sorted(arr)

    # Bước 2: Khởi tạo hai con trỏ
    left = 0
    right = len(arr_sorted) - 1

    # Bước 3: Duyệt mảng bằng hai con trỏ - O(n)
    while left < right:
        current_sum = arr_sorted[left] + arr_sorted[right]

        if current_sum == S:
            return (arr_sorted[left], arr_sorted[right])
        elif current_sum < S:
            left += 1
        else:
            right -= 1

    return None

# Ví dụ sử dụng:
arr = [8, 4, 1, 6, 9, 3, 5, 2]
S = 10
result = find_pair_with_sum(arr, S)

if result:
    print(f"Tìm thấy cặp có tổng bằng {S}: {result}")
else:
    print(f"Không tìm thấy cặp có tổng bằng {S}")