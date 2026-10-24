struct TSPBranchAndBound
    matrix::Matrix{Int}
    n::Int
    c_min::Int
end

function TSPBranchAndBound(matrix::Matrix{Int})
    n = size(matrix, 1)
    # Tim c_min (canh nho nhat khong nam tren duong cheo chinh)
    c_min = minimum([matrix[i, j] for i in 1:n, j in 1:n if i != j])
    return TSPBranchAndBound(matrix, n, c_min)
end

function solve(tsp::TSPBranchAndBound; with_pruning::Bool=true)
    n = tsp.n
    best_cost = Ref(typemax(Int))
    best_path = Int[]
    node_count = Ref(0)

    visited = fill(false, n)
    visited[1] = true
    path = [1]

    function dfs(u::Int, current_cost::Int, level::Int)
        node_count[] += 1

        if level == n
            total_cost = current_cost + tsp.matrix[u, 1]
            if total_cost < best_cost[]
                best_cost[] = total_cost
                best_path = copy(path)
                push!(best_path, 1)
            end
            return
        end

        for v in 1:n
            if !visited[v]
                next_cost = current_cost + tsp.matrix[u, v]
                lb = next_cost + (n - level) * tsp.c_min

                if !with_pruning || lb < best_cost[]
                    visited[v] = true
                    push!(path, v)
                    dfs(v, next_cost, level + 1)
                    pop!(path)
                    visited[v] = false
                end
            end
        end
    end

    dfs(1, 0, 1)

    # Chuyen chi so tu 1-based (Julia) ve 0-based de khop de bai
    path_0based = best_path .- 1
    mode_str = with_pruning ? "CO CAT NHANH" : "KHONG CAT NHANH"
    
    println("[$mode_str]")
    println("Chi phi toi uu: ", best_cost[])
    println("Hanh trinh toi uu: ", join(path_0based, " -> "))
    println("So nut da duyet: ", node_count[], "\n")
end

# Ma tran chi phi 5x5
cost_matrix = [
     0 10  9 22 23;
    10  0 16 19 14;
     9 16  0  7 28;
    22 19  7  0  8;
    23 14 28  8  0
]

solver = TSPBranchAndBound(cost_matrix)
println("Gia tri c_min tim duoc: ", solver.c_min, "\n")

solve(solver, with_pruning=true)  # Co cat nhanh
solve(solver, with_pruning=false) # Khong cat nhanh