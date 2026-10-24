#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Item {
    string name;
    int w, v;
    double ratio;
};

int W = 14;
int best_val = 0;
vector<string> best_set;
int nodes_count = 0;

double upper_bound(const vector<Item>& items, int idx, int curr_w, int curr_v) {
    if (curr_w > W) return 0;
    double ub = curr_v;
    int rem_w = W - curr_w;
    for (size_t j = idx; j < items.size(); ++j) {
        if (items[j].w <= rem_w) {
            rem_w -= items[j].w;
            ub += items[j].v;
        } else {
            ub += rem_w * items[j].ratio;
            break;
        }
    }
    return ub;
}

void dfs(const vector<Item>& items, int idx, int curr_w, int curr_v, vector<string>& curr_set, bool with_pruning) {
    nodes_count++;
    if (curr_w > W) return;

    if (curr_v > best_val) {
        best_val = curr_v;
        best_set = curr_set;
    }

    if (idx == items.size()) return;

    if (with_pruning) {
        double ub = upper_bound(items, idx, curr_w, curr_v);
        if (ub <= best_val) return;
    }

    // Branch 1: Take item
    curr_set.push_back(items[idx].name);
    dfs(items, idx + 1, curr_w + items[idx].w, curr_v + items[idx].v, curr_set, with_pruning);
    curr_set.pop_back();

    // Branch 2: Skip item
    dfs(items, idx + 1, curr_w, curr_v, curr_set, with_pruning);
}

int main() {
    vector<Item> items = {
        {"A", 4, 19, 19.0/4}, {"B", 7, 25, 25.0/7}, {"C", 3, 7, 7.0/3},
        {"D", 3, 8, 8.0/3},   {"E", 3, 9, 9.0/3},   {"F", 10, 21, 21.0/10}
    };

    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio > b.ratio;
    });

    vector<string> curr_set;
    
    // Mode 1: With Pruning
    best_val = 0; nodes_count = 0;
    dfs(items, 0, 0, 0, curr_set, true);
    int nodes_pruned = nodes_count;

    // Mode 2: Without Pruning
    best_val = 0; nodes_count = 0;
    dfs(items, 0, 0, 0, curr_set, false);
    int nodes_unpruned = nodes_count;

    cout << "Gia tri lon nhat: " << best_val << endl;
    cout << "So nut CO cat nhanh: " << nodes_pruned << endl;
    cout << "So nut KHONG cat nhanh: " << nodes_unpruned << endl;

    return 0;
}