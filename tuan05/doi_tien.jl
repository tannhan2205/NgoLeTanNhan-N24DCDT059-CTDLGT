function greedy_coin_change(coins, S)
    sorted_coins = sort(coins, rev=true)
    res = Int[]
    rem = S
    for c in sorted_coins
        while rem >= c
            push!(res, c)
            rem -= c
        end
    end
    return length(res), res
end

function dp_coin_change(coins, S)
    dp = fill(typemax(Int) ÷ 2, S + 1)
    last_coin = fill(-1, S + 1)
    dp[1] = 0

    for i in 1:S
        for c in coins
            if i >= c && dp[i - c + 1] + 1 < dp[i + 1]
                dp[i + 1] = dp[i - c + 1] + 1
                last_coin[i + 1] = c
            end
        end
    end

    res = Int[]
    curr = S
    while curr > 0
        c = last_coin[curr + 1]
        push!(res, c)
        curr -= c
    end
    return dp[S + 1], res
end

test_cases = [
    ([1, 4, 6, 9], 12),
    ([1, 5, 10, 20, 50], 85),
    ([1, 3, 7, 12], 20),
    ([1, 2, 5, 10], 38),
    ([1, 6, 10], 12),
    ([1, 4, 5, 15, 20], 23)
]

for (idx, (coins, S)) in enumerate(test_cases)
    g_cnt, g_coins = greedy_coin_change(coins, S)
    dp_cnt, dp_coins = dp_coin_change(coins, S)
    is_correct = (g_cnt == dp_cnt) ? "Đúng" : "Sai"

    println("Bộ $idx:")
    println("  Tham lam ($g_cnt tờ): ", join(g_coins, " + "))
    println("  Tối ưu   ($dp_cnt tờ): ", join(dp_coins, " + "))
    println("  Tham lam đúng? $is_correct\n")
end