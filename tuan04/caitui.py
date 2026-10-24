class Item:
    def __init__(self, name, w, v):
        self.name = name
        self.w = w
        self.v = v
        self.ratio = v / w

def fractional_knapsack_ub(items, idx, current_w, current_v, W):
    if current_w > W:
        return 0
    ub = float(current_v)
    rem_w = W - current_w
    for j in range(idx, len(items)):
        if items[j].w <= rem_w:
            rem_w -= items[j].w
            ub += items[j].v
        else:
            ub += rem_w * items[j].ratio
            break
    return ub

def solve_knapsack(items, W, with_pruning=True):
    best_val = 0
    best_set = []
    node_count = 0

    def dfs(idx, current_w, current_v, current_set):
        nonlocal best_val, best_set, node_count
        node_count += 1

        if current_w > W:
            return

        if current_v > best_val:
            best_val = current_v
            best_set = list(current_set)

        if idx == len(items):
            return

        if with_pruning:
            ub = fractional_knapsack_ub(items, idx, current_w, current_v, W)
            if ub <= best_val:
                return

        # Nhánh 1: Lấy đồ vật idx
        dfs(idx + 1, current_w + items[idx].w, current_v + items[idx].v, current_set + [items[idx].name])
        # Nhánh 2: Không lấy đồ vật idx
        dfs(idx + 1, current_w, current_v, current_set)

    dfs(0, 0, 0, [])
    return best_val, best_set, node_count

# Dữ liệu
raw_items = [
    Item('A', 4, 19), Item('B', 7, 25), Item('C', 3, 7),
    Item('D', 3, 8), Item('E', 3, 9), Item('F', 10, 21)
]
W = 14

# Sắp xếp v/w giảm dần
items = sorted(raw_items, key=lambda x: x.ratio, reverse=True)

val_p, set_p, nodes_p = solve_knapsack(items, W, with_pruning=True)
_, _, nodes_np = solve_knapsack(items, W, with_pruning=False)

print(f"Thu tu xet: {[i.name for i in items]}")
print(f"Gia tri lon nhat: {val_p}, Tap chon: {set_p}")
print(f"So nut CÓ cat nhanh: {nodes_p}")
print(f"So nut KHONG cat nhanh: {nodes_np}")