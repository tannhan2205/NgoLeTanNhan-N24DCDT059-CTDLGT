# --- 1. THUẬT TOÁN INSERTION SORT ---
def insertion_sort(arr):
    a = arr.copy()  # Tạo bản sao độc lập
    n = len(a)
    insert_cmps = 0
    insert_shifts = 0

    for i in range(1, n):
        key = a[i]
        j = i - 1
        while j >= 0:
            insert_cmps += 1  # Đếm mỗi lần so sánh A[j] với key
            if a[j] > key:
                a[j + 1] = a[j]  # Dịch phần tử sang phải
                insert_shifts += 1
                j -= 1
            else:
                break  # Dừng khi so sánh trả về False
        a[j + 1] = key

    return a, insert_cmps, insert_shifts


# --- 2. HÀM TRỘN (MERGE) TÁCH RIÊNG ---
def merge(left, right):
    i = j = 0
    merged = []
    cmps = 0

    # Chỉ đếm so sánh khi cả hai nửa đều còn phần tử
    while i < len(left) and j < len(right):
        cmps += 1
        if left[i] <= right[j]:
            merged.append(left[i])
            i += 1
        else:
            merged.append(right[j])
            j += 1

    # Chép phần dư còn lại (không đếm so sánh)
    merged.extend(left[i:])
    merged.extend(right[j:])

    return merged, cmps


# --- 3. THUẬT TOÁN MERGE SORT ---
def merge_sort(arr):
    a = arr.copy()  # Tạo bản sao độc lập
    if len(a) <= 1:
        return a, 0

    mid = len(a) // 2
    left, cmps_l = merge_sort(a[:mid])
    right, cmps_r = merge_sort(a[mid:])

    # Gọi hàm merge để trộn 2 nửa
    merged, cmps_m = merge(left, right)

    # Tổng số phép so sánh = số phép so sánh 2 nửa con + số phép so sánh khi trộn
    total_cmps = cmps_l + cmps_r + cmps_m
    return merged, total_cmps


# ================= SỐ LIỆU KIỂM THỬ =================
if __name__ == "__main__":
    test_cases = [
        [],
        [1, 2, 3, 4, 5],
        [5, 4, 3, 2, 1],
        [2, 2, 2, 2],
        [38, 27, 43, 3, 9, 82, 10]
    ]

    print(f"{'Dãy đầu vào':<25} | {'INS CMPS':<9} | {'INS SHIFTS':<10} | {'MERGE CMPS':<10} | {'Kết quả'}")
    print("-" * 80)

    for tc in test_cases:
        res_ins, ins_c, ins_s = insertion_sort(tc)
        res_mrg, mrg_c = merge_sort(tc)
        print(f"{str(tc):<25} | {ins_c:<9} | {ins_s:<10} | {mrg_c:<10} | {res_ins}")