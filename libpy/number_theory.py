def mu(x):
	if x==1:
		return 1
	p=0
	y=x
	for i in range(2, x):
		if i*i>x: break
		if y%i==0:
			y=y//i
			p+=1
			if y%i==0:
				return 0
	return 1 if p%2 else -1

def fastpow(a, p, m):
	if a==0:
		return 1
	t=fastpow(a,p//2)
	return t*t*(a if a%2 else 1)

#Multivariable Linear Deophantine:
#ax+by+cz=k
#=> gcd(a,b)w+cz=k && ax+by=gcd(a,b)w
#(extend it recursively)
def xgcd(a,b):
	if b==0:
		return (1,0,abs(a))
	x,y,g=xgcd(b,a%b)
	return (y,x-(a//b)*y,g);

def adjust_xgcd_lb(x,y,g,a,b,lbx,lby):
	if x<lbx:
		t=0
		if b>=0:
			t=(lbx-x)*g//b + int((lbx-x)*g%b!=0)
		else:
			t=(lbx-x)*g//b
		x+=t*b//g;
		y-=t*a//g;
	if y<lby:
		t=0
		if a>=0:
			t=(lby-y)*g//a + int((lby-y)*g%a!=0)
		else:
			t=(lby-y)*g//a
		x-=t*b//g;
		y+=t*a//g;
	#if x<lbx or y<lby:
	#	raise Exception;
	return (x,y);


# XGCD XGCDtoub(XGCD a, i64 ubx, i64 uby){
# 	if(0)
# 		throw "no root";
# 	return {};
# 	//return maximum a which satisfies a<ub
# }

def is_prime(n):
	if n<2:
		return False
	for i in range(n):
		if i*i>n:
			break
		if n%i==0:
			return False
	return True

def miller_rabin(n):
	return True

def factorize(n):
	x=n
	ret=[]
	for i in range(n):
		if i*i>n:
			break
		while x%i==0:
			x//=i
			ret.append(i)
	if x>1:
		ret.append(x)
	return ret