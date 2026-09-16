#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct TestCase {
    vector<int> coins;
    int S;
};

pair<int, vector<int>> greedyCoinChange(vector<int> coins, int S) {
    sort(coins.rbegin(), coins.rend());
    vector<int> res;
    int rem = S;
    for (int c : coins) {
        while (rem >= c) {
            res.push_back(c);
            rem -= c;
        }
    }
    return {res.size(), res};
}

pair<int, vector<int>> dpCoinChange(const vector<int>& coins, int S) {
    const int INF = 1e9;
    vector<int> dp(S + 1, INF);
    vector<int> last_coin(S + 1, -1);
    dp[0] = 0;

    for (int i = 1; i <= S; ++i) {
        for (int c : coins) {
            if (i >= c && dp[i - c] + 1 < dp[i]) {
                dp[i] = dp[i - c] + 1;
                last_coin[i] = c;
            }
        }
    }

    vector<int> res;
    int curr = S;
    while (curr > 0) {
        int c = last_coin[curr];
        res.push_back(c);
        curr -= c;
    }
    return {dp[S], res};
}

string joinCoins(const vector<int>& coins) {
    string s = "";
    for (size_t i = 0; i < coins.size(); ++i) {
        s += to_string(coins[i]);
        if (i + 1 < coins.size()) s += " + ";
    }
    return s;
}

int main() {
    vector<TestCase> tests = {
        {{1, 4, 6, 9}, 12},
        {{1, 5, 10, 20, 50}, 85},
        {{1, 3, 7, 12}, 20},
        {{1, 2, 5, 10}, 38},
        {{1, 6, 10}, 12},
        {{1, 4, 5, 15, 20}, 23}
    };

    for (size_t i = 0; i < tests.size(); ++i) {
        auto [g_cnt, g_coins] = greedyCoinChange(tests[i].coins, tests[i].S);
        auto [dp_cnt, dp_coins] = dpCoinChange(tests[i].coins, tests[i].S);
        string is_correct = (g_cnt == dp_cnt) ? "Dung" : "Sai";

        cout << "Bo " << i + 1 << ":\n";
        cout << "  Tham lam (" << g_cnt << " to): " << joinCoins(g_coins) << "\n";
        cout << "  Toi uu   (" << dp_cnt << " to): " << joinCoins(dp_coins) << "\n";
        cout << "  Tham lam dung? " << is_correct << "\n\n";
    }
    return 0;
}