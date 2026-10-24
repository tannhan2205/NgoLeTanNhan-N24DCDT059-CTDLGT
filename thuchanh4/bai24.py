class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None
        self.h = 1

def height(g):
    return 0 if g is None else g.h

def update(g):
    g.h = 1 + max(height(g.left), height(g.right))

def rotate_right(y):
    x = y.left
    middle = x.right
    x.right = y
    y.left = middle
    update(y)
    update(x)
    return x

def rotate_left(x):
    y = x.right
    middle = y.left
    y.left = x
    x.right = middle
    update(x)
    update(y)
    return y

def insert_avl(g, value):
    if g is None:
        return Node(value)
    if value < g.value:
        g.left = insert_avl(g.left, value)
    elif value > g.value:
        g.right = insert_avl(g.right, value)
    else:
        return g
    update(g)
    b = height(g.left) - height(g.right)
    if b > 1 and value < g.left.value:
        return rotate_right(g)
    if b < -1 and value > g.right.value:
        return rotate_left(g)
    if b > 1 and value > g.left.value:      # Trái–Phải
        g.left = rotate_left(g.left)
        return rotate_right(g)
    if b < -1 and value < g.right.value:    # Phải–Trái
        g.right = rotate_right(g.right)
        return rotate_left(g)
    return g

def pre(g): return [] if g is None else [g.value]+pre(g.left)+pre(g.right)
def ino(g): return [] if g is None else ino(g.left)+[g.value]+ino(g.right)
def bf(g): return 0 if g is None else height(g.left)-height(g.right)
def allbf(g): return [] if g is None else allbf(g.left)+[bf(g)]+allbf(g.right)

root = None
for value in [10, 20, 30, 40, 50, 25]:
    root = insert_avl(root, value)
    print('Chèn', value, '| gốc', root.value, '| cao', root.h, '| trước', pre(root), '| giữa', ino(root), '| bf', allbf(root))
r=None
for v in [30,10,20]: r=insert_avl(r,v)
print('[30,10,20] ->', pre(r), r.h)
