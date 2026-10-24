# Julia danh chi so mang tu 1.
function liet_ke(n::Int)
    x = zeros(Int, n)
    dem = 0
    k = 1
    dem_dat = 0
    while true
        if sum(x) == k
            println(join(x))
            dem_dat += 1
        end
        dem += 1
        i = n
        while i >= 1 && x[i] == 1
            x[i] = 0  # Xoa cac bit 1 lien tiep o duoi.
            i -= 1
        end
        if i < 1
            break
        end
        x[i] = 1
    end
    println("So xau dat: ", dem_dat)
    return dem
end

function main()
    println("MSSV: N24DCDT059 | Ma ca: 1")
    println("Nhap n (1..10):")
    n = tryparse(Int, strip(readline()))
    if n === nothing || !(1 <= n <= 10)
        println("Du lieu khong hop le.")
        return
    end
    dem = liet_ke(n)
    println("Tong so xau da duyet: ", dem)
end

main()