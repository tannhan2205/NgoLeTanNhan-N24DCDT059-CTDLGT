### A Pluto.jl notebook ###
# v0.20.0

# ╔═╡ 09102026-0000-4000-8000-000000000001
begin
    READ_DATA = true
    RUN_APP = true
    ROOT_DATA = joinpath(@__DIR__, "data")
end

# ╔═╡ 09102026-0000-4000-8000-000000000002
AppCore = let
    sandbox = Module(:ThucHanhNgay0910)
    Base.include(sandbox, joinpath(@__DIR__, "TH_2026_10_09_Sinh_vien.jl"))
    Base.invokelatest(getfield, sandbox, :GiaoDon)
end

# ╔═╡ 09102026-0000-4000-8000-000000000003
"""MỤC TIÊU: một luồng từ CSV đến giao đơn: đọc don_hang.csv và ban_do.csv, sắp danh mục theo ID, tra cứu theo ID, BFS tính khoảng cách và tuyến đường, tính costs[id] = 2h + phục vụ, quy hoạch động chọn đơn trong ngân sách B, nạp kế hoạch vào hàng đợi FIFO, giao hoặc hoàn tác bằng ngăn xếp, xuất CSV kết quả.

1) merge_sort(a, before)
 Ý tưởng: chia đôi, sắp từng nửa bằng đệ quy, trộn hai nửa đã có thứ tự.
 Giả mã: nếu độ dài <= 1 thì trả bản sao; sắp nửa trái và nửa phải; lặp lấy phần tử đứng trước (hòa thì lấy bên trái); chép phần còn lại.
 Điều kiện áp dụng: before so sánh nhất quán. Chi phí: O(n log n) thời gian, O(n) bộ nhớ cho vector kết quả.

2) binary_search(a, id)
 Ý tưởng: giữ đoạn [lo, hi], so sánh phần tử giữa với id rồi loại một nửa.
 Giả mã: lo = 1, hi = length(a); khi lo <= hi: mid = lo + (hi - lo) / 2; bằng thì trả Order; nhỏ hơn thì lo = mid + 1; lớn hơn thì hi = mid - 1; hết đoạn thì trả nothing.
 Điều kiện áp dụng: danh mục tăng theo ID, ID duy nhất. Chi phí: O(log n) thời gian, O(1) bộ nhớ phụ.

3) bfs_routes(graph, source)
 Ý tưởng: hàng đợi FIFO duyệt theo từng lớp khoảng cách; lần đầu tới một đỉnh là số cạnh ít nhất.
 Giả mã: distance = -1 cho mọi đỉnh, distance[nguồn] = 0, đưa nguồn vào hàng đợi; lấy u; với mỗi láng giềng v chưa tới: đặt distance[v], parent[v], đưa v vào hàng đợi; sau đó dựng đường đi bằng cách lần theo parent rồi đảo ngược.
 Điều kiện áp dụng: đồ thị không trọng số. Chi phí: O(V + E) thời gian, O(V) bộ nhớ (thêm tối đa O(V^2) nếu lưu đường đi của mọi đỉnh).

4) knapsack(orders, costs, budget)
 Ý tưởng: F(i,b) là lợi ích tốt nhất khi xét i đơn đầu với ngân sách b.
 Giả mã: F(0,b) = 0; nếu tau_i > b thì F(i,b) = F(i-1,b); ngược lại F(i,b) = max(F(i-1,b), lợi_ích_i + F(i-1, b - tau_i)); truy vết từ i = n, b = B: nếu F(i,b) khác F(i-1,b) thì chọn đơn i và trừ tau_i.
 Điều kiện áp dụng: tau và B nguyên, mỗi đơn chọn tối đa một lần. Chi phí: O(nB) thời gian và bộ nhớ, truy vết O(n)."""

# ╔═╡ 09102026-0000-4000-8000-000000000004
ho_so = AppCore.mini_profile()

# ╔═╡ 09102026-0000-4000-8000-000000000005
du_lieu = READ_DATA ? AppCore.read_data(joinpath(ROOT_DATA,"MINI001")) : nothing

# ╔═╡ 09102026-0000-4000-8000-000000000006
bao_cao = !RUN_APP || du_lieu === nothing ? nothing : let
    s = AppCore.build_session(du_lieu.orders,du_lieu.edges,ho_so)
    r = AppCore.plan!(s)
    trace = NamedTuple[]
    save(label) = push!(trace,(buoc=label,queue=AppCore.queue_values(s.pending),
                              stack=copy(s.completed),spent=s.spent,earned=s.earned))
    save("Sau lập kế hoạch")
    AppCore.deliver!(s); save("Sau giao một đơn")
    AppCore.undo!(s); save("Sau hoàn tác")
    while s.pending.count > 0
        AppCore.deliver!(s)
    end
    save("Sau giao hết")
    (chi_phi=copy(s.costs),tuyen=deepcopy(s.routes),chon=copy(s.selected_ids),
     loi_ich_toi_uu=r.optimal.value,truy_vet=trace,bat_bien=AppCore.check_invariants(s))
end

# ╔═╡ 09102026-0000-4000-8000-000000000007
"""Ô F(2,8) của bộ MINI001: F(2,8) = max(F(1,8), 8 + F(1,3)) = max(6, 8 + 6) = 14.
Không lấy đơn 2 thì giữ F(1,8) = 6. Lấy đơn 2 (tau = 5, lợi ích 8) thì còn ngân sách 3 và cộng F(1,3) = 6, được 14.
Vị trí trong Julia: F(2,8) là table[3,9]; F(1,8) là table[2,9]; F(1,3) là table[2,4] (chỉ số lệch 1 vì mảng bắt đầu từ 1).
Nhánh lấy phải dùng hàng i-1 vì hàng đó chưa xét đơn i; dùng hàng i thì đơn i có thể bị cộng nhiều lần.
Đối chiếu vét cạn: tập {1,2} cho 14 và là tối ưu; chương trình tự so DP với vét cạn trong plan!."""

# ╔═╡ 09102026-0000-4000-8000-000000000008
"""MINH CHỨNG NỘP
Lệnh kiểm thử: julia TH_2026_10_09_Kiem_thu.jl --phase=sort | search | bfs | dp | app | all, và julia TH_2026_10_09_Sinh_vien.jl --mini.
Kết quả thực tế từng pha: ........ (điền ĐẠT hoặc CHƯA ĐẠT sau khi chạy).
CSV kết quả: data/MINI001/ket_qua.csv và data/N24DCDT059/ket_qua.csv.
GitHub: ........ | Commit SHA: ........
MSSV cá nhân: N24DCDT059 (dữ liệu trong data/N24DCDT059)."""

# ╔═╡ 09102026-0000-4000-8000-000000000010
ca_nhan = !RUN_APP ? nothing : let
    loaded = AppCore.load_session("N24DCDT059"; root=ROOT_DATA)
    s = loaded.session
    r = AppCore.plan!(s)
    (ngan_sach=s.profile.budget, chon=copy(s.selected_ids), loi_ich_toi_uu=r.optimal.value,
     vet_can=r.oracle.value, tham_lam=r.greedy.value)
end

# ╔═╡ 09102026-0000-4000-8000-000000000009
if RUN_APP && bao_cao !== nothing
    println("Kết quả từ cùng lõi ứng dụng Julia:")
    show(stdout, "text/plain", bao_cao)
    println()
    println("Dữ liệu cá nhân N24DCDT059:")
    show(stdout, "text/plain", ca_nhan)
    println()
end

# ╔═╡ Cell order:
# ╠═09102026-0000-4000-8000-000000000001
# ╠═09102026-0000-4000-8000-000000000002
# ╠═09102026-0000-4000-8000-000000000003
# ╠═09102026-0000-4000-8000-000000000004
# ╠═09102026-0000-4000-8000-000000000005
# ╠═09102026-0000-4000-8000-000000000006
# ╠═09102026-0000-4000-8000-000000000007
# ╠═09102026-0000-4000-8000-000000000008
# ╠═09102026-0000-4000-8000-000000000009
# ╠═09102026-0000-4000-8000-000000000010