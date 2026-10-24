"""Bốn chức năng của bài tập 7 ngày — bản sinh viên."""

BAN = "Sinh viên"
from cau_truc import DSLK, NganXep, HangDoiVong, so_nguyen


def dem_gia_tri(L: DSLK, x: int) -> int:
    """Bài 1: Đếm số nút có gt == x. Chỉ duyệt liên kết, không đổi L."""
    x = so_nguyen(x)          # dữ liệu phải nằm trong [-1_000_000, 1_000_000]
    dem, p = 0, L.dau
    while p is not None:      # lần theo ke tới khi hết danh sách
        if p.gt == x:
            dem += 1
        p = p.ke              # dùng đúng biến p như đề cho phép
    return dem                # danh sách rỗng -> vòng lặp không chạy -> 0


def xoa_tat_ca(L: DSLK, x: int) -> int:
    """Bài 2: Xoá mọi nút có gt == x trong MỘT lượt duyệt.
    Giữ nguyên các đối tượng nút còn lại; trả về số nút đã xoá."""
    x = so_nguyen(x)
    dem = 0
    truoc, p = None, L.dau
    while p is not None:
        sau = p.ke                    # lưu lối đi trước khi sửa liên kết
        if p.gt == x:
            if truoc is None:
                L.dau = sau           # xoá nút đầu: dau nhảy sang nút sau
            else:
                truoc.ke = sau        # xoá giữa/cuối: nhảy qua p
            L.n -= 1
            dem += 1
            # Giữ nguyên truoc — nếu dời truoc sang p sẽ bỏ sót
            # nút trùng đứng LIỀN SAU p (câu 3a của báo cáo).
        else:
            truoc = p                 # chỉ dời truoc khi giữ lại nút p
        p = sau
    return dem


def lay_nhieu(s: NganXep, k: int) -> list[int]:
    """Bài 3: Lấy đúng k phần tử từ đỉnh (LIFO).
    Kiểm tra k TRƯỚC khi lấy để k sai không làm mất dữ liệu."""
    if type(k) is not int or not 0 <= k <= len(s.a):
        # type(k) is not int chặn luôn True/False (bool là con của int)
        raise ValueError("k phải là số nguyên từ 0 đến số phần tử ngăn xếp.")
    result: list[int] = []
    for _ in range(k):
        result.append(s.lay())        # dùng thao tác lấy một phần tử có sẵn
    return result                     # thứ tự lấy ra: đỉnh trước (LIFO)


def xem_k(q: HangDoiVong, k: int) -> list[int]:
    """Bài 4: Trả về k phần tử đầu theo FIFO — chỉ XEM, không đổi q."""
    if type(k) is not int or not 0 <= k <= q.so:
        raise ValueError("k phải là số nguyên từ 0 đến số phần tử hàng đợi.")
    result: list[int] = []
    for i in range(k):
        # Chỉ số logic i quy đổi vào mảng vật lý quay vòng:
        # (dau + i) % n — KHÔNG đọc thẳng k ô đầu của mảng a.
        result.append(q.a[(q.dau + i) % q.n])
    return result                     # a, dau, so, n giữ nguyên