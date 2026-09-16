Yêu cầu môi trường
Python: Python 3.8+

C++: Trình biên dịch g++ (hỗ trợ C++17 trở lên)

Julia: Julia v1.6+
HƯỚNG DẪN CHẠY CHƯƠNG TRÌNH CHI TIẾT
Mở Terminal trong VS Code (Ctrl + ~) và di chuyển vào thư mục bài tập cần chạy (Ví dụ: cd tuan05).
1. Chạy mã nguồn Python (.py)
# Chạy bài toán Viterbi & Mô hình ngôn ngữ
python viterbi.py

# Chạy bài toán Đổi tiền
python doi_tien.py

# Chạy bài toán Cái túi
python cai_tui.py

# Chạy bài toán 4 tiêu chí
python bontieuchi.py
2. Biên dịch & Chạy mã nguồn C++ (.cpp)
Bước 1: Biên dịch file .cpp thành file thực thi
g++ -std=c++17 viterbi.cpp -o viterbi
g++ -std=c++17 doi_tien.cpp -o doi_tien
g++ -std=c++17 cai_tui.cpp -o cai_tui
g++ -std=c++17 bontieuchi.cpp -o bontieuchi
Bước 2: Chạy file đã biên dịch
Trên Windows (PowerShell / CMD / VS Code Terminal):
.\viterbi.exe
.\doi_tien.exe
.\cai_tui.exe
.\bontieuchi.exe
Trên macOS / Linux:
./viterbi
./doi_tien
./cai_tui
./bontieuchi
3. Chạy mã nguồn Julia (.jl)
Chạy trực tiếp file script Julia:
# Chạy bài toán Viterbi & Mô hình ngôn ngữ
julia viterbi.jl

# Chạy bài toán Đổi tiền
julia doi_tien.jl

# Chạy bài toán Cái túi
julia cai_tui.jl

# Chạy bài toán 4 tiêu chí
julia bontieuchi.jl