#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cstdlib>
#include <climits>

using namespace std;

void error_exit() {
    cout << "ERROR: invalid data\n";
    exit(1);
}

struct Point {
    int id;
    int x, y;
    string label;
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
    if (n < 1 || n > 2000 || k != 1) error_exit();

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

        points.push_back({id, x, y, label});
    }

    int qx, qy;
    if (!parse_int(tokens[idx++], qx) || !parse_int(tokens[idx++], qy)) error_exit();
    if (qx < 0 || qx > 10 || qy < 0 || qy > 10) error_exit();

    int min_d2 = INT_MAX;
    int min_id = INT_MAX;
    Point best_point;

    for (const auto& p : points) {
        int d2 = (p.x - qx) * (p.x - qx) + (p.y - qy) * (p.y - qy);
        if (d2 < min_d2 || (d2 == min_d2 && p.id < min_id)) {
            min_d2 = d2;
            min_id = p.id;
            best_point = p;
        }
    }

    cout << "NEIGHBORS 1\n";
    cout << best_point.id << " " << best_point.label << " " << min_d2 << "\n";
    if (best_point.label == "A") {
        cout << "VOTES A 1 B 0\n";
    } else {
        cout << "VOTES A 0 B 1\n";
    }
    cout << "PREDICT " << best_point.label << "\n";

    return 0;
}