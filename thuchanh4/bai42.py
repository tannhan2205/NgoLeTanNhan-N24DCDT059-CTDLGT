def bang_ma(s):
    freq={c:s.count(c) for c in sorted(set(s))}
    nodes=[(f,c) for c,f in freq.items()]
    if not nodes: return {}
    while len(nodes)>1:
        nodes.sort(key=lambda x:x[0])
        f1,t1=nodes.pop(0);f2,t2=nodes.pop(0)
        nodes.append((f1+f2,(t1,t2)))
    ma={}
    def ve(nut,p):
        if isinstance(nut,str): ma[nut]=p or "0";return
        ve(nut[0],p+"0")
        ve(nut[1],p+"1")
    ve(nodes[0][1],"")
    return ma

def ma_hoa(s,ma):
    bits=[]
    for c in s:
        bits.append(ma[c])
    return "".join(bits)

def giai_ma(bits,ma):
    nguoc={v:k for k,v in ma.items()}
    out=[];p=""
    for b in bits:
        p+=b
        if p in nguoc:
            out.append(nguoc[p])
            p=""
    return "".join(out)

for s in ["BANANA","AAAA"]:
    ma=bang_ma(s);bits=ma_hoa(s,ma)
    print(s,ma,bits,len(bits),giai_ma(bits,ma))
