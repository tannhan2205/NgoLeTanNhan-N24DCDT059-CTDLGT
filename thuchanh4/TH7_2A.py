DATA = [["đỏ", "nhỏ", "có"], ["đỏ", "lớn", "có"],
        ["xanh", "nhỏ", "không"], ["xanh", "lớn", "không"]]

def gini(labels):
    if not labels:
        return 0.0
    counts = {}
    for x in labels:
        counts[x] = counts.get(x, 0) + 1
    total = 0.0
    for c in counts.values():
        total += (c / len(labels)) ** 2
    return 1.0 - total

def learn(rows, cols):
    labels = [r[-1] for r in rows]
    if len(set(labels)) == 1:
        return labels[0]
    if not cols:
        return max(sorted(set(labels)), key=labels.count)
    candidates = []
    for col in cols:
        groups = {}
        for r in rows:
            groups.setdefault(r[col], []).append(r)
        score = 0.0
        for group in groups.values():
            score += len(group) / len(rows) * gini([r[-1] for r in group])
        candidates.append((score, col, groups))
    _, col, groups = min(candidates, key=lambda x: (x[0], x[1]))
    rest = [c for c in cols if c != col]
    return (col, {v: learn(g, rest) for v, g in groups.items()})

def du_doan(cay, mau):
    while not isinstance(cay, str):
        col, nhanh = cay
        print("  hỏi cột", col, "->", mau[col])
        cay = nhanh[mau[col]]
    return cay

print(gini(["có","có","không","không"]), gini(["có","có"]))
cay = learn(DATA, [0, 1])
print(cay)
print(du_doan(cay, ["xanh", "lớn"]))
