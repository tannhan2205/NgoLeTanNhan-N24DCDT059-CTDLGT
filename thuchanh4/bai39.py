def tim(g,x):
    while g is not None:
        k,trai,phai=g
        if x==k: return True
        g=trai if x<k else phai
    return False

def so_nut_di_qua(g,x):
    dem=0
    while g is not None:
        dem+=1
        k,trai,phai=g
        if x==k: break
        g=trai if x<k else phai
    return dem

bst=(1,None,(2,None,(3,None,(4,None,(5,None,None)))))
avl=(3,(2,(1,None,None),None),(4,None,(5,None,None)))
tap={1,2,3,4,5}
truy_van=[0,1,3,5,6]
print("BST:",[tim(bst,x) for x in truy_van])
print("AVL:",[tim(avl,x) for x in truy_van])
print("set:",[x in tap for x in truy_van])
print("Tìm 5 qua:",so_nut_di_qua(bst,5),"nút (BST),",so_nut_di_qua(avl,5),"nút (AVL)")
