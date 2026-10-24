def solve(a, x, test_num):
    print(f"=== TEST CASE {test_num} ===")
    print(f"Array: {a}, x = {x}")

    n = len(a)
    if n == 0:
        print("FIRST -1\nCOUNT 0\nLOWER 0\nUPPER 0\nPROBES 0\n")
        return

    # Kiểm tra tính chất không giảm
    for i in range(n - 1):
        if a[i] > a[i + 1]:
            print("ERROR: array must be sorted\n")
            return

    # lower_bound
    low, high = 0, n
    probes_lower = 0
    while low < high:
        mid = (low + high) // 2
        probes_lower += 1
        if a[mid] >= x:
            high = mid
        else:
            low = mid + 1
    lower = low

    # upper_bound
    low, high = 0, n
    probes_upper = 0
    while low < high:
        mid = (low + high) // 2
        probes_upper += 1
        if a[mid] > x:
            high = mid
        else:
            low = mid + 1
    upper = low

    count = upper - lower
    first = lower if count > 0 else -1
    probes = probes_lower + probes_upper

    print(f"FIRST {first}")
    print(f"COUNT {count}")
    print(f"LOWER {lower}")
    print(f"UPPER {upper}")
    print(f"PROBES {probes}\n")


def main():
    tests = [
        ([1, 2, 2, 5, 7, 9], 2),
        ([], 2),
        ([2, 2, 2], 2),
        ([1, 2, 2, 5, 7, 9], 4),
        ([1, 2, 2, 5, 7, 9], 0),
        ([1, 2, 2, 5, 7, 9], 10),
        ([7, 2, 5, 2, 9, 1], 2)
    ]

    for idx, (a, x) in enumerate(tests, 1):
        solve(a, x, idx)

if __name__ == "__main__":
    main()