function solve(a::Vector{Int}, x::Int, test_num::Int)
    println("=== TEST CASE $test_num ===")
    println("Array: $a, x = $x")

    n = length(a)
    if n == 0
        println("FIRST -1\nCOUNT 0\nLOWER 0\nUPPER 0\nPROBES 0\n")
        return
    end

    # Kiểm tra tính chất không giảm
    for i in 1:(n - 1)
        if a[i] > a[i + 1]
            println("ERROR: array must be sorted\n")
            return
        end
    end

    # lower_bound
    low, high = 0, n
    probes_lower = 0
    while low < high
        mid = div(low + high, 2)
        probes_lower += 1
        if a[mid + 1] >= x
            high = mid
        else
            low = mid + 1
        end
    end
    lower = low

    # upper_bound
    low, high = 0, n
    probes_upper = 0
    while low < high
        mid = div(low + high, 2)
        probes_upper += 1
        if a[mid + 1] > x
            high = mid
        else
            low = mid + 1
        end
    end
    upper = low

    count = upper - lower
    first = (count > 0) ? lower : -1
    probes = probes_lower + probes_upper

    println("FIRST $first")
    println("COUNT $count")
    println("LOWER $lower")
    println("UPPER $upper")
    println("PROBES $probes\n")
end

function main()
    tests = [
        ([1, 2, 2, 5, 7, 9], 2),
        (Int[], 2),
        ([2, 2, 2], 2),
        ([1, 2, 2, 5, 7, 9], 4),
        ([1, 2, 2, 5, 7, 9], 0),
        ([1, 2, 2, 5, 7, 9], 10),
        ([7, 2, 5, 2, 9, 1], 2)
    ]

    for (idx, (a, x)) in enumerate(tests)
        solve(a, x, idx)
    end
end

main()