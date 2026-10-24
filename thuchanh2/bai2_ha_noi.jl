# Thu tu tham so: n, nguon, trung_gian, dich.
function ha_noi(n::Int, a::String, b::String, c::String)
    if n == 0
        return 0
    end
    trai = ha_noi(n - 1, a, c, b)
    println("Dia $n: $a -> $c")
    phai = ha_noi(n - 1, b, a, c)
    return trai + 1 + phai  # Dem cac nuoc di da thuc hien.
end

function main()
    println("MSSV: N24DCDT059 | Ma ca: 1")
    println("Nhap n (1..8):")
    n = tryparse(Int, strip(readline()))
    if n === nothing || !(1 <= n <= 8)
        println("Du lieu khong hop le.")
        return
    end
    dem = ha_noi(n, "A", "B", "C")
    println("Tong so nuoc di: ", dem)
end

main()
