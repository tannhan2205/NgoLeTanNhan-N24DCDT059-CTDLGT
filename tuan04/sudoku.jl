using Printf

# De bai Sudoku 9x9 (0 la o trong)
const BOARD_INITIAL = [
    0 0 0  0 0 6  0 0 0;
    0 8 1  0 5 0  4 0 0;
    0 0 9  0 0 7  0 5 8;
    0 0 0  0 9 0  0 0 0;
    0 0 6  0 0 1  0 0 7;
    7 4 0  0 0 0  2 0 1;
    0 0 0  1 3 0  0 0 4;
    0 0 0  0 2 9  0 0 0;
    9 0 0  0 0 8  0 6 0
]

function is_valid(board, r, c, val)
    for i in 1:9
        if board[r, i] == val || board[i, c] == val
            return false
        end
    end
    br = 3 * div(r - 1, 3) + 1
    bc = 3 * div(c - 1, 3) + 1
    for i in br:(br + 2)
        for j in bc:(bc + 2)
            if board[i, j] == val
                return false
            end
        end
    end
    return true
end

function get_candidates(board, r, c)
    used = Set{Int}()
    for i in 1:9
        if board[r, i] != 0
            push!(used, board[r, i])
        end
        if board[i, c] != 0
            push!(used, board[i, c])
        end
    end
    br = 3 * div(r - 1, 3) + 1
    bc = 3 * div(c - 1, 3) + 1
    for i in br:(br + 2)
        for j in bc:(bc + 2)
            if board[i, j] != 0
                push!(used, board[i, j])
            end
        end
    end
    return [val for val in 1:9 if !(val in used)]
end

# --- 1. QUET TUAN TU ---
calls_seq = 0

function solve_sequential!(board)
    global calls_seq += 1
    empty_pos = nothing
    for r in 1:9
        for c in 1:9
            if board[r, c] == 0
                empty_pos = (r, c)
                break
            end
        end
        if empty_pos !== nothing
            break
        end
    end

    if empty_pos === nothing
        return true
    end

    r, c = empty_pos
    for val in 1:9
        if is_valid(board, r, c, val)
            board[r, c] = val
            if solve_sequential!(board)
                return true
            end
            board[r, c] = 0
        end
    end
    return false
end

# --- 2. HEURISTIC MRV ---
calls_mrv = 0

function solve_mrv!(board)
    global calls_mrv += 1
    min_cands = 10
    best_cell = nothing
    best_candidates = Int[]

    for r in 1:9
        for c in 1:9
            if board[r, c] == 0
                cands = get_candidates(board, r, c)
                if length(cands) < min_cands
                    min_cands = length(cands)
                    best_cell = (r, c)
                    best_candidates = cands
                    if min_cands == 0
                        return false
                    end
                end
            end
        end
    end

    if best_cell === nothing
        return true
    end

    r, c = best_cell
    for val in best_candidates
        board[r, c] = val
        if solve_mrv!(board)
            return true
        end
        board[r, c] = 0
    end
    return false
end

function main()
    board_seq = copy(BOARD_INITIAL)
    global calls_seq = 0
    t_start = time_ns()
    solve_sequential!(board_seq)
    time_seq = (time_ns() - t_start) / 1e6

    board_mrv = copy(BOARD_INITIAL)
    global calls_mrv = 0
    t_start = time_ns()
    solve_mrv!(board_mrv)
    time_mrv = (time_ns() - t_start) / 1e6

    same_res = board_seq == board_mrv ? "Co" : "Khong"

    println("=" ^ 65)
    @printf("%-35s | %-12s | %-10s\n", "Dai luong", "Quet tuan tu", "MRV")
    println("-" ^ 65)
    @printf("%-35s | %-12d | %-10d\n", "So loi goi ham de quy", calls_seq, calls_mrv)
    @printf("%-35s | %-12.3f | %-10.3f\n", "Thoi gian chay (ms)", time_seq, time_mrv)
    @printf("%-35s | %-12s | %-10s\n", "Loi giai tim duoc co giong nhau?", same_res, same_res)
    println("=" ^ 65)
end

main()