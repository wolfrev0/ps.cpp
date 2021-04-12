import math

def topow2(x):
  return 1 if x==0 else 1<<(x-1).bit_length()

def fftr(a,w):
  n=len(a)
  if n==1:
    return a
  even=[];odd=[]
  for i,x in enumerate(a):
    (even if i%2==0 else odd).append(x)
  even=fftr(even,w*w);odd=fftr(odd,w*w)
  ret=[]
  ww=1
  for i in range(n):
    ret.append(even[i%(n//2)]+ww*odd[i%(n//2)])
    ww*=w
  return ret

def fft(a):
  return fftr(a,math.e**(-2*math.pi*complex(0,1)/len(a)))

def ffti(a):
  a[1:]=reversed(a[1:])
  ret=fft(a)
  ret=[x/len(a) for x in ret]
  return ret

def conv(a,b):
  return list(map(lambda x:round(x.real), ffti([x*y for x,y in zip(fft(a), fft(b))])))

def conv_mul(a,b):
  a=list(a);b=list(b)
  n=max(len(a),len(b))
  a.extend([0]*(topow2(n*2)-n))
  b.extend([0]*(topow2(n*2)-n))
  return conv(a,b)

def conv_cir(a,b):
  a=list(a);b=list(b)
  n=max(len(a),len(b))
  a.extend([0]*(topow2(n*2)-n))
  b.reverse()
  for i in range(topow2(n*2)-n):
    b.append(b[(n+i)%n])
  b.reverse()
  return conv(a,b)[-n:]
