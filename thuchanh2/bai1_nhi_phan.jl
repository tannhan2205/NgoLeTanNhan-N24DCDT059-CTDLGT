# Julia danh chi so mang tu 1.
function liet_ke(n::Int)
    x = zeros(Int, n)
    dem = 0
    while true
        println(join(x))
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
    return dem
end

function main()
    println("MSSV: DIEN_MSSV | Ma ca: DIEN_MA_CA")
    println("Nhap n (1..10):")
    n = tryparse(Int, strip(readline()))
    if n === nothing || !(1 <= n <= 10)
        println("Du lieu khong hop le.")
        return
    end
    dem = liet_ke(n)
    println("Tong so xau: ", dem)
end

main()
