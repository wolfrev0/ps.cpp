M=30
def conv_mul(a,b):
	a=int(''.join(list(map(lambda x:('{:0'+str(M)+'b}').format(x), a[::-1]))),2)
	b=int(''.join(list(map(lambda x:('{:0'+str(M)+'b}').format(x), b[::-1]))),2)
	c=format(a*b,'b')[::-1]
	d=[]
	for i in range(0,len(c),M):
		d.append(int(c[i:min(i+M,len(c))][::-1],2))
	return d

def conv_cyc(a,b):
	a+=a
	b+=[0]*len(b)
	return conv_mul(a,b)