class MinHeap:
    def __init__(self): self.a=[]
    def them(self,d,u):
        self.a.append((d,u))
        i=len(self.a)-1
        while i>0:
            cha=(i-1)//2
            if self.a[i]<self.a[cha]:
                self.a[i],self.a[cha]=self.a[cha],self.a[i]
                i=cha
            else: break
    def lay(self):
        if not self.a: raise IndexError("heap rỗng")
        goc=self.a[0]
        cuoi=self.a.pop()
        if self.a:
            self.a[0]=cuoi
            i,n=0,len(self.a)
            while 2*i+1<n:
                c=2*i+1
                if c+1<n and self.a[c+1]<self.a[c]: c+=1
                if self.a[c]<self.a[i]:
                    self.a[i],self.a[c]=self.a[c],self.a[i]
                    i=c
                else: break
        return goc

def dijkstra(g,nguon):
    d={u:float("inf") for u in g}
    d[nguon]=0
    h=MinHeap();h.them(0,nguon)
    while h.a:
        du,u=h.lay()
        if du>d[u]: continue          # bản cũ, bỏ
        for v,w in g[u]:
            if du+w<d[v]:
                d[v]=du+w
                h.them(d[v],v)
    return d

g={"A":[("B",4),("C",1)],"B":[("D",1)],
   "C":[("B",2),("D",5)],"D":[]}
print(dijkstra(g,"A"))
h=MinHeap()
for x in [4,1,3]: h.them(x,"x")
print([h.lay()[0] for _ in range(3)])
