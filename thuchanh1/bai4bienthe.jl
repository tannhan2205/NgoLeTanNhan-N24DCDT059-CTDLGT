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
end

function main()
    raw_input = read(stdin, String)
    tokens = split(raw_input)
    
    length(tokens) < 4 && error_exit()
    
    n = tryparse(Int, tokens[1])
    k = tryparse(Int, tokens[2])
    
    (n === nothing || k === nothing) && error_exit()
    (n < 1 || n > 2000 || k != 1) && error_exit()
    
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
        
        push!(points, Point(id, x, y, label))
    end
    
    qx = tryparse(Int, tokens[idx])
    qy = tryparse(Int, tokens[idx+1])
    (qx === nothing || qy === nothing) && error_exit()
    (qx < 0 || qx > 10 || qy < 0 || qy > 10) && error_exit()
    
    min_d2 = typemax(Int)
    min_id = typemax(Int)
    best_point = nothing
    
    for p in points
        d2 = (p.x - qx)^2 + (p.y - qy)^2
        if d2 < min_d2 || (d2 == min_d2 && p.id < min_id)
            min_d2 = d2
            min_id = p.id
            best_point = p
        end
    end
    
    println("NEIGHBORS 1")
    println("$(best_point.id) $(best_point.label) $min_d2")
    if best_point.label == "A"
        println("VOTES A 1 B 0")
    else
        println("VOTES A 0 B 1")
    end
    println("PREDICT $(best_point.label)")
end

main()