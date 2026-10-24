using Printf
# Đọc TOÀN BỘ dữ liệu từ file/terminal
data = split(read(stdin, String))
n = parse(Int, data[1])
numbers = Int[]
# Đưa n số còn lại vào mảng
for i in 2:(n + 1)
    push!(numbers, parse(Int, data[i]))
end
# Tính toán các giá trị
tong = sum(numbers)
trung_binh = tong / n
nho_nhat = minimum(numbers)
lon_nhat = maximum(numbers)

# In kết quả chuẩn 4 chữ số thập phân
@printf("%d %.4f %d %d\n", tong, trung_binh, nho_nhat, lon_nhat)