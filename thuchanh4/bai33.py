def tong_nut(g):
    if g is None: return 0
    x,trai,phai=g
    return x+tong_nut(trai)+tong_nut(phai)

def tong_la(g):
    if g is None: return 0
    x,trai,phai=g
    if trai is None and phai is None: return x
    return tong_la(trai)+tong_la(phai)

g=(5,(-2,None,None),(9,(0,None,None),None))
print(tong_nut(g),tong_la(g))
print(tong_nut((-7,None,None)),tong_la((-7,None,None)))
h=(-5,(3,None,None),(4,None,None))     # nút trong âm
print(tong_nut(h),tong_la(h))
