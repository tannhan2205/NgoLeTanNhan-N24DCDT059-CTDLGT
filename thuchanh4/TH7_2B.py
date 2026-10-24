LINES = [(0,1,2),(3,4,5),(6,7,8),(0,3,6),
         (1,4,7),(2,5,8),(0,4,8),(2,4,6)]
BOARD = list("XOXXO O X")  # O đi, trống ở 5 và 7.

def terminal(b):
    for p in ("X", "O"):
        if any(all(b[i] == p for i in line) for line in LINES):
            return 1 if p == "X" else -1
    return 0 if " " not in b else None

def minimax(b, turn):
    end = terminal(b)
    if end is not None: return end
    best = -2 if turn == "X" else 2
    for i in range(9):
        if b[i] == " ":
            child = b.copy(); child[i] = turn
            value = minimax(child, "O" if turn == "X" else "X")
            best = max(best, value) if turn == "X" else min(best, value)
    return best

def alpha_beta(b, turn, alpha=-2, beta=2):
    end = terminal(b)
    if end is not None: return end
    best = -2 if turn == "X" else 2
    for i in range(9):
        if b[i] == " ":
            child = b.copy(); child[i] = turn
            value = alpha_beta(child, "O" if turn == "X" else "X",
                               alpha, beta)
            if turn == "X":
                best = max(best, value)
                alpha = max(alpha, best)
            else:
                best = min(best, value)
                beta = min(beta, best)
            if beta <= alpha:
                break
    return best

print(minimax(BOARD, "O"), alpha_beta(BOARD, "O"))
for i in (5, 7):
    b = BOARD.copy(); b[i] = "O"
    print("O đi ô", i, "->", minimax(b, "X"), alpha_beta(b, "X"))
