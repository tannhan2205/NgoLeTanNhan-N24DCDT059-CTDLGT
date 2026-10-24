function find_pair_with_sum(arr::Vector{Int}, S::Int)
    # Bước 1: Sắp xếp mảng tăng dần - O(n log n)
    arr_sorted = sort(arr)

    # Bước 2: Khởi tạo hai con trỏ (chỉ số trong Julia bắt đầu từ 1)
    left = 1
    right = length(arr_sorted)

    # Bước 3: Duyệt mảng bằng hai con trỏ - O(n)
    while left < right
        current_sum = arr_sorted[left] + arr_sorted[right]

        if current_sum == S
            return (arr_sorted[left], arr_sorted[right])
        elseif current_sum < S
            left += 1
        else
            right -= 1
        end
    end

    return nothing
end

# Ví dụ sử dụng:
arr = [8, 4, 1, 6, 9, 3, 5, 2]
S = 10
result = find_pair_with_sum(arr, S)

if result !== nothing
    println("Tim thay cap co tong bang $S: $(result[1]), $(result[2])")
else
    println("Khong tim thay cap co tong bang $S")
end