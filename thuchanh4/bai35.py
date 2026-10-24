def truoc(g):
    stack,out=([g] if g else []),[]
    while stack:
        nut=stack.pop()
        out.append(nut[0])
        if nut[2] is not None: stack.append(nut[2])
        if nut[1] is not None: stack.append(nut[1])
    return out

def giua(g):
    stack,out=[],[]
    while g is not None or stack:
        while g is not None:
            stack.append(g)
            g=g[1]
        g=stack.pop()
        out.append(g[0])
        g=g[2]
    return out

def sau(g):
    stack,out=([(g,False)] if g else []),[]
    while stack:
        nut,da_mo=stack.pop()
        if da_mo:
            out.append(nut[0])
        else:
            stack.append((nut,True))
            if nut[2] is not None: stack.append((nut[2],False))
            if nut[1] is not None: stack.append((nut[1],False))
    return out

g=(8,(3,None,None),(10,None,None))
for ham in [truoc,giua,sau]:
    print(ham(g))
print(truoc(None),giua(None),sau(None))
h=(8,(3,(1,None,None),(6,None,None)),(10,None,None))
print(truoc(h),giua(h),sau(h))
