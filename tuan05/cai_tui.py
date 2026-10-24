def knapsack_01():
    items = ["A", "B", "C", "D", "E"]
    w = [2, 3, 4, 5, 7]
    v = [3, 7, 9, 12, 16]
    W = 11
    n = len(items)

    # Khởi tạo bảng f kích thước (n+1) x (W+1) bằng các giá trị 0
    f = [[0] * (W + 1) for _ in range(n + 1)]

    # Điền bảng quy hoạch động
    for i in range(1, n + 1):
        for j in range(1, W + 1):
            if w[i - 1] > j:
                f[i][j] = f[i - 1][j]
            else:
                f[i][j] = max(f[i - 1][j], f[i - 1][j - w[i - 1]] + v[i - 1])

    # 1. In toàn bộ bảng f (72 ô kể cả hàng 0 và cột 0)
    print("=== BẢNG f QUY HOẠCH ĐỘNG (6 HÀNG x 12 CỘT) ===")
    header = f"{'f[i][j]':<10}" + "".join(f"{j:<4}" for j in range(W + 1))
    print(header)
    print("-" * len(header))
    for i in range(n + 1):
        row_label = "i=0" if i == 0 else f"i={i} ({items[i-1]})"
        row_str = "".join(f"{f[i][j]:<4}" for j in range(W + 1))
        print(f"{row_label:<10}{row_str}")

    # 2. Truy vết từ ô f[n][W] ngược lên f[0][.]
    selected_items = []
    i, j = n, W
    while i > 0 and j > 0:
        if f[i][j] != f[i - 1][j]:
            selected_items.append(items[i - 1])
            j -= w[i - 1]
        i -= 1
    selected_items.reverse()

    # 3. In kết quả cuối cùng
    print("\nGiá trị lớn nhất f[5][11]:", f[n][W])
    print("Tập đồ vật được chọn:", selected_items)

knapsack_01()