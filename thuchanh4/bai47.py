DATA = [[1, "không"], [2, "không"], [4, "có"], [7, "có"]]

def gini(labels):
    if not labels:
        return 0.0
    return 1 - sum((labels.count(x)/len(labels))**2
                   for x in set(labels))

def best_threshold(rows):
    values = sorted({r[0] for r in rows})
    if len(values) < 2:
        raise ValueError("Không có ngưỡng")
    best_t, best_score = None, float("inf")
    for a, b in zip(values, values[1:]):
        t = (a+b)/2
        left = [r[-1] for r in rows if r[0] <= t]
        right = [r[-1] for r in rows if r[0] > t]
        score = (len(left)*gini(left) + len(right)*gini(right)) / len(rows)
        if score < best_score:
            best_t, best_score = t, score
    return best_t, best_score

print(best_threshold(DATA))
try:
    best_threshold([[2,"có"],[2,"không"]])
except ValueError as e:
    print("Lỗi:", e)
