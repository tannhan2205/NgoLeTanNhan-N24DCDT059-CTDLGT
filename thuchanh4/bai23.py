class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

def preorder(g):
    if g is None:
        return []
    return [g.value] + preorder(g.left) + preorder(g.right)
def inorder(g):
    if g is None:
        return []
    return inorder(g.left) + [g.value] + inorder(g.right)
def postorder(g):
    if g is None:
        return []
    return postorder(g.left) + postorder(g.right) + [g.value]

def build(pre, ino):
    if not pre:
        return None
    k = ino.index(pre[0])
    g = Node(pre[0])
    g.left = build(pre[1:1+k], ino[:k])
    g.right = build(pre[1+k:], ino[k+1:])
    return g

pre = [50, 30, 20, 40, 70, 60, 80]
ino = [20, 30, 40, 50, 60, 70, 80]
root = build(pre, ino)
print('Cây hiện có:', preorder(root))
print('Mục tiêu sau TODO:', pre)
print(inorder(root), postorder(root))
print(preorder(build([50,30,70],[30,50,70])), build([],[]))
