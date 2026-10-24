#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

// Cấu trúc biểu diễn một điểm dữ liệu (tập đặc trưng và nhãn)
struct Sample {
    std::vector<double> features;
    int label;
};

// Cấu trúc lưu khoảng cách và chỉ số gốc của mẫu huấn luyện
struct DistanceIndex {
    double distance;
    int index;
};

// Hàm tính khoảng cách Euclidean giữa hai vector đặc trưng
double euclideanDistance(const std::vector<double>& a, const std::vector<double>& b) {
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        double diff = a[i] - b[i];
        sum += diff * diff;
    }
    return std::sqrt(sum);
}

// Hàm dự đoán nhãn phân loại bằng KNN
int predictKNN(const std::vector<Sample>& trainData, const std::vector<double>& queryPoint, int k) {
    int n = trainData.size();
    std::vector<DistanceIndex> distList(n);

    // Step 1: Tính khoảng cách từ queryPoint tới từng điểm trong tập huấn luyện
    for (int i = 0; i < n; ++i) {
        distList[i].distance = euclideanDistance(trainData[i].features, queryPoint);
        distList[i].index = i;
    }

    // Step 2: Sắp xếp danh sách chỉ số theo khoảng cách tăng dần
    std::sort(distList.begin(), distList.end(), [](const DistanceIndex& a, const DistanceIndex& b) {
        return a.distance < b.distance;
    });

    // Step 3: Đếm số lượng bầu chọn (votes) cho từng nhãn trong K láng giềng gần nhất
    std::map<int, int> labelVotes;
    for (int i = 0; i < k; ++i) {
        int neighborIndex = distList[i].index;
        int neighborLabel = trainData[neighborIndex].label;
        labelVotes[neighborLabel]++;
    }

    // Step 4: Tìm nhãn có số lượt bầu chọn cao nhất (Majority Vote)
    int bestLabel = -1;
    int maxVotes = -1;
    for (const auto& pair : labelVotes) {
        if (pair.second > maxVotes) {
            maxVotes = pair.second;
            bestLabel = pair.first;
        }
    }

    return bestLabel;
}

int main() {
    // Tập dữ liệu huấn luyện mẫu (2 đặc trưng, nhãn 0 hoặc 1)
    std::vector<Sample> trainData = {
        {{1.0, 2.0}, 0},
        {{1.5, 1.8}, 0},
        {{5.0, 8.0}, 1},
        {{6.0, 9.0}, 1},
        {{1.2, 0.9}, 0},
        {{5.5, 7.0}, 1}
    };

    // Điểm truy vấn cần dự đoán
    std::vector<double> queryPoint = {2.0, 2.5};
    int k = 3;

    int predictedLabel = predictKNN(trainData, queryPoint, k);

    std::cout << "Diem du lieu truy van: (2.0, 2.5)" << std::endl;
    std::cout << "Gia tri K = " << k << std::endl;
    std::cout << "Nhan du doan: " << predictedLabel << std::endl;

    return 0;
}