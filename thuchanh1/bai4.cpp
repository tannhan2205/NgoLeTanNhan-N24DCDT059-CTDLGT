#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <cstdlib>

using namespace std;

void error_exit() {
    cout << "ERROR: invalid data\n";
    exit(1);
}

struct Point {
    int id;
    int x, y;
    string label;
    int d2;
};

bool parse_int(const string& s, int& val) {
    if (s.empty()) return false;
    size_t idx = 0;
    try {
        val = stoi(s, &idx);
        return idx == s.length();
    } catch (...) {
        return false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> tokens;
    string token;
    while (cin >> token) {
        tokens.push_back(token);
    }

    if (tokens.size() < 4) error_exit();

    int idx = 0;
    int n, k;
    if (!parse_int(tokens[idx++], n) || !parse_int(tokens[idx++], k)) error_exit();
    if (n < 1 || n > 2000 || k < 1 || k > n) error_exit();

    // Tổng số token cần thiết: 2 (n, k) + 4 * n (id, x, y, label) + 2 (qx, qy)
    if (tokens.size() != static_cast<size_t>(2 + 4 * n + 2)) error_exit();

    vector<Point> points;
    set<int> seen_ids;

    for (int i = 0; i < n; ++i) {
        int id, x, y;
        if (!parse_int(tokens[idx++], id)) error_exit();
        if (!parse_int(tokens[idx++], x)) error_exit();
        if (!parse_int(tokens[idx++], y)) error_exit();
        string label = tokens[idx++];

        if (id < 1 || id > 1000000 || seen_ids.count(id)) error_exit();
        seen_ids.insert(id);

        if (x < 0 || x > 10 || y < 0 || y > 10) error_exit();
        if (label != "A" && label != "B") error_exit();

        points.push_back({id, x, y, label, 0});
    }

    int qx, qy;
    if (!parse_int(tokens[idx++], qx) || !parse_int(tokens[idx++], qy)) error_exit();
    if (qx < 0 || qx > 10 || qy < 0 || qy > 10) error_exit();

    for (auto& p : points) {
        p.d2 = (p.x - qx) * (p.x - qx) + (p.y - qy) * (p.y - qy);
    }

    sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        if (a.d2 != b.d2) return a.d2 < b.d2;
        return a.id < b.id;
    });

    int votes_a = 0, votes_b = 0;
    cout << "NEIGHBORS " << k << "\n";
    for (int i = 0; i < k; ++i) {
        cout << points[i].id << " " << points[i].label << " " << points[i].d2 << "\n";
        if (points[i].label == "A") votes_a++;
        else votes_b++;
    }

    cout << "VOTES A " << votes_a << " B " << votes_b << "\n";
    string predict = (votes_a >= votes_b) ? "A" : "B";
    cout << "PREDICT " << predict << "\n";

    return 0;
}