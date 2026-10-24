function solve()
    # 1. Đọc n
    line_n = readline()
    if isempty(strip(line_n))
        return
    end
    n = parse(Int, strip(line_n))

    if n == 0
        println("SUM 0")
        println("MIN NA")
        println("MAX NA")
        println("FIRST -1")
        println("SEARCH_CMPS 0")
        println("PAIRS 0")
        println("DOUBLINGS 0")
        println("SCAN_VISITS 0")
        return
    end

    # 2. Đọc các số tiếp theo cho mảng A và giá trị x
    tokens = String[]
    while length(tokens) < n + 1
        line = readline()
        if !isempty(strip(line))
            append!(tokens, split(line))
        end
    end

    A = [parse(Int, tokens[i]) for i in 1:n]
    x = parse(Int, tokens[n + 1])

    # 3. Tính toán các giá trị
    sum_val = 0
    min_val = A[1]
    max_val = A[1]
    scan_visits = 0

    for val in A
        sum_val += val
        if val < min_val
            min_val = val
        end
        if val > max_val
            max_val = val
        end
        scan_visits += 1
    end

    first_idx = -1
    search_cmps = 0
    for i in 1:n
        search_cmps += 1
        if A[i] == x
            first_idx = i - 1  # Chuyển về chỉ số 0-indexed theo đề bài
            break
        end
    end

    pairs = 0
    for i in 1:n
        for j in (i + 1):n
            pairs += 1
        end
    end

    doublings = 0
    i = 1
    while i <= n
        doublings += 1
        i *= 2
    end

    # 4. In kết quả
    println("SUM ", sum_val)
    println("MIN ", min_val)
    println("MAX ", max_val)
    println("FIRST ", first_idx)
    println("SEARCH_CMPS ", search_cmps)
    println("PAIRS ", pairs)
    println("DOUBLINGS ", doublings)
    println("SCAN_VISITS ", scan_visits)
end

solve()