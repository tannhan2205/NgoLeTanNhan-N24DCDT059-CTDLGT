# Thu tu tham so: n, nguon, trung_gian, dich.
def ha_noi(n: int, a: str, b: str, c: str) -> int:
    if n == 0:
        return 0
    trai = ha_noi(n - 1, a, c, b)
    print(f"Dia {n}: {a} -> {c}")
    phai = ha_noi(n - 1, b, a, c)
    return trai + 1 + phai  # Dem cac nuoc di da thuc hien.

def main():
    print("MSSV: N24DCDT059 | Ma ca: 1")
    print("Nhap n (1..8):")
    try:
        n = int(input().strip())
    except (ValueError, EOFError):
        print("Du lieu khong hop le.")
        return
    if not 1 <= n <= 8:
        print("Du lieu khong hop le.")
        return
    
    dem = ha_noi(n, "A", "B", "C")  
    print("Tong so nuoc di:", dem)

if __name__ == "__main__":
    main()