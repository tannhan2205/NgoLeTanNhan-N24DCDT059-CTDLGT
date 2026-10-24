class Nut:
    def __init__(self,gt,trai=None,phai=None):
        self.gt,self.trai,self.phai=gt,trai,phai

def cao(g):
    return 0 if g is None else 1+max(cao(g.trai),cao(g.phai))

def chen(g,x):
    if g is None: return Nut(x)
    if x==g.gt: return g
    if x<g.gt: g.trai=chen(g.trai,x)
    else: g.phai=chen(g.phai,x)
    return g

def tim(g,x):
    while g is not None:
        if x==g.gt: return g
        g=g.trai if x<g.gt else g.phai
    return None

def xoa(g,x):
    if g is None: return None
    if x<g.gt:
        g.trai=xoa(g.trai,x)
    elif x>g.gt:
        g.phai=xoa(g.phai,x)
    else:
        if g.trai is None: return g.phai
        if g.phai is None: return g.trai
        ke=g.phai
        while ke.trai is not None: ke=ke.trai
        g.gt=ke.gt
        g.phai=xoa(g.phai,ke.gt)
    return g

def giua(g):
    if g is None: return []
    return giua(g.trai)+[g.gt]+giua(g.phai)

def quay_trai(g):
    p=g.phai
    g.phai=p.trai
    p.trai=g
    return p

def quay_phai(g):
    t=g.trai
    g.trai=t.phai
    t.phai=g
    return t

def chen_avl(g,x):
    if g is None: return Nut(x)
    if x==g.gt: return g
    if x<g.gt: g.trai=chen_avl(g.trai,x)
    else: g.phai=chen_avl(g.phai,x)
    b=cao(g.trai)-cao(g.phai)
    if b>1:
        if x>g.trai.gt:                 # TP: quay trái con trước
            g.trai=quay_trai(g.trai)
        return quay_phai(g)             # TT (hoặc sau bước trên)
    if b<-1:
        if x<g.phai.gt:                 # PT: quay phải con trước
            g.phai=quay_phai(g.phai)
        return quay_trai(g)             # PP (hoặc sau bước trên)
    return g

g=None
for x in [4,2,6,1,3,5,7]: g=chen(g,x)
print(giua(g),tim(g,5).gt,tim(g,9))
print("Sau xóa4:",giua(xoa(g,4)))
for ds in [[30,20,10],[10,20,30],[30,10,20],[10,30,20]]:
    a=None
    for x in ds: a=chen_avl(a,x)
    print(ds,"-> gốc",a.gt,"cao",cao(a),"giữa",giua(a))
