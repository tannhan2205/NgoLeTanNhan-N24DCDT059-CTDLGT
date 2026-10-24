Bài tập Chương 5 — Danh sách liên kết, Ngăn xếp, Hàng đợi
Bài tập lập trình 7 ngày — Cấu trúc dữ liệu và giải thuật

Họ tên: Ngô Lê Tấn Nhân
MSSV: N24DCDT059
Lớp: D24CQDT01-N
Ngôn ngữ: Python 3.
Hệ điều hành: Windows
Ngày hoàn thành: 23/09 /2026
Nội dung tự viết
Tệp	Nội dung
python/bai_lam.py	Bốn hàm bài tập: dem_gia_tri, xoa_tat_ca, lay_nhieu, xem_k
python/test_them.py	Hai kiểm thử tự bổ sung: T13 (hàng đợi sức chứa 1 quay vòng), T14 (k    kiểu sai bị từ chối)
Phần được cung cấp sẵn (không sửa)
python/cau_truc.py — cấu trúc dữ liệu và thao tác cơ bản
python/dich_vu.py — nối nút bấm giao diện với thuật toán
python/app.py — máy chủ cục bộ
python/test_bai_tap.py, python/test_co_ban.py — bộ kiểm thử mẫu
web/ — giao diện trình duyệt
Cách chạy chương trình
cd pythonpython app.py
Mở trình duyệt tại: http://127.0.0.1:8000

Nếu cổng 8000 bị chiếm: python app.py --port 8002 và mở http://127.0.0.1:8002
(Windows: nếu lệnh python không nhận, dùng py thay thế.)

Cách chạy kiểm thử
bash

cd python
python test_bai_tap.py     # 17 kiểm thử bài tập (gồm 200 dãy ngẫu nhiên seed 20260917)
python test_them.py        # 2 kiểm thử tự bổ sung (T13, T14)
python test_co_ban.py      # 25 kiểm thử mẫu
Kết quả khi nộp: cả ba bộ đều OK (chi tiết trong ket_qua_kiem_thu.txt).

Minh chứng
ket_qua_kiem_thu.txt — kết quả chạy thật của ba bộ kiểm thử
nhat_ky_chuong5.json — nhật ký thao tác xuất từ giao diện web
Ảnh chụp bốn chức năng (Đếm x, Xóa tất cả x, Lấy k phần tử, Xem k phần tử) được chèn trong tệp báo cáo
Ghi chú
Bốn hàm trong bai_lam.py đã vượt qua toàn bộ kiểm thử công khai và kiểm thử tự viết.
Không sửa đổi JavaScript, bộ kiểm thử mẫu hay phần giao diện.