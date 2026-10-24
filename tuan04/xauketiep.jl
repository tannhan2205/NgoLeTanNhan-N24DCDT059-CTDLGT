function xau_ke_tiep!(x::Vector{Int})
    i = length(x)
    while i >= 1 && x[i] == 1      # quet tu phai sang, xoa cac so 1 ve 0
        x[i] = 0
        i -= 1
    end
    if i < 1                       # het: moi chu so deu la 1
        return false
    end
    x[i] = 1                       # doi chu so 0 dau tien thanh 1
    return true
end

function liet_ke_xau(n::Int)
    x = zeros(Int, n)
    ds = [join(x)]
    while xau_ke_tiep!(x)
        push!(ds, join(x))
    end
    return ds
end

n = 3  
ket_qua = liet_ke_xau(n)

println("Danh sách $n-bit:")
for s in ket_qua
    println(s)
end