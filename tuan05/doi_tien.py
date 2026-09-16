def greedy_coin_change(coins, S):
    coins = sorted(coins, reverse=True)
    res = []
    rem = S
    for c in coins:
        while rem >= c:
            res.append(c)
            rem -= c
    return len(res), res

def dp_coin_change(coins, S):
    dp = [float('inf')] * (S + 1)
    last_coin = [-1] * (S + 1)
    dp[0] = 0

    for i in range(1, S + 1):
        for c in coins:
            if i >= c and dp[i - c] + 1 < dp[i]:
                dp[i] = dp[i - c] + 1
                last_coin[i] = c

    res = []
    curr = S
    while curr > 0:
        c = last_coin[curr]
        res.append(c)
        curr -= c
    return dp[S], res

test_cases = [
    ([1, 4, 6, 9], 12),
    ([1, 5, 10, 20, 50], 85),
    ([1, 3, 7, 12], 20),
    ([1, 2, 5, 10], 38),
    ([1, 6, 10], 12),
    ([1, 4, 5, 15, 20], 23)
]

for idx, (coins, S) in enumerate(test_cases, 1):
    g_cnt, g_coins = greedy_coin_change(coins, S)
    dp_cnt, dp_coins = dp_coin_change(coins, S)
    is_correct = "Đúng" if g_cnt == dp_cnt else "Sai"
    
    print(f"Bộ {idx}:")
    print(f"  Tham lam ({g_cnt} tờ): {' + '.join(map(str, g_coins))}")
    print(f"  Tối ưu   ({dp_cnt} tờ): {' + '.join(map(str, dp_coins))}")
    print(f"  Tham lam đúng? {is_correct}\n")