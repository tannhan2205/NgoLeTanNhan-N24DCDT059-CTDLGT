TREE = [[4, 7], [2, 9]]
DA_XET = []

def minimax(node, is_max=True):
    if isinstance(node, int): return node
    best = float("-inf") if is_max else float("inf")
    for child in node:
        value = minimax(child, not is_max)
        best = max(best, value) if is_max else min(best, value)
    return best

def alpha_beta(node, is_max=True,
               alpha=float("-inf"), beta=float("inf")):
    if isinstance(node, int):
        DA_XET.append(node)
        return node
    best = float("-inf") if is_max else float("inf")
    for child in node:
        value = alpha_beta(child, not is_max, alpha, beta)
        if is_max:
            best = max(best, value)
            alpha = max(alpha, best)
        else:
            best = min(best, value)
            beta = min(beta, best)
        if beta <= alpha:
            break
    return best

print(minimax(TREE), alpha_beta(TREE), "lá đã xét:", DA_XET)
for t in ([[1, 8], [5, 6]], [[3, 5], [2, 9], [0, 1]]):
    DA_XET.clear()
    print(t, minimax(t), alpha_beta(t), "lá đã xét:", DA_XET)
