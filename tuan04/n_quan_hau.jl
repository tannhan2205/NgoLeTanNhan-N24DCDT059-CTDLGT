 function n_quan_hau()
    print("Nhập n: ")
    n = parse(Int, readline())

    node_count = 0
    solution_count = 0
    first_solution = Int[]

    X = zeros(Int, n)
    col = fill(false, n)
    diag1 = fill(false, 2 * n)  # Đường chéo xuôi: i - j + n
    diag2 = fill(false, 2 * n)  # Đường chéo ngược: i + j

    function backtrack(i)
        node_count += 1  # Mỗi lần gọi hàm đệ quy tính 1 nút

        for j in 1:n
            if !col[j] && !diag1[i - j + n] && !diag2[i + j]
                X[i] = j
                col[j] = diag1[i - j + n] = diag2[i + j] = true

                if i == n
                    solution_count += 1
                    if isempty(first_solution)
                        first_solution = copy(X)
                    end
                else
                    backtrack(i + 1)
                end

                col[j] = diag1[i - j + n] = diag2[i + j] = false
            end
        end
    end

    backtrack(1)

    println("Số nút đã duyệt: ", node_count)
    println("Số lời giải: ", solution_count)

    if !isempty(first_solution)
        println("\nBàn cờ lời giải đầu tiên:")
        for r in 1:n
            line = ""
            for c in 1:n
                if c == first_solution[r]
                    line *= "Q "
                else
                    line *= ". "
                end
            end
            println(line)
        end
    end
end
n_quan_hau()
