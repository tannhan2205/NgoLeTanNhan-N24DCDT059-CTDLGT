def gini_counts(counts):
    if any((not isinstance(c, int)) or c < 0 for c in counts):
        raise ValueError('Số đếm phải là số nguyên không âm')
    n = sum(counts)
    if n == 0:
        return 0.0
    s = 0.0
    for c in counts:
        p = c / n
        s += p*p
    return 1 - s

for counts in [[5, 0], [3, 3], [4, 1]]:
    print(counts, gini_counts(counts))
print(gini_counts([10,2]) , gini_counts([5,1]))
