# ĐỀ TÀI DT022: ĐẾM SỐ PHẦN TỬ NHỎ HƠN X BẰNG TÌM KIẾM NHỊ PHÂN
**Học viện Công nghệ Bưu chính Viễn thông - Cơ sở tại TP. Hồ Chí Minh**  
**Môn học:** Cấu trúc dữ liệu và giải thuật (INT13185 - Nhóm 03)  
**Giảng viên hướng dẫn:** ThS. Hồ Nhựt Minh  

---

## 1. Thông tin sinh viên
* **Họ và tên:** Ngô Lê Tấn Nhân
* **MSSV:** N24DCDT059
* **Lớp:** D24CQDT01-N
* **Mã đề:** DT022
* **Tên đề tài:** Đếm số phần tử nhỏ hơn x bằng tìm kiếm nhị phân
* **Giáo trình tham khảo:** INT1306 - Chương 2, Mục 2.6.2; mục 2.8 bài 22; trang in 50–52, 61; trang PDF 62–64, 73.

---

## 2. Mô tả bài toán
Cho mảng số nguyên $a$ gồm $n$ phần tử ($0 \le n \le 10000$) đã được sắp xếp tăng không giảm ($a[i] \le a[i+1]$) và một số nguyên $x$. Các phần tử trong mảng có thể có giá trị âm, dương, bằng 0 và có thể có nhiều phần tử trùng lặp.

**Yêu cầu:**
Đếm số lượng phần tử nhỏ hơn $x$ ($a[i] < x$) bằng cách tìm vị trí đầu tiên có giá trị không nhỏ hơn $x$ ($a[i] \ge x$, tức là ranh giới phân tách mảng).

**Quy ước chỉ số và vị trí biên (1-based index theo giáo trình):**
1. Nếu tồn tại phần tử $a[i] \ge x$, gọi vị trí đầu tiên xuất hiện là $bien$ ($1 \le bien \le n$). Khi đó, toàn bộ các phần tử từ chỉ số $1$ đến $bien - 1$ đều thỏa mãn $a[i] < x$. Do đó:
   $$\text{so\_nho\_hon} = bien - 1$$
2. Nếu không có phần tử nào $\ge x$ (mọi phần tử trong mảng đều $< x$), quy ước vị trí biên là:
   $$bien = n + 1$$
   Khi đó: $\text{so\_nho\_hon} = (n + 1) - 1 = n$.
3. Nếu mảng rỗng ($n = 0$), không có phần tử nào $\ge x$, quy ước $bien = 1$, và $\text{so\_nho\_hon} = 0$.

**Hai ví dụ chuẩn theo phiếu giao đề tài:**
* **Ví dụ 1:** $a = [1, 2, 2, 4], x = 2 \implies \text{so\_nho\_hon} = 1; bien = 2$  
  *(Giải thích: Tại vị trí thứ 2, $a[2] = 2 \ge 2$. Trước đó có 1 phần tử là $a[1] = 1 < 2$. Hai phần tử bằng 2 không được đếm).*
* **Ví dụ 2:** $a = [1, 2, 2, 4], x = 5 \implies \text{so\_nho\_hon} = 4; bien = 5$  
  *(Giải thích: Mọi phần tử đều nhỏ hơn 5; biên nằm ở sau mảng tại vị trí $n + 1 = 5$).*

---

## 3. Cấu trúc thư mục
```text
DT022/
├── src/
│   ├── DemNhoHonNhiPhan.hpp    # Định nghĩa cấu trúc dữ liệu, giải thuật chính & mở rộng
│   └── main.cpp                # Chương trình CLI chạy ví dụ, lần vết & nhập từ bàn phím
├── test/
│   └── runtests.cpp            # Bộ kiểm thử tự động 14 ca độc lập (100% PASS)
├── docs/
│   └── anh_ket_qua/            # Thư mục lưu 11 ảnh minh chứng kết quả A01 - A11
├── web/                        # Ứng dụng Web mô phỏng trực quan thuật toán (Visualizer)
│   ├── index.html
│   ├── style.css
│   └── app.js
├── build_and_run.ps1           # Script PowerShell tự động biên dịch và chạy kiểm thử
├── chay_chup_anh.bat           # File thực thi hỗ trợ chụp 11 ảnh A01 - A11
├── chay_chup_anh.ps1           # Script PowerShell điều phối chụp ảnh
├── N24DCDT059_DT022_NgoLeTanNhan_ThongTinNop.txt # Phiếu thông tin nộp bài
└── README.md                   # Hướng dẫn chi tiết biên dịch & chạy
```

---

## 4. Hướng dẫn biên dịch và chạy

### 4.1. Yêu cầu môi trường
* Trình biên dịch C++ hỗ trợ C++14 trở lên (`g++`, `clang++`, hoặc `MSVC`).
* Khuyến nghị dùng MinGW-w64 (`g++ 14.2.0` hoặc tương đương).

### 4.2. Lệnh biên dịch nhanh

#### Biên dịch chương trình chính (CLI):
```bash
g++ -O2 -static -std=c++14 src/main.cpp -o main.exe
```

#### Biên dịch bộ kiểm thử tự động (Test suite):
```bash
g++ -O2 -static -std=c++14 test/runtests.cpp -o test/runtests.exe
```

---

### 4.3. Các lệnh thực thi

1. **Chạy Ví dụ 1 đề bài:**
   ```bash
   ./main.exe --vd1
   ```
   *Kết quả mong đợi:* `so_nho_hon=1; bien=2`

2. **Chạy Ví dụ 2 đề bài:**
   ```bash
   ./main.exe --vd2
   ```
   *Kết quả mong đợi:* `so_nho_hon=4; bien=5`

3. **Chế độ tương tác & nhập từ bàn phím:**
   ```bash
   ./main.exe
   ```
   *Bao gồm các tùy chọn:*
   - Lựa chọn 1 & 2: Chạy ví dụ đề bài
   - Lựa chọn 3: Nhập $n$, mảng $a$ và khóa $x$ tùy ý, hiển thị bảng lần vết chi tiết
   - Lựa chọn 4: Phân tích mở rộng $(< x$ vs $\le x$ vs $= x$)
   - Lựa chọn 5: Khảo sát thực nghiệm thời gian và số phép so sánh $O(\log n)$ vs $O(n)$ trên các quy mô $n = 5, 50, 500, 5000$

4. **Chạy toàn bộ 14 ca kiểm thử độc lập:**
   ```bash
   ./test/runtests.exe
   ```

5. **Trải nghiệm ứng dụng Web Visualizer trực quan:**
   Mở tệp `web/index.html` trực tiếp trên trình duyệt web (Google Chrome, Edge, Firefox, ...).

---

## 5. Tóm tắt kết quả kiểm thử (14 ca độc lập)
* **Tổng số ca kiểm thử:** 14 ca (vượt chuẩn tối thiểu 12 ca)
* **Số ca đạt:** 14/14 ca (100% PASS)
* **Bao quát đầy đủ các tiêu chí A01 – A08:**
  - **A01, A02:** Ví dụ 1 và Ví dụ 2 phiếu giao (TC01, TC02)
  - **A05, A06:** Các ca biên bắt buộc: $x < \min$ (TC03), toàn phần tử trùng $x$ (TC04), mảng rỗng (TC05), đơn phần tử (TC06, TC07, TC08)
  - **A03, A04:** Các ca sinh viên tự thiết kế: mảng có số âm và 0 (TC09), khóa trùng kéo dài ở giữa và hai biên (TC10)
  - **A07:** Ca quy mô cực đại $n = 10000$ và khảo sát thực nghiệm số bước lặp $\le \lfloor\log_2 n\rfloor + 1$ (TC11)
  - **A08:** Phản hồi từ chối đầu vào không hợp lệ của Validator khi mảng chưa sắp xếp hoặc $n > 10000$ (TC12, TC13)
  - **Mở rộng:** Phân tích đồng thời bất đẳng thức nghiêm $(< x)$ và không nghiêm $(\le x)$, đếm số lần xuất hiện của $x$ (TC14)

---

## 6. Phân tích độ phức tạp thuật toán
| Thuật toán | Độ phức tạp thời gian (Tốt nhất) | Độ phức tạp thời gian (Xấu nhất) | Không gian bộ nhớ phụ |
|---|---|---|---|
| **Tìm kiếm nhị phân (Đề tài)** | $O(1)$ | $O(\log n)$ | $O(1)$ |
| **Quét tuần tự (Đối chiếu)** | $O(1)$ | $O(n)$ | $O(1)$ |

*Tại quy mô $n = 10000$, tìm kiếm nhị phân chỉ cần tối đa 14 lần xét `mid`, trong khi duyệt tuần tự có thể cần tới 10000 lần so sánh (nhanh hơn gấp hàng trăm lần).*
