def dem_mot_con(g):
    if g is None: return 0
    _,trai,phai=g
    a,b=trai is not None,phai is not None
    return (1 if a!=b else 0)+dem_mot_con(trai)+dem_mot_con(phai)

g=(8,(3,None,(6,None,None)),(10,None,(14,None,None)))
print(dem_mot_con(g),dem_mot_con((1,None,None)))
chuoi=(1,(2,(3,(4,None,None),None),None),None)
print(dem_mot_con(chuoi))
g0=(0,(0,None,(0,None,None)),(0,None,(0,None,None)))   # đổi hết khóa thành 0
print(dem_mot_con(g0))
