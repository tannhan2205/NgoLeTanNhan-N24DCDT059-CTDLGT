"""Hai kiểm thử tự bổ sung (T13, T14) + trường hợp biên kèm theo.

T13 — biên: hàng đợi sức chứa 1 sau khi quay vòng.
T14 — dữ liệu không hợp lệ: k thực/k Boolean cho cả hai hàm.
Nếu dùng ngẫu nhiên, seed = 20260917.
"""
import unittest
from cau_truc import DSLK, NganXep, HangDoiVong
from bai_lam import dem_gia_tri, xoa_tat_ca, lay_nhieu, xem_k


class TestThem(unittest.TestCase):

    def test_t13_hang_doi_suc_chua_mot(self):
        q = HangDoiVong(1)
        self.assertTrue(q.them(5))
        self.assertEqual(q.lay(), 5)          # dau quay vòng: (0+1) % 1 = 0
        self.assertTrue(q.them(7))            # mảng vật lý chỉ có 1 ô
        before = (q.a.copy(), q.dau, q.so, q.n)
        self.assertEqual(xem_k(q, 1), [7])    # FIFO = phần tử duy nhất
        self.assertEqual((q.a, q.dau, q.so, q.n), before)
        # Biên kèm theo: xoá danh sách chỉ có MỘT nút trùng x
        L = DSLK([9])
        self.assertEqual(xoa_tat_ca(L, 9), 1)
        self.assertIsNone(L.dau)
        self.assertEqual(L.n, 0)

    # ------------------------------------------------------------------
    # T14 (dữ liệu không hợp lệ): k = 1.5 và k = True phải bị từ chối
    # bởi cả lay_nhieu lẫn xem_k, và KHÔNG làm thay đổi dữ liệu.
    # Lý do chọn: trong Python True == 1 nên nếu chỉ so sánh giá trị
    # sẽ bỏ lọt; đề yêu cầu chặn riêng kiểu Boolean.
    # ------------------------------------------------------------------
    def test_t14_k_kieu_sai_bi_tu_choi(self):
        s = NganXep()
        for v in [10, 20, 30]:
            s.day(v)
        for k_sai in [1.5, True]:
            before = s.a.copy()
            with self.assertRaises(ValueError):
                lay_nhieu(s, k_sai)
            self.assertEqual(s.a, before)     # không mất dữ liệu

        q = HangDoiVong(4)
        for v in [1, 2, 3, 4]:
            q.them(v)
        for k_sai in [1.5, True]:
            before = (q.a.copy(), q.dau, q.so, q.n)
            with self.assertRaises(ValueError):
                xem_k(q, k_sai)
            self.assertEqual((q.a, q.dau, q.so, q.n), before)


if __name__ == "__main__":
    unittest.main(verbosity=2)