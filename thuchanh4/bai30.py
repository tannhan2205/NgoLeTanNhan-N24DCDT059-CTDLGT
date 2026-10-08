def la_bst(g,lo=None,hi=None):
    if g is None: return True
    x,trai,phai=g
    if lo is not None and x<=lo: return False
    if hi is not None and x>=hi: return False
    return la_bst(trai,lo,x) and la_bst(phai,x,hi)

dung=(4,(2,(1,None,None),(3,None,None)),(6,None,None))
sai=(50,(30,None,(60,None,None)),(70,None,None))
# cây sai nhưng mọi cặp cha-con đều đúng thứ tự: 12 > 5 nhưng 12 lại nằm bên trái 10
sai2=(10,(5,None,(12,None,None)),(15,None,None))
print(la_bst(dung),la_bst(sai))
print(la_bst(sai2),la_bst(None))
