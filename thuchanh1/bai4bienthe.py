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
        
    if not (1 <= n <= 2000 and k == 1):
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
        
    min_d2 = float('inf')
    min_id = float('inf')
    best_point = None
    
    for p in points:
        d2 = (p["x"] - qx) ** 2 + (p["y"] - qy) ** 2
        if d2 < min_d2 or (d2 == min_d2 and p["id"] < min_id):
            min_d2 = d2
            min_id = p["id"]
            best_point = p
            
    print("NEIGHBORS 1")
    print(f"{best_point['id']} {best_point['label']} {min_d2}")
    if best_point["label"] == "A":
        print("VOTES A 1 B 0")
    else:
        print("VOTES A 0 B 1")
    print(f"PREDICT {best_point['label']}")

if __name__ == "__main__":
    main()