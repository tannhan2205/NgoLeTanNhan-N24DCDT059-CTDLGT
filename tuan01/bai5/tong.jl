function main()
    n = parse(Int, readline())
    a = parse.(Int, split(readline()))
    
    total = sum(a)
    maxval = maximum(a)
    
    println(total, " ", maxval)
end

main()