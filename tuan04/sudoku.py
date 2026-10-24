import copy
import time

# De bai Sudoku 9x9 (0 dai dien cho o trong)
board_initial = [
    [0, 0, 0, 0, 0, 6, 0, 0, 0],
    [0, 8, 1, 0, 5, 0, 4, 0, 0],
    [0, 0, 9, 0, 0, 7, 0, 5, 8],
    [0, 0, 0, 0, 9, 0, 0, 0, 0],
    [0, 0, 6, 0, 0, 1, 0, 0, 7],
    [7, 4, 0, 0, 0, 0, 2, 0, 1],
    [0, 0, 0, 1, 3, 0, 0, 0, 4],
    [0, 0, 0, 0, 2, 9, 0, 0, 0],
    [9, 0, 0, 0, 0, 8, 0, 6, 0],
]


def is_valid(board, r, c, val):
  for i in range(9):
    if board[r][i] == val or board[i][c] == val:
      return False
  br, bc = 3 * (r // 3), 3 * (c // 3)
  for i in range(br, br + 3):
    for j in range(bc, bc + 3):
      if board[i][j] == val:
        return False
  return True


def get_candidates(board, r, c):
  used = set()
  for i in range(9):
    if board[r][i] != 0:
      used.add(board[r][i])
    if board[i][c] != 0:
      used.add(board[i][c])
  br, bc = 3 * (r // 3), 3 * (c // 3)
  for i in range(br, br + 3):
    for j in range(bc, bc + 3):
      if board[i][j] != 0:
        used.add(board[i][j])
  return [val for val in range(1, 10) if val not in used]


# --- 1. QUET TUAN TU ---
calls_seq = 0


def solve_sequential(board):
  global calls_seq
  calls_seq += 1

  empty = None
  for r in range(9):
    for c in range(9):
      if board[r][c] == 0:
        empty = (r, c)
        break
    if empty:
      break

  if not empty:
    return True

  r, c = empty
  for val in range(1, 10):
    if is_valid(board, r, c, val):
      board[r][c] = val
      if solve_sequential(board):
        return True
      board[r][c] = 0
  return False


# --- 2. HEURISTIC MRV ---
calls_mrv = 0


def solve_mrv(board):
  global calls_mrv
  calls_mrv += 1

  min_cands = 10
  best_cell = None
  best_candidates = []

  for r in range(9):
    for c in range(9):
      if board[r][c] == 0:
        cands = get_candidates(board, r, c)
        if len(cands) < min_cands:
          min_cands = len(cands)
          best_cell = (r, c)
          best_candidates = cands
          if min_cands == 0:
            return False

  if best_cell is None:
    return True

  r, c = best_cell
  for val in best_candidates:
    board[r][c] = val
    if solve_mrv(board):
      return True
    board[r][c] = 0
  return False


# --- THIET LAP VA IN KET QUA ---
board_seq = copy.deepcopy(board_initial)
calls_seq = 0
t0 = time.perf_counter()
solve_sequential(board_seq)
t1 = time.perf_counter()
time_seq = (t1 - t0) * 1000

board_mrv = copy.deepcopy(board_initial)
calls_mrv = 0
t0 = time.perf_counter()
solve_mrv(board_mrv)
t1 = time.perf_counter()
time_mrv = (t1 - t0) * 1000

same_res = "Co" if board_seq == board_mrv else "Khong"

print("=" * 65)
print(f"{'Dai luong':<35} | {'Quet tuan tu':<12} | {'MRV':<10}")
print("-" * 65)
print(f"{'So loi goi ham de quy':<35} | {calls_seq:<12} | {calls_mrv:<10}")
print(f"{'Thoi gian chay (ms)':<35} | {time_seq:<12.3f} | {time_mrv:<10.3f}")
print(
    f"{'Loi giai tim duoc co giong nhau?':<35} | {same_res:<12} | {same_res:<10}"
)
print("=" * 65)