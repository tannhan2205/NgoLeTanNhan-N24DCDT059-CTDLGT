# ĐỀ TÀI DT053: ĐƯỜNG ĐI CÓ TỔNG NHỎ NHẤT TRÊN LƯỚI
**Học viện Công nghệ Bưu chính Viễn thông - Cơ sở tại TP. Hồ Chí Minh**  
**Môn học:** Cấu trúc dữ liệu và giải thuật (INT13185 - Nhóm 03)  
**Giảng viên hướng dẫn:** ThS. Hồ Nhựt Minh  

---

## 1. Thông tin sinh viên
* **Họ và tên:** Ngô Lê Tấn Nhân
* **MSSV:** N24DCDT059
* **Lớp:** D24CQDT01-N
* **Mã đề:** DT053
* **Repository GitHub:** [https://github.com/tannhan2205/NgoLeTanNhan-N24DCDT059-CTDLGT](https://github.com/tannhan2205/NgoLeTanNhan-N24DCDT059-CTDLGT)

---

## 2. Mô tả bài toán
Cho lưới ô vuông $C$ kích thước $m \times n$ ($1 \le m, n \le 10$), mỗi ô chứa số nguyên $0 \le C[i][j] \le 99$.
Xuất phát từ ô trên-trái $(1, 1)$, tìm đường đi đến ô dưới-phải $(m, n)$ sao cho tổng chi phí các ô đi qua là nhỏ nhất.
Chỉ cho phép hai thao tác di chuyển:
* **Sang phải:** $(i, j) \to (i, j+1)$
* **Xuống dưới:** $(i, j) \to (i+1, j)$

---

## 3. Cấu trúc thư mục
```text
NgoLeTanNhan-N24DCDT059/
├── src/
│   ├── DuongDiNhoNhat.hpp    # Định nghĩa cấu trúc dữ liệu và thuật toán chính + truy vết
│   └── main.cpp              # Chương trình CLI chạy ví dụ & nhập trực tiếp từ bàn phím
├── test/
│   └── runtests.cpp          # Bộ kiểm thử tự động 14 ca độc lập (100% PASS)
├── docs/
│   └── anh_ket_qua/          # Thư mục lưu 11 ảnh minh chứng A01 - A11
├── README.md                 # Hướng dẫn chi tiết biên dịch & chạy
└── .gitignore
```

---

## 4. Hướng dẫn biên dịch và chạy

### 4.1. Yêu cầu môi trường
* Trình biên dịch C++ hỗ trợ C++14 trở lên (`g++` hoặc `clang++` hoặc `MSVC`).

### 4.2. Lệnh biên dịch

#### Biên dịch chương trình chính (CLI / Demo):
```bash
g++ -O2 -std=c++14 src/main.cpp -o main.exe
# hoặc nếu dùng clang++:
clang++ -O2 -std=c++14 src/main.cpp -o main.exe
```

#### Biên dịch bộ kiểm thử (Test suite):
```bash
g++ -O2 -std=c++14 test/runtests.cpp -o runtests.exe
# hoặc nếu dùng clang++:
clang++ -O2 -std=c++14 test/runtests.cpp -o runtests.exe
```

---

### 4.3. Các lệnh thực thi

1. **Chạy Ví dụ 1 đề bài:**
   ```bash
   ./main.exe --vd1
   ```
   *Kết quả mong đợi:* `tong=7; duong=[(1, 1), (1, 2), (1, 3), (2, 3), (3, 3)]`

2. **Chạy Ví dụ 2 đề bài:**
   ```bash
   ./main.exe --vd2
   ```
   *Kết quả mong đợi:* `tong=7; duong=[(1, 1), (1, 2), (1, 3)]`

3. **Chế độ nhập từ bàn phím:**
   ```bash
   ./main.exe
   ```
   *(Lựa chọn 3: Nhập số hàng m, số cột n và các phần tử ma trận)*

4. **Chạy toàn bộ 14 ca kiểm thử:**
   ```bash
   ./runtests.exe
   ```

---

## 5. Tóm tắt kết quả kiểm thử (14 ca)
* **Số ca kiểm độc lập:** 14 ca (vượt chuẩn tối thiểu 12 ca)
* **Số ca đạt:** 14/14 ca (100%)
* Bao quát đầy đủ:
  - Ví dụ 1 & Ví dụ 2 phiếu giao (A01, A02)
  - 2 ca tự thiết kế (A03, A04)
  - 3 ca biên [1x1, 1 hàng, 1 cột, cực đại 10x10, hình 4.4 giáo trình] (A05, A06, A07)
  - Các ca input sai phạm vi bị từ chối và báo lỗi chính xác (A08)
