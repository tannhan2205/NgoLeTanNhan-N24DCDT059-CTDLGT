# Sinh ke tiep; moi cau hinh duoc in va dem mot lan.
def liet_ke(n: int) -> int:
    x = [0] * n
    dem = 0
    while True:
        print("".join(map(str, x)))
        dem += 1
        i = n - 1
        while i >= 0 and x[i] == 1:
            x[i] = 0  # Xoa cac bit 1 lien tiep o duoi.
            i -= 1
        if i < 0:
            break
        x[i] = 1
    return dem

def main():
    print("MSSV: DIEN_MSSV | Ma ca: DIEN_MA_CA")
    print("Nhap n (1..10):")
    try:
        n = int(input().strip())
    except (ValueError, EOFError):
        print("Du lieu khong hop le.")
        return
    if not 1 <= n <= 10:
        print("Du lieu khong hop le.")
        return
    dem = liet_ke(n)
    print("Tong so xau:", dem)

if __name__ == "__main__":
    main()
