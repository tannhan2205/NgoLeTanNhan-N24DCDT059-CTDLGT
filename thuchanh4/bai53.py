GRAPH = {"A": ["B", "C"], "B": ["D", "E"],
         "C": ["D", "F"], "D": 5, "E": 3, "F": 7}

def solve(name, is_max, memo, stats):
    key = (name, is_max)
    if key in memo:
        stats["hit"] += 1
        return memo[key]
    stats["computed"] += 1
    node = GRAPH[name]
    if isinstance(node, int):
        memo[key] = node
        return node
    best = -2e9 if is_max else 2e9
    for child in node:
        value = solve(child, not is_max, memo, stats)
        best = max(best, value) if is_max else min(best, value)
    memo[key] = best
    return best

memo, stats = {}, {"computed": 0, "hit": 0}
print(solve("A", True, memo, stats), stats)
print(solve("A", True, memo, stats), stats)
