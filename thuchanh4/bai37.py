def khoi_phuc(truoc,giua):
    if len(truoc)!=len(giua) or set(truoc)!=set(giua):
        raise ValueError("hai dãy không tương ứng")
    if len(set(truoc))!=len(truoc):
        raise ValueError("khóa phải phân biệt")
    if not truoc: return None
    goc=truoc[0]
    p=giua.index(goc)
    trai=khoi_phuc(truoc[1:p+1],giua[:p])
    phai=khoi_phuc(truoc[p+1:],giua[p+1:])
    return (goc,trai,phai)

def sau(g):
    return [] if g is None else sau(g[1])+sau(g[2])+[g[0]]

truoc=[8,3,1,6,10];giua=[1,3,6,8,10]
cay=khoi_phuc(truoc,giua)
print(cay)
print(sau(cay))
print(khoi_phuc([],[]))
