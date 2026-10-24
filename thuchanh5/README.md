# Thực hành Cấu trúc dữ liệu và giải thuật – Julia

## 1. Giới thiệu

Dự án thực hành học phần **Cấu trúc dữ liệu và giải thuật (CTDL & GT)**, sử dụng ngôn ngữ **Julia** để xây dựng chương trình điều phối giao đơn dựa trên dữ liệu bản đồ.

Chương trình xử lý dữ liệu đơn hàng và bản đồ từ các tệp CSV, sắp xếp và tra cứu đơn hàng, tìm đường đi ngắn nhất, lựa chọn đơn trong giới hạn thời gian, quản lý trạng thái giao hàng và xuất kết quả.

## 2. Cấu trúc thư mục

```text
thuchanh5/
├── data/
│   ├── MINI001/
│   │   ├── ban_do.csv
│   │   ├── don_hang.csv
│   │   └── ket_qua.csv
│   └── N24DCDT059/
│       ├── ban_do.csv
│       ├── don_hang.csv
│       └── ket_qua.csv
├── TH_2026_10_09_Kiem_thu.jl
├── TH_2026_10_09_Log_giai.jl
├── TH_2026_10_09_Pluto.jl
├── TH_2026_10_09_Sinh_vien.jl
└── README.md
```

### Ý nghĩa các tệp

- `TH_2026_10_09_Sinh_vien.jl`: chương trình Julia chính để chạy bài thực hành.
- `TH_2026_10_09_Kiem_thu.jl`: các bài kiểm thử cho chương trình.
- `TH_2026_10_09_Log_giai.jl`: tệp log/ghi nhận lời giải.
- `TH_2026_10_09_Pluto.jl`: tệp Julia dùng cho phần trình bày/notebook Pluto.
- `ban_do.csv`: dữ liệu các cạnh của bản đồ.
- `don_hang.csv`: dữ liệu đơn hàng.
- `ket_qua.csv`: dữ liệu kết quả được chương trình xuất ra.

Thư mục `MINI001` chứa bộ dữ liệu mẫu nhỏ để kiểm tra. Thư mục `N24DCDT059` chứa bộ dữ liệu theo mã sinh viên.

## 3. Nội dung đã thực hiện

Các thuật toán và cấu trúc dữ liệu chính trong bài gồm:

- **Merge sort**: sắp xếp danh mục đơn hàng theo mã và sắp xếp thứ tự ưu tiên.
- **Binary search**: tìm đơn hàng theo mã trên danh mục đã được sắp xếp.
- **BFS (Breadth-First Search)**: tìm đường đi ngắn nhất trên đồ thị không trọng số.
- **Quy hoạch động – Knapsack 0/1**: chọn tập đơn hàng có tổng lợi ích lớn nhất mà không vượt quá ngân sách thời gian.
- **Cấu trúc dữ liệu quản lý giao hàng**: sử dụng hàng đợi FIFO cho các đơn chờ giao, ngăn xếp để lưu lịch sử giao và hỗ trợ hoàn tác, cùng các cấu trúc tra cứu được cung cấp trong chương trình.
- **Đọc/ghi CSV**: đọc dữ liệu đầu vào và xuất trạng thái, kết quả xử lý.

Luồng xử lý tổng quát:

```text
Đọc CSV
   ↓
Chuẩn hóa và sắp xếp danh mục đơn hàng
   ↓
Tra cứu đơn hàng
   ↓
BFS tìm đường đi và tính thời gian giao
   ↓
Knapsack 0/1 chọn đơn theo ngân sách
   ↓
Quản lý giao hàng / hoàn tác
   ↓
Xuất kết quả ra CSV
```

## 4. Yêu cầu

- Đã cài đặt **Julia** và có thể chạy lệnh `julia` từ terminal/command prompt.
- Mở terminal tại thư mục chứa các tệp `.jl`.
- Các thao tác CSV trong bài sử dụng Julia Base; theo tài liệu bài thực hành, không cần cài thêm thư viện CSV riêng.

Kiểm tra Julia đã được cài đặt:

```bash
julia --version
```

## 5. Cách chạy

### Chạy với bộ dữ liệu mẫu

Tạo/đọc dữ liệu mẫu:

```bash
julia TH_2026_10_09_Sinh_vien.jl --data
```

Chạy kiểm thử phần dữ liệu:

```bash
julia TH_2026_10_09_Kiem_thu.jl --phase=data
```

### Chạy với bộ dữ liệu theo mã sinh viên

Ví dụ với thư mục dữ liệu `N24DCDT059`:

```bash
julia TH_2026_10_09_Sinh_vien.jl N24DCDT059 --data
```

Sau khi dữ liệu đã sẵn sàng, có thể chạy chế độ demo hoặc menu theo các tham số chương trình hỗ trợ:

```bash
julia TH_2026_10_09_Sinh_vien.jl N24DCDT059 --demo
julia TH_2026_10_09_Sinh_vien.jl N24DCDT059 --menu
```

### Chạy kiểm thử

Có thể chạy từng nhóm kiểm thử theo pha:

```bash
julia TH_2026_10_09_Kiem_thu.jl --phase=sort
julia TH_2026_10_09_Kiem_thu.jl --phase=search
julia TH_2026_10_09_Kiem_thu.jl --phase=bfs
julia TH_2026_10_09_Kiem_thu.jl --phase=dp
julia TH_2026_10_09_Kiem_thu.jl --phase=app
julia TH_2026_10_09_Kiem_thu.jl --phase=all
```

Nên chạy kiểm thử sau khi thay đổi mã nguồn và trước khi nộp bài. Chỉ ghi nhận một pha đã đạt khi đã chạy thực tế và kết quả kiểm thử xác nhận đạt.

## 6. Kết quả mẫu

Với bộ dữ liệu mẫu `MINI001`, theo đề bài:

- Khoảng cách BFS từ đỉnh 1 đến các đỉnh 1–6 là `[0, 1, 1, 2, 2, 3]`.
- Thời gian thực hiện ba đơn lần lượt là `[3, 5, 7]`.
- Với ngân sách thời gian `B = 8`, phương án tối ưu chọn đơn hàng có ID `1` và `2`, tổng thời gian `8` và tổng lợi ích `14`.
- Khi giao đơn ID `1`, tổng thời gian đã dùng là `3`, lợi ích nhận được là `6`. Nếu hoàn tác ngay, trạng thái được khôi phục và đơn được đưa lại vào đầu hàng đợi.

Các giá trị trên là kết quả mẫu theo bộ dữ liệu của bài thực hành; kết quả khi chạy bộ dữ liệu khác có thể khác.

## 7. Ghi chú

- `binary_search` yêu cầu danh mục được sắp xếp theo mã đơn hàng tăng dần.
- BFS tìm đường đi ngắn nhất theo số cạnh khi đồ thị không trọng số.
- Chi phí/thời gian giao được tính từ khoảng cách trên bản đồ và thời gian phục vụ của đơn.
- Knapsack 0/1 chọn tập đơn theo tổng lợi ích với ràng buộc ngân sách; thứ tự ưu tiên giao và tập đơn được chọn là hai việc khác nhau.
- Khi nộp bài, nên đưa mã nguồn, dữ liệu cần thiết, kết quả kiểm thử và notebook/trình bày lên GitHub; bổ sung URL repository và commit tương ứng nếu được yêu cầu.

---
**Học phần:** Cấu trúc dữ liệu và giải thuật  
**Ngôn ngữ:** Julia  
**Ngày thực hành:** 09/10/2026
