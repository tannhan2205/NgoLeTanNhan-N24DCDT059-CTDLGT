class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

def insert(g, x):
    if g is None:
        return Node(x)
    if x < g.value:
        g.left = insert(g.left, x)
    elif x > g.value:
        g.right = insert(g.right, x)
    return g

def preorder(g):
    if g is None:
        return []
    return [g.value] + preorder(g.left) + preorder(g.right)

def inorder(g):
    if g is None:
        return []
    return inorder(g.left) + [g.value] + inorder(g.right)

def height(g):
    if g is None:
        return 0
    return 1 + max(height(g.left), height(g.right))

def postorder(g):
    if g is None:
        return []
    return postorder(g.left) + postorder(g.right) + [g.value]

root = None
for x in [45, 15, 79]:
    root = insert(root, x)
print(preorder(root), inorder(root), height(root))
print(postorder(root))
print(postorder(None), height(None))
