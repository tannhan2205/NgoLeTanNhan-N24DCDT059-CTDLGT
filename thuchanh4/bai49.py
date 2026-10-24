DATA = [["đỏ", "có"], ["đỏ", "có"],
        ["xanh", "không"], ["đỏ", "không"]]
BOOT = [[0, 1, 2, 2], [0, 0, 1, 2], [3, 3, 2, 0]]

def majority(labels):
    return max(sorted(set(labels)), key=labels.count)

def learn_stump(rows):
    groups = {}
    for color, label in rows:
        groups.setdefault(color, []).append(label)
    tree = {}
    for color, labels in groups.items():
        tree[color] = majority(labels)
    return tree

def vote(trees, color):
    counts = {}
    for tree in trees:
        label = tree[color]
        counts[label] = counts.get(label, 0) + 1
    return max(sorted(counts), key=counts.get)

trees = [learn_stump([DATA[i] for i in ids]) for ids in BOOT]
print([t["đỏ"] for t in trees])
print(vote(trees, "đỏ"))
print([t["xanh"] for t in trees], vote(trees, "xanh"))
