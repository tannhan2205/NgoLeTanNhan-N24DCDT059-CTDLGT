def xau_ke_tiep(x):
    """Bien doi x thanh xau ke tiep. Tra ve None neu x da la xau cuoi cung."""
    i = len(x) - 1
    while i >= 0 and x[i] == 1:   # quet tu phai sang, xoa cac so 1 ve 0
        x[i] = 0
        i -= 1
    if i < 0:                     # het: moi chu so deu la 1
        return None
    x[i] = 1                      # doi chu so 0 dau tien thanh 1
    return x

def liet_ke_xau(n):
    x = [0] * n
    ds = ["".join(map(str, x))]
    while xau_ke_tiep(x) is not None:
        ds.append("".join(map(str, x)))
    return ds
if __name__ == "__main__":
    n = int(input("Nhập độ dài xâu n: "))
    ket_qua = liet_ke_xau(n)
    
    print(f"Danh sách {len(ket_qua)} xâu nhị phân:")
    for xau in ket_qua:
        print(xau)