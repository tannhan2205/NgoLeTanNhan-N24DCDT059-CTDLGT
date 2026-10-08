class Nut:
    def __init__(self,x,trai=None,phai=None):
        self.gt,self.trai,self.phai=x,trai,phai

def tim(g,x):
    while g is not None:
        if g.gt==x: return g
        g=g.trai if x<g.gt else g.phai
    return None

def co(g,x):
    return g is not None and (g is x or co(g.trai,x) or co(g.phai,x))

def lca_bst(g,x,y):
    if tim(g,x) is None or tim(g,y) is None: return None
    while g is not None:
        if x<g.gt and y<g.gt: g=g.trai
        elif x>g.gt and y>g.gt: g=g.phai
        else: return g
    return None

def lca_chung(g,x,y):
    if not co(g,x) or not co(g,y): return None
    def di(u):
        if u is None: return None
        if u is x or u is y: return u
        l,r=di(u.trai),di(u.phai)
        if l is not None and r is not None: return u
        return l if l is not None else r
    return di(g)

mot,sau=Nut(1),Nut(6)
ba=Nut(3,mot,sau);g=Nut(8,ba,Nut(10))
print(lca_bst(g,1,6).gt,lca_chung(g,ba,sau).gt)
print(lca_bst(g,1,10).gt,lca_chung(g,mot,g.phai).gt)
print(lca_bst(g,1,99),lca_chung(g,mot,Nut(99)))
