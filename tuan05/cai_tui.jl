
function knapsack_01()
    items = ["A", "B", "C", "D", "E"]
    w = [2, 3, 4, 5, 7]
    v = [3, 7, 9, 12, 16]
    W = 11
    n = length(items)

    # Khởi tạo bảng f kích thước (n+1) x (W+1) với các giá trị 0
    f = zeros(Int, n + 1, W + 1)

    # Điền bảng quy hoạch động
    for i in 1:n
        for j in 1:W
            if w[i] > j
                f[i + 1, j + 1] = f[i, j + 1]
            else
                f[i + 1, j + 1] = max(f[i, j + 1], f[i, j - w[i] + 1] + v[i])
            end
        end
    end

    # 1. In toàn bộ bảng f (72 ô kể cả hàng 0 và cột 0)
    println("=== BẢNG f QUY HOẠCH ĐỘNG (6 HÀNG x 12 CỘT) ===")
    print(rpad("f[i][j]", 10))
    for j in 0:W
        print(rpad(j, 4))
    end
    println("\n" * "-"^58)

    for i in 0:n
        label = (i == 0) ? "i=0" : "i=$i ($(items[i]))"
        print(rpad(label, 10))
        for j in 0:W
            print(rpad(f[i + 1, j + 1], 4))
        end
        println()
    end

    # 2. Truy vết từ f[n+1, W+1] tương ứng f[5][11] ngược lên f[1, .]
    selected_items = String[]
    i, j = n, W
    while i > 0 && j > 0
        if f[i + 1, j + 1] != f[i, j + 1]
            push!(selected_items, items[i])
            j -= w[i]
        end
        i -= 1
    end
    reverse!(selected_items)

    # 3. In kết quả cuối cùng
    println("\nGiá trị lớn nhất f[5][11]: ", f[n + 1, W + 1])
    println("Tập đồ vật được chọn: ", selected_items)
end

knapsack_01()