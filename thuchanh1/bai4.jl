using Base: exit

function error_exit()
    println("ERROR: invalid data")
    exit(1)
end

struct Point
    id::Int
    x::Int
    y::Int
    label::String
    d2::Int
end

function main()
    raw_input = read(stdin, String)
    tokens = split(raw_input)
    
    length(tokens) < 4 && error_exit()
    
    n = tryparse(Int, tokens[1])
    k = tryparse(Int, tokens[2])
    
    (n === nothing || k === nothing) && error_exit()
    (n < 1 || n > 2000 || k < 1 || k > n) && error_exit()
    
    length(tokens) != 2 + 4 * n + 2 && error_exit()
    
    idx = 3
    points = Point[]
    seen_ids = Set{Int}()
    
    for i in 1:n
        id = tryparse(Int, tokens[idx])
        x = tryparse(Int, tokens[idx+1])
        y = tryparse(Int, tokens[idx+2])
        label = String(tokens[idx+3])
        idx += 4
        
        (id === nothing || x === nothing || y === nothing) && error_exit()
        (id < 1 || id > 1000000 || id in seen_ids) && error_exit()
        push!(seen_ids, id)
        
        (x < 0 || x > 10 || y < 0 || y > 10) && error_exit()
        (label != "A" && label != "B") && error_exit()
        
        push!(points, Point(id, x, y, label, 0))
    end
    
    qx = tryparse(Int, tokens[idx])
    qy = tryparse(Int, tokens[idx+1])
    (qx === nothing || qy === nothing) && error_exit()
    (qx < 0 || qx > 10 || qy < 0 || qy > 10) && error_exit()
    
    points_with_d2 = map(p -> Point(p.id, p.x, p.y, p.label, (p.x - qx)^2 + (p.y - qy)^2), points)
    
    sort!(points_with_d2, by = p -> (p.d2, p.id))
    
    votes_a = 0
    votes_b = 0
    
    println("NEIGHBORS $k")
    for i in 1:k
        p = points_with_d2[i]
        println("$(p.id) $(p.label) $(p.d2)")
        if p.label == "A"
            votes_a += 1
        else
            votes_b += 1
        end
    end
    
    println("VOTES A $votes_a B $votes_b")
    predict = (votes_a >= votes_b) ? "A" : "B"
    println("PREDICT $predict")
end

main()