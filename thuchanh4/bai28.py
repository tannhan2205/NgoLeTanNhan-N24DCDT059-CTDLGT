def minimax(tree, is_max):
    if isinstance(tree, (int, float)):
        return tree
    values = [minimax(child, not is_max) for child in tree]
    return max(values) if is_max else min(values)

def alpha_beta(tree, is_max, alpha, beta, visited, path='A'):
    if isinstance(tree, (int, float)):
        visited.append((path, tree))
        return tree
    best = -float('inf') if is_max else float('inf')
    for k, child in enumerate(tree):
        child_path = path + '.' + str(k + 1)
        value = alpha_beta(child, not is_max, alpha, beta, visited, child_path)
        if is_max:
            best = max(best, value)
            alpha = max(alpha, best)
        else:
            best = min(best, value)
            beta = min(beta, best)
        if beta <= alpha:
            break
    return best

tree = [[3, 12, 8], [2, 4, 6], [14, 5, 2]]
visited = []
print('Minimax:', minimax(tree, True))
print('Alpha-beta:', alpha_beta(tree, True, -float('inf'), float('inf'), visited))
print('Lá đã xét:', visited, len(visited))
v=[]; print(alpha_beta(3,True,-float('inf'),float('inf'),v), v)
v=[]; print(alpha_beta([[3,12],[2,4]],True,-float('inf'),float('inf'),v), v)
