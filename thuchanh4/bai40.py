def day_xuong(a,i,n):
    while 2*i+1<n:
        c=2*i+1
        if c+1<n and a[c+1]>a[c]: c+=1
        if a[i]>=a[c]: break
        a[i],a[c]=a[c],a[i]
        i=c

def heap_sort(a):
    n=len(a)
    for i in range(n//2-1,-1,-1): day_xuong(a,i,n)
    for cuoi in range(n-1,0,-1):
        a[0],a[cuoi]=a[cuoi],a[0]
        day_xuong(a,0,cuoi)

def quick_sort(a,lo=0,hi=None):
    if hi is None: hi=len(a)-1
    if lo>=hi: return
    chot=a[hi]
    i=lo
    for j in range(lo,hi):
        if a[j]<chot:
            a[i],a[j]=a[j],a[i]
            i+=1
    a[i],a[hi]=a[hi],a[i]
    quick_sort(a,lo,i-1)
    quick_sort(a,i+1,hi)

a=[7,2,9,1,5,3,8,4]
for ham in [heap_sort,quick_sort]:
    b=a.copy(); ham(b); print(ham.__name__,b)
for ham in [heap_sort,quick_sort]:
    c=[2,2,-1,2]; ham(c); print(ham.__name__,c)
