import sys

def error_exit():
    print("ERROR: invalid data")
    sys.exit(1)

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        error_exit()
    
    idx = 0
    try:
        n = int(input_data[idx])
        k = int(input_data[idx+1])
        idx += 2
    except (ValueError, IndexError):
        error_exit()
        
    if not (1 <= n <= 2000 and 1 <= k <= n):
        error_exit()
        
    if len(input_data) != 2 + 4 * n + 2:
        error_exit()
        
    points = []
    seen_ids = set()
    
    for _ in range(n):
        try:
            p_id = int(input_data[idx])
            x = int(input_data[idx+1])
            y = int(input_data[idx+2])
            label = input_data[idx+3]
            idx += 4
        except (ValueError, IndexError):
            error_exit()
            
        if not (1 <= p_id <= 1000000) or p_id in seen_ids:
            error_exit()
        seen_ids.add(p_id)
        
        if not (0 <= x <= 10 and 0 <= y <= 10):
            error_exit()
        if label not in ("A", "B"):
            error_exit()
            
        points.append({"id": p_id, "x": x, "y": y, "label": label})
        
    try:
        qx = int(input_data[idx])
        qy = int(input_data[idx+1])
    except (ValueError, IndexError):
        error_exit()
        
    if not (0 <= qx <= 10 and 0 <= qy <= 10):
        error_exit()
        
    for p in points:
        p["d2"] = (p["x"] - qx) ** 2 + (p["y"] - qy) ** 2
        
    points.sort(key=lambda p: (p["d2"], p["id"]))
    
    votes_a = 0
    votes_b = 0
    
    print(f"NEIGHBORS {k}")
    for i in range(k):
        p = points[i]
        print(f"{p['id']} {p['label']} {p['d2']}")
        if p["label"] == "A":
            votes_a += 1
        else:
            votes_b += 1
            
    print(f"VOTES A {votes_a} B {votes_b}")
    predict = "A" if votes_a >= votes_b else "B"
    print(f"PREDICT {predict}")

if __name__ == "__main__":
    main()