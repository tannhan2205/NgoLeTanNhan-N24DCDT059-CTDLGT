DATA = [["mây", "nhẹ", "có"], ["mây", "mạnh", "có"],
        ["nắng", "nhẹ", "có"], ["nắng", "mạnh", "không"]]
TREE = (0, {"mây": "có",
            "nắng": (1, {"nhẹ": "có", "mạnh": "không"})})

def predict(tree, sample):
    current = tree
    while not isinstance(current, str):
        col, branches = current
        value = sample[col]
        if value not in branches:
            raise ValueError("Thuộc tính chưa gặp: " + value)
        current = branches[value]
    return current

print(predict(TREE, ["nắng", "mạnh"]))
print(predict(TREE, ["mây", "nhẹ"]))
try:
    print(predict(TREE, ["mưa", "nhẹ"]))
except ValueError as e:
    print("Lỗi:", e)
print([predict(TREE, r[:2])==r[2] for r in DATA])
