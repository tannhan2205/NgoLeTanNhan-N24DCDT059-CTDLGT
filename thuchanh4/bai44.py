def cung_cay(a,b):
    if a is None or b is None: return a is None and b is None
    if a[0]!=b[0]: return False
    return cung_cay(a[1],b[1]) and cung_cay(a[2],b[2])

def la_cay_con(g,b):
    if b is None: return True
    if g is None: return False
    return cung_cay(g,b) or la_cay_con(g[1],b) or la_cay_con(g[2],b)

a=(8,(3,None,(6,None,None)),(10,None,None))
b=(3,None,(6,None,None));c=(3,None,None)
print(la_cay_con(a,b),la_cay_con(a,c),cung_cay(None,None))
x=(2,(1,None,None),None);y=(2,None,(1,None,None))   # cùng khóa, khác hình dạng
print(cung_cay(x,y),cung_cay(x,x))
