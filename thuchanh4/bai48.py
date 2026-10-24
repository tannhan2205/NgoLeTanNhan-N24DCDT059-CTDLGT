DATA = [["đỏ", "có"], ["đỏ", "có"],
        ["xanh", "không"], ["xanh", "không"]]

def majority(labels):  # Hỗ trợ: hòa chọn nhãn theo từ điển.
    return max(sorted(set(labels)), key=labels.count)

def learn(rows, max_height, level=1):
    labels = [r[-1] for r in rows]
    if len(set(labels)) == 1:
        return labels[0]
    if level >= max_height:
        return majority(labels)
    groups = {}
    for r in rows:
        groups.setdefault(r[0], []).append(r)
    children = {}
    for value, group in groups.items():
        children[value] = learn(group, max_height, level+1)
    return (0, children)

print("Cao 1:", learn(DATA, 1))
print("Cao 2:", learn(DATA, 2))
print("Cao 5:", learn(DATA, 5))
