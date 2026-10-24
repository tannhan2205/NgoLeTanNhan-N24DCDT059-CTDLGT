import math
from collections import Counter

# Hàm tính khoảng cách Euclidean giữa hai điểm
def euclidean_distance(a, b):
    return math.sqrt(sum((x - y) ** 2 for x, y in zip(a, b)))

# Hàm dự đoán nhãn bằng thuật toán KNN
def predict_knn(train_data, query_point, k):
    distances = []
    
    # Step 1: Tính khoảng cách và lưu kèm nhãn gốc
    for sample in train_data:
        dist = euclidean_distance(sample['features'], query_point)
        distances.append((dist, sample['label']))
    
    # Step 2: Sắp xếp mảng theo khoảng cách tăng dần
    distances.sort(key=lambda x: x[0])
    
    # Step 3: Chọn K láng giềng gần nhất
    k_nearest_labels = [label for _, label in distances[:k]]
    
    # Step 4: Bầu chọn theo đa số (Majority Voting)
    most_common = Counter(k_nearest_labels).most_common(1)
    return most_common[0][0]

# Chạy thử dữ liệu
if __name__ == "__main__":
    train_data = [
        {'features': [1.0, 2.0], 'label': 0},
        {'features': [1.5, 1.8], 'label': 0},
        {'features': [5.0, 8.0], 'label': 1},
        {'features': [6.0, 9.0], 'label': 1},
        {'features': [1.2, 0.9], 'label': 0},
        {'features': [5.5, 7.0], 'label': 1}
    ]
    
    query_point = [2.0, 2.5]
    k = 3
    
    predicted_label = predict_knn(train_data, query_point, k)
    
    print(f"Điểm truy vấn: {query_point}")
    print(f"Giá trị K: {k}")
    print(f"Nhãn dự đoán: {predicted_label}")