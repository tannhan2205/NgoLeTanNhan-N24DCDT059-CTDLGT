def cao(g):
    return 0 if g is None else 1+max(cao(g[1]),cao(g[2]))
def can(g):
    return 0 if g is None else cao(g[1])-cao(g[2])
def giua(g):
    return [] if g is None else giua(g[1])+[g[0]]+giua(g[2])

def quay_trai(g):
    k,t,p=g
    pk,pt,pp=p
    return (pk,(k,t,pt),pp)

def quay_phai(g):
    k,t,p=g
    tk,tt,tp=t
    return (tk,tt,(k,tp,p))

def xoa_avl(g,x):
    if g is None: return None
    k,trai,phai=g
    if x<k:
        trai=xoa_avl(trai,x)
    elif x>k:
        phai=xoa_avl(phai,x)
    else:
        if trai is None: return phai
        if phai is None: return trai
        ke=phai
        while ke[1] is not None: ke=ke[1]
        k=ke[0]
        phai=xoa_avl(phai,k)
    g=(k,trai,phai)
    b=can(g)
    if b>1:
        if can(g[1])<0:
            g=(g[0],quay_trai(g[1]),g[2])
        return quay_phai(g)
    if b<-1:
        if can(g[2])>0:
            g=(g[0],g[1],quay_phai(g[2]))
        return quay_trai(g)
    return g

g=(4,(2,(1,None,None),(3,None,None)),(5,None,None))
g2=xoa_avl(g,5)
print(giua(g2),g2[0],cao(g2))
print(g2)
print(xoa_avl(g,9)==g)
