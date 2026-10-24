using StatsBase

# Hàm tính khoảng cách Euclidean
function euclidean_distance(a::Vector{Float64}, b::Vector{Float64})
    return sqrt(sum((a .- b) .^ 2))
end

# Hàm dự đoán nhãn bằng thuật toán KNN
function predict_knn(train_features::Vector{Vector{Float64}}, train_labels::Vector{Int}, query_point::Vector{Float64}, k::Int)
    n = length(train_features)
    distances = Vector{Tuple{Float64, Int}}(undef, n)
    
    # Step 1: Tính khoảng cách từ query_point đến từng mẫu huấn luyện
    for i in 1:n
        dist = euclidean_distance(train_features[i], query_point)
        distances[i] = (dist, train_labels[i])
    end
    
    # Step 2: Sắp xếp danh sách theo khoảng cách tăng dần
    sort!(distances, by = x -> x[1])
    
    # Step 3: Lấy nhãn của K láng giềng gần nhất
    k_nearest_labels = [distances[i][2] for i in 1:k]
    
    # Step 4: Bầu chọn đa số (Majority Voting)
    counts = countmap(k_nearest_labels)
    best_label = first(keys(counts))
    max_votes = -1
    
    for (label, count) in counts
        if count > max_votes
            max_votes = count
            best_label = label
        end
    end
    
    return best_label
end

# Chạy thử dữ liệu
train_features = [
    [1.0, 2.0],
    [1.5, 1.8],
    [5.0, 8.0],
    [6.0, 9.0],
    [1.2, 0.9],
    [5.5, 7.0]
]
train_labels = [0, 0, 1, 1, 0, 1]

query_point = [2.0, 2.5]
k = 3

predicted_label = predict_knn(train_features, train_labels, query_point, k)

println("Diem truy van: ", query_point)
println("Gia tri K: ", k)
println("Nhan du doan: ", predicted_label)