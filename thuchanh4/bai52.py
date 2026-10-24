TREE = {"h": 0, "children": [
    {"h": 2, "children": [4, 7]},
    {"h": 5, "children": [1, 6]}
]}

def minimax_depth(node, depth, is_max):
    if isinstance(node, int):
        return node
    if depth == 0:
        return node["h"]
    best = -2e9 if is_max else 2e9
    for child in node["children"]:
        value = minimax_depth(child, depth - 1, not is_max)
        best = max(best, value) if is_max else min(best, value)
    return best

for depth in [1, 2]:
    print(depth, minimax_depth(TREE, depth, True))
