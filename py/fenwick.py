class Fenwick:
  def __init__(z,n):
    z.n=n
    z.t=[0 for i in range(n+1)]
  def pfs(z,i):
    i+=1
    a=0
    while i>0:
      a+=z.t[i]
      i-=i&-i
    return a
  def q(z,s,e):
    if s>=e:
      return 0
    return z.pfs(e-1)-z.pfs(s-1)
  def upd(z,i,d):
    i+=1
    while i<=z.n:
      z.t[i]+=d
      i+=i&-i