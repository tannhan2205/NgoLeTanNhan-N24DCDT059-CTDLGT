# Bai 4.2 - Chon hoat dong: bon tieu chi tren cung mot bo du lieu
activities = [
    ("H1", 1, 5),
    ("H2", 2, 5),
    ("H3", 2, 6),
    ("H4", 3, 4),
    ("H5", 4, 8),
    ("H6", 6, 9),
    ("H7", 8, 11),
    ("H8", 9, 14),
    ("H9", 11, 13),
    ("H10", 12, 15),
]

def compatible(a, b):
    _, s1, f1 = a
    _, s2, f2 = b
    return s2 >= f1 or s1 >= f2

def compatible_with_all(act, chosen):
    return all(compatible(act, c) for c in chosen)

def greedy(order):
    chosen = []
    for act in order:
        if compatible_with_all(act, chosen):
            chosen.append(act)
    return chosen

def show(name, chosen):
    names = [a[0] for a in chosen]
    print(f"{name:22s} -> {len(chosen):2d} hoat dong: {', '.join(names)}")

# Tieu chi 1: Ket thuc som nhat
order1 = sorted(activities, key=lambda a: a[2])
r1 = greedy(order1)

# Tieu chi 2: Bat dau som nhat
order2 = sorted(activities, key=lambda a: a[1])
r2 = greedy(order2)

# Tieu chi 3: Ngan nhat (thoi luong nho nhat)
order3 = sorted(activities, key=lambda a: a[2] - a[1])
r3 = greedy(order3)

# Tieu chi 4: Chong lan voi it hoat dong khac nhat
conflict_count = {}
for a in activities:
    cnt = sum(1 for b in activities if b[0] != a[0] and not compatible(a, b))
    conflict_count[a[0]] = cnt
order4 = sorted(activities, key=lambda a: conflict_count[a[0]])
r4 = greedy(order4)

print("=== Bon tieu chi tham lam ===")
show("1. Ket thuc som nhat", r1)
show("2. Bat dau som nhat", r2)
show("3. Ngan nhat", r3)
show("4. It chong lan nhat", r4)

# Chuong trinh tim so hoat dong nhieu nhat that su (vet can toan bo tap con)
n = len(activities)
best = []
for mask in range(1 << n):
    subset = [activities[i] for i in range(n) if (mask >> i) & 1]
    ok = True
    for i in range(len(subset)):
        for j in range(i + 1, len(subset)):
            if not compatible(subset[i], subset[j]):
                ok = False
                break
        if not ok:
            break
    if ok and len(subset) > len(best):
        best = subset

print("\n=== Ket qua toi uu that su (vet can) ===")
show("Toi uu (brute force)", best)