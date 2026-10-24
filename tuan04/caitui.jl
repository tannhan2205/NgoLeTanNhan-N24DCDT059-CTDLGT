struct Item
    name::String
    w::Int
    v::Int
    ratio::Float64
end

function upper_bound(items, idx, curr_w, curr_v, W)
    if curr_w > W
        return 0.0
    end
    ub = Float64(curr_v)
    rem_w = W - curr_w
    for j in idx:length(items)
        if items[j].w <= rem_w
            rem_w -= items[j].w
            ub += items[j].v
        else
            ub += rem_w * items[j].ratio
            break
        end
    end
    return ub
end

function solve_knapsack(items, W, with_pruning)
    best_val = 0
    best_set = String[]
    nodes_count = 0

    function dfs(idx, curr_w, curr_v, curr_set)
        nodes_count += 1
        if curr_w > W
            return
        end

        if curr_v > best_val
            best_val = curr_v
            best_set = copy(curr_set)
        end

        if idx > length(items)
            return
        end

        if with_pruning
            ub = upper_bound(items, idx, curr_w, curr_v, W)
            if ub <= best_val
                return
            end
        end

        # Branch 1: Take item
        push!(curr_set, items[idx].name)
        dfs(idx + 1, curr_w + items[idx].w, curr_v + items[idx].v, curr_set)
        pop!(curr_set)

        # Branch 2: Skip item
        dfs(idx + 1, curr_w, curr_v, curr_set)
    end

    dfs(1, 0, 0, String[])
    return best_val, best_set, nodes_count
end

items = [
    Item("A", 4, 19, 19/4), Item("B", 7, 25, 25/7), Item("C", 3, 7, 7/3),
    Item("D", 3, 8, 8/3),   Item("E", 3, 9, 9/3),   Item("F", 10, 21, 21/10)
]

sort!(items, by = x -> x.ratio, rev = true)
W = 14

val_p, set_p, nodes_p = solve_knapsack(items, W, true)
_, _, nodes_np = solve_knapsack(items, W, false)

println("Gia tri lon nhat: ", val_p)
println("So nut CO cat nhanh: ", nodes_p)
println("So nut KHONG cat nhanh: ", nodes_np)