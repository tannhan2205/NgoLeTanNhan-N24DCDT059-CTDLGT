# Bai 4.2 - Chon hoat dong: bon tieu chi tren cung mot bo du lieu

struct Act
    name::String
    s::Int
    f::Int
end

activities = [
    Act("H1", 1, 5), Act("H2", 2, 5), Act("H3", 2, 6), Act("H4", 3, 4), Act("H5", 4, 8),
    Act("H6", 6, 9), Act("H7", 8, 11), Act("H8", 9, 14), Act("H9", 11, 13), Act("H10", 12, 15)
]

compatible(a::Act, b::Act) = b.s >= a.f || a.s >= b.f

function compatible_with_all(a::Act, chosen::Vector{Act})
    for c in chosen
        if !compatible(a, c)
            return false
        end
    end
    return true
end

function greedy(order::Vector{Act})
    chosen = Act[]
    for a in order
        if compatible_with_all(a, chosen)
            push!(chosen, a)
        end
    end
    return chosen
end

function show_result(label::String, chosen::Vector{Act})
    names = join([a.name for a in chosen], ", ")
    println(rpad(label, 22), " -> ", lpad(length(chosen), 2), " hoat dong: ", names)
end

# Tieu chi 1: Ket thuc som nhat
order1 = sort(activities, by = a -> a.f)
r1 = greedy(order1)

# Tieu chi 2: Bat dau som nhat
order2 = sort(activities, by = a -> a.s)
r2 = greedy(order2)

# Tieu chi 3: Ngan nhat
order3 = sort(activities, by = a -> a.f - a.s)
r3 = greedy(order3)

# Tieu chi 4: Chong lan voi it hoat dong khac nhat
conflict_count = Dict{String,Int}()
for a in activities
    cnt = count(b -> b.name != a.name && !compatible(a, b), activities)
    conflict_count[a.name] = cnt
end
order4 = sort(activities, by = a -> conflict_count[a.name])
r4 = greedy(order4)

println("=== Bon tieu chi tham lam ===")
show_result("1. Ket thuc som nhat", r1)
show_result("2. Bat dau som nhat", r2)
show_result("3. Ngan nhat", r3)
show_result("4. It chong lan nhat", r4)

# Chuong trinh tim so hoat dong nhieu nhat that su (vet can toan bo tap con)
n = length(activities)
best = Act[]
for mask in 0:(2^n - 1)
    subset = Act[]
    for i in 0:(n-1)
        if (mask >> i) & 1 == 1
            push!(subset, activities[i+1])
        end
    end
    ok = true
    for i in 1:length(subset)
        for j in (i+1):length(subset)
            if !compatible(subset[i], subset[j])
                ok = false
                break
            end
        end
        if !ok
            break
        end
    end
    if ok && length(subset) > length(best)
       global  best = subset
    end
end

println("\n=== Ket qua toi uu that su (vet can) ===")
show_result("Toi uu (brute force)", best)