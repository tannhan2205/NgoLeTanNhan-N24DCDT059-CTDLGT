def nho_nhat(g):
    if g is None: return None
    while g[1] is not None:
        g=g[1]
    return g[0]

def lon_nhat(g):
    if g is None: return None
    while g[2] is not None:
        g=g[2]
    return g[0]

g=(8,(3,(1,None,None),None),(10,None,(14,None,None)))
print(nho_nhat(g),lon_nhat(g),nho_nhat(None))
la=(-7,None,None)
print(nho_nhat(la),lon_nhat(la))
# cây không phải BST: gốc 5, trái 9, phải 1
khong_bst=(5,(9,None,None),(1,None,None))
print(nho_nhat(khong_bst),lon_nhat(khong_bst))
