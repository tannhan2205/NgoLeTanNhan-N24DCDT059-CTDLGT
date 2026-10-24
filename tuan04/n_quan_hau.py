def n_quan_hau():
    n = int(input("Nhập n: "))
    
    node_count = 0
    solution_count = 0
    first_solution = None
    
    X = [0] * (n + 1)
    col = [False] * (n + 1)
    diag1 = [False] * (2 * n + 1)  # Đường chéo xuôi: i - j + n
    diag2 = [False] * (2 * n + 1)  # Đường chéo ngược: i + j

    def backtrack(i):
        nonlocal node_count, solution_count, first_solution
        node_count += 1  # Đếm nút: mỗi lần gọi hàm đệ quy tính 1 nút
        
        for j in range(1, n + 1):
            if not col[j] and not diag1[i - j + n] and not diag2[i + j]:
                X[i] = j
                col[j] = diag1[i - j + n] = diag2[i + j] = True
                
                if i == n:
                    solution_count += 1
                    if first_solution is None:
                        first_solution = X[1:].copy()
                else:
                    backtrack(i + 1)
                    
                col[j] = diag1[i - j + n] = diag2[i + j] = False

    backtrack(1)
    print(f"Số nút đã duyệt: {node_count}")
    print(f"Số lời giải: {solution_count}")
    
    if first_solution:
        print("\nBàn cờ lời giải đầu tiên:")
        for row in range(n):
            line = ""
            for c in range(1, n + 1):
                if c == first_solution[row]:
                    line += "Q "
                else:
                    line += ". "
            print(line)
if __name__ == "__main__":
    n_quan_hau()