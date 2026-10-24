from math import log2

DATA = [["đỏ", "nhỏ", "có"], ["đỏ", "lớn", "có"],
        ["xanh", "nhỏ", "không"], ["xanh", "lớn", "không"]]

def entropy(labels):
    if not labels:
        return 0.0
    counts = {}
    for x in labels:
        counts[x] = counts.get(x, 0) + 1
    result = 0.0
    for c in counts.values():
        p = c / len(labels)
        result += -p * log2(p)
    return result

def gain(rows, col):
    parent = entropy([r[-1] for r in rows])
    groups = {}
    for r in rows:
        groups.setdefault(r[col], []).append(r)
    for group in groups.values():
        parent -= len(group) / len(rows) * entropy([r[-1] for r in group])
    return parent

print(entropy(["có","không"]),entropy(["có","có"]))
print(gain(DATA, 0), gain(DATA, 1))
tot=max([0,1],key=lambda c:gain(DATA,c))
print("Chọn cột",tot,"=",["màu","cỡ"][tot])
