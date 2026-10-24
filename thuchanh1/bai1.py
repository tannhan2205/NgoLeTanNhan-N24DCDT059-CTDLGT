import sys

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    n = int(input_data[0])
    
    if n == 0:
        print("SUM 0")
        print("MIN NA")
        print("MAX NA")
        print("FIRST -1")
        print("SEARCH_CMPS 0")
        print("PAIRS 0")
        print("DOUBLINGS 0")
        print("SCAN_VISITS 0")
        return
    
    A = [int(v) for v in input_data[1:n+1]]
    x = int(input_data[n+1])
    
    sum_val = 0
    min_val = A[0]
    max_val = A[0]
    scan_visits = 0
    
    for val in A:
        sum_val += val
        if val < min_val:
            min_val = val
        if val > max_val:
            max_val = val
        scan_visits += 1
        
    first_idx = -1
    search_cmps = 0
    for i in range(n):
        search_cmps += 1
        if A[i] == x:
            first_idx = i
            break
            
    pairs = 0
    for i in range(n):
        for j in range(i + 1, n):
            pairs += 1
            
    doublings = 0
    i = 1
    while i <= n:
        doublings += 1
        i *= 2
        
    print(f"SUM {sum_val}")
    print(f"MIN {min_val}")
    print(f"MAX {max_val}")
    print(f"FIRST {first_idx}")
    print(f"SEARCH_CMPS {search_cmps}")
    print(f"PAIRS {pairs}")
    print(f"DOUBLINGS {doublings}")
    print(f"SCAN_VISITS {scan_visits}")

if __name__ == "__main__":
    main()