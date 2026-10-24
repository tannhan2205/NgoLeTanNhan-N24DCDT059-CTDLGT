import sys

def main():
    # Đọc toàn bộ dữ liệu đầu vào (hỗ trợ đọc nhiều dòng hoặc cách nhau bởi khoảng trắng)
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    n = int(input_data[0])
    numbers = [int(x) for x in input_data[1:n+1]]
    
    tong = sum(numbers)
    trung_binh = tong / n
    nho_nhat = min(numbers)
    lon_nhat = max(numbers)
    
    # In kết quả theo yêu cầu: Tổng TBC Min Max
    print(f"{tong} {trung_binh:.4f} {nho_nhat} {lon_nhat}")

if __name__ == "__main__":
    main()