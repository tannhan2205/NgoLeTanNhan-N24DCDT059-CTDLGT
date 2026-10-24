# --- 1. THUẬT TOÁN INSERTION SORT ---
function insertion_sort(arr::Vector{Int})
    a = copy(arr) # Tạo bản sao độc lập (tránh chỉ số index 0 trong Julia)
    n = length(a)
    insert_cmps = 0
    insert_shifts = 0

    for i in 2:n
        key = a[i]
        j = i - 1
        while j >= 1
            insert_cmps += 1 # Đếm phép so sánh A[j] với key
            if a[j] > key
                a[j + 1] = a[j] # Dịch phần tử sang phải
                insert_shifts += 1
                j -= 1
            else
                break # Dừng khi so sánh trả về false
            end
        end
        a[j + 1] = key
    end

    return a, insert_cmps, insert_shifts
end

# --- 2. HÀM TRỘN (MERGE) TÁCH RIÊNG ---
function merge_arrays(left::Vector{Int}, right::Vector{Int})
    i = 1
    j = 1
    merged = Int[]
    cmps = 0

    # Chỉ đếm so sánh khi cả hai nửa đều còn phần tử
    while i <= length(left) && j <= length(right)
        cmps += 1
        if left[i] <= right[j]
            push!(merged, left[i])
            i += 1
        else
            push!(merged, right[j])
            j += 1
        end
    end

    # Chép phần dư còn lại (không đếm so sánh)
    while i <= length(left)
        push!(merged, left[i])
        i += 1
    end

    while j <= length(right)
        push!(merged, right[j])
        j += 1
    end

    return merged, cmps
end

# --- 3. THUẬT TOÁN MERGE SORT ---
function merge_sort(arr::Vector{Int})
    a = copy(arr)
    n = length(a)
    if n <= 1
        return a, 0
    end

    mid = div(n, 2)
    left_sorted, cmps_l = merge_sort(a[1:mid])
    right_sorted, cmps_r = merge_sort(a[mid+1:end])

    # Gọi hàm merge_arrays để trộn 2 nửa
    merged, cmps_m = merge_arrays(left_sorted, right_sorted)

    total_cmps = cmps_l + cmps_r + cmps_m
    return merged, total_cmps
end

# ================= SỐ LIỆU KIỂM THỬ =================
test_cases = [
    Int[],
    [1, 2, 3, 4, 5],
    [5, 4, 3, 2, 1],
    [2, 2, 2, 2],
    [38, 27, 43, 3, 9, 82, 10]
]

println(rpad("Dãy đầu vào", 25), " | ", rpad("INS CMPS", 9), " | ", rpad("INS SHIFTS", 10), " | ", rpad("MERGE CMPS", 10), " | Kết quả")
println("-"^80)

for tc in test_cases
    res_ins, ins_c, ins_s = insertion_sort(tc)
    res_mrg, mrg_c = merge_sort(tc)
    println(rpad(string(tc), 25), " | ", rpad(ins_c, 9), " | ", rpad(ins_s, 10), " | ", rpad(mrg_c, 10), " | ", res_ins)
end