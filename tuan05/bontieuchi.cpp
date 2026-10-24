// Bai 4.2 - Chon hoat dong: bon tieu chi tren cung mot bo du lieu
#include <bits/stdc++.h>
using namespace std;

struct Act {
    string name;
    int s, f;
};

bool compatible(const Act& a, const Act& b) {
    return b.s >= a.f || a.s >= b.f;
}

bool compatibleWithAll(const Act& a, const vector<Act>& chosen) {
    for (const auto& c : chosen)
        if (!compatible(a, c)) return false;
    return true;
}

vector<Act> greedy(vector<Act> order) {
    vector<Act> chosen;
    for (const auto& a : order)
        if (compatibleWithAll(a, chosen)) chosen.push_back(a);
    return chosen;
}

void show(const string& label, const vector<Act>& chosen) {
    cout << left << setw(22) << label << " -> " << setw(2) << right << chosen.size() << " hoat dong: ";
    for (size_t i = 0; i < chosen.size(); ++i) {
        cout << chosen[i].name;
        if (i + 1 < chosen.size()) cout << ", ";
    }
    cout << "\n";
}

int main() {
    vector<Act> activities = {
        {"H1", 1, 5}, {"H2", 2, 5}, {"H3", 2, 6}, {"H4", 3, 4}, {"H5", 4, 8},
        {"H6", 6, 9}, {"H7", 8, 11}, {"H8", 9, 14}, {"H9", 11, 13}, {"H10", 12, 15}
    };
    int n = activities.size();

    // Tieu chi 1: Ket thuc som nhat
    auto order1 = activities;
    sort(order1.begin(), order1.end(), [](const Act& a, const Act& b){ return a.f < b.f; });
    auto r1 = greedy(order1);

    // Tieu chi 2: Bat dau som nhat
    auto order2 = activities;
    sort(order2.begin(), order2.end(), [](const Act& a, const Act& b){ return a.s < b.s; });
    auto r2 = greedy(order2);

    // Tieu chi 3: Ngan nhat
    auto order3 = activities;
    sort(order3.begin(), order3.end(), [](const Act& a, const Act& b){ return (a.f - a.s) < (b.f - b.s); });
    auto r3 = greedy(order3);

    // Tieu chi 4: Chong lan voi it hoat dong khac nhat
    map<string,int> conflictCount;
    for (auto& a : activities) {
        int cnt = 0;
        for (auto& b : activities)
            if (a.name != b.name && !compatible(a, b)) cnt++;
        conflictCount[a.name] = cnt;
    }
    auto order4 = activities;
    sort(order4.begin(), order4.end(), [&](const Act& a, const Act& b){
        return conflictCount[a.name] < conflictCount[b.name];
    });
    auto r4 = greedy(order4);

    cout << "=== Bon tieu chi tham lam ===\n";
    show("1. Ket thuc som nhat", r1);
    show("2. Bat dau som nhat", r2);
    show("3. Ngan nhat", r3);
    show("4. It chong lan nhat", r4);

    // Chuong trinh tim so hoat dong nhieu nhat that su (vet can toan bo tap con)
    vector<Act> best;
    for (int mask = 0; mask < (1 << n); ++mask) {
        vector<Act> subset;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i)) subset.push_back(activities[i]);
        bool ok = true;
        for (size_t i = 0; i < subset.size() && ok; ++i)
            for (size_t j = i + 1; j < subset.size() && ok; ++j)
                if (!compatible(subset[i], subset[j])) ok = false;
        if (ok && subset.size() > best.size()) best = subset;
    }

    cout << "\n=== Ket qua toi uu that su (vet can) ===\n";
    show("Toi uu (brute force)", best);
    return 0;
}