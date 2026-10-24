def in_cay(g):
    dong=[]
    def ve(nut,sau):
        if nut is None: return
        x,trai,phai=nut
        dong.append(" "*(4*sau)+str(x))
        ve(trai,sau+1)
        ve(phai,sau+1)
    ve(g,0)
    return "\n".join(dong)

g=(8,(3,None,(6,None,None)),(10,None,None))
print(in_cay(g))
print(repr(in_cay(None)))
