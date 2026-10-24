class TSPBranchAndBound:
    def __init__(self, matrix):
        self.matrix = matrix
        self.n = len(matrix)
        # Tìm giá trị c_min (cạnh nhỏ nhất không nằm trên đường chéo chính)
        self.c_min = min(matrix[i][j] for i in range(self.n) for j in range(self.n) if i != j)

    def solve(self, with_pruning=True):
        self.best_cost = float('inf')
        self.best_path = []
        self.node_count = 0

        visited = [False] * self.n
        visited[0] = True
        path = [0]

        self._dfs(0, 0, 1, path, visited, with_pruning)
        
        mode = "CÓ CẮT NHÁNH" if with_pruning else "KHÔNG CẮT NHÁNH"
        print(f"[{mode}]")
        print(f"Chi phí tối ưu: {self.best_cost}")
        print(f"Hành trình: {' -> '.join(map(str, self.best_path))}")
        print(f"Số nút đã duyệt: {self.node_count}\n")

    def _dfs(self, u, current_cost, level, path, visited, with_pruning):
        self.node_count += 1

        if level == self.n:
            total_cost = current_cost + self.matrix[u][0]
            if total_cost < self.best_cost:
                self.best_cost = total_cost
                self.best_path = path + [0]
            return

        for v in range(self.n):
            if not visited[v]:
                next_cost = current_cost + self.matrix[u][v]
                # Hàm cận dưới: chi phí hiện tại + (số cạnh còn lại) * c_min
                lb = next_cost + (self.n - level) * self.c_min

                if not with_pruning or lb < self.best_cost:
                    visited[v] = True
                    path.append(v)
                    self._dfs(v, next_cost, level + 1, path, visited, with_pruning)
                    path.pop()
                    visited[v] = False


# Ma trận chi phí 5x5 từ đề bài
cost_matrix = [
    [0, 10, 9, 22, 23],
    [10, 0, 16, 19, 14],
    [9, 16, 0, 7, 28],
    [22, 19, 7, 0, 8],
    [23, 14, 28, 8, 0]
]

solver = TSPBranchAndBound(cost_matrix)
print(f"Giá trị c_min tìm được: {solver.c_min}\n")

# Chạy chế độ CÓ cắt nhánh
solver.solve(with_pruning=True)

# Chạy chế độ KHÔNG cắt nhánh
solver.solve(with_pruning=False)