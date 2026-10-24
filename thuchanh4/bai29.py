class Nut:
    def __init__(self,gt,trai=None,phai=None):
        self.gt,self.trai,self.phai=gt,trai,phai

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
        if g.trai is None: return g.phai      # lá hoặc chỉ có con phải
        if g.phai is None: return g.trai      # chỉ có con trái
        ke_vi=g.phai                          # hai con: kế vị = nhỏ nhất bên phải
        while ke_vi.trai is not None: ke_vi=ke_vi.trai
        g.gt=ke_vi.gt
        g.phai=xoa(g.phai,ke_vi.gt)
    return g

def duyet(g,kieu):
    if g is None: return []
    t,p=duyet(g.trai,kieu),duyet(g.phai,kieu)
    if kieu=="truoc": return [g.gt]+t+p
    if kieu=="giua": return t+[g.gt]+p
    return t+p+[g.gt]

def thong_ke(g):
    if g is None: return (0,0,0)
    nt,lt,ct=thong_ke(g.trai)
    np_,lp,cp=thong_ke(g.phai)
    la=1 if (g.trai is None and g.phai is None) else lt+lp
    return (nt+np_+1,la,1+max(ct,cp))

g=Nut(4,Nut(2,Nut(1),Nut(3)),Nut(6,Nut(5),Nut(7)))
print(duyet(g,"truoc"),duyet(g,"giua"),duyet(g,"sau"))
print(duyet(g,"giua"),thong_ke(g))
for x in [1,2,4]:
    g=xoa(g,x)
    print("sau xóa",x,":",duyet(g,"giua"),thong_ke(g))
print(tim(g,5).gt,tim(g,4))
print(duyet(chen(g,6),"giua"))   # khóa trùng: không đổi
print(duyet(None,"giua"),thong_ke(None))
