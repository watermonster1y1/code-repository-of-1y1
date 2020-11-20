#include <cstdio>

using namespace std;

#define il inline
#define re register

typedef long long ll;

const int N=1e5+10;

namespace FastIO
{
char buf[1<<21],buf2[1<<21],*p1=buf,*p2=buf;
int p4,p3=-1;
il int getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
il void flush(){fwrite(buf2,1,p3+1,stdout),p3=-1;}
#define isdigit(ch) (ch>=48&&ch<=57)
template <typename T>
il void read(T &x)
{
    re bool f=0;x=0;re char ch=getc();
    while(!isdigit(ch)) f|=(ch=='-'),ch=getc();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getc();
    x=f?-x:x;
}
template <typename T>
il void print(T x)
{
    if(p3>(1<<20)) flush();
    if(x<0) buf2[++p3]=45,x=-x;
    re int a[50]={};
    do{a[++p4]=x%10+48;}while(x/=10);
    do{buf2[++p3]=a[p4];}while(--p4);
	buf2[++p3]='\n';
}
}
using namespace FastIO;

int n,m;
ll mod;

ll lz1[N<<2],lz2[N<<2];
ll sum[N<<2];
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define pushup(x) (sum[x]=(sum[ls(x)]+sum[rs(x)])%mod)
il void pushdown(int p,int l,int r)
{
	re int mid=(l+r)>>1;
	sum[ls(p)]*=lz2[p]%mod;sum[ls(p)]%=mod;
	sum[ls(p)]+=(mid-l+1)*lz1[p]%mod;sum[ls(p)]%=mod;
	sum[rs(p)]*=lz2[p]%mod;sum[rs(p)]%=mod;
	sum[rs(p)]+=(r-mid)*lz1[p]%mod;sum[rs(p)]%=mod;
	lz2[ls(p)]*=lz2[p]%mod;lz2[ls(p)]%=mod;
	lz2[rs(p)]*=lz2[p]%mod;lz2[rs(p)]%=mod;
	lz1[ls(p)]*=lz2[p]%mod;lz1[ls(p)]%=mod;
	lz1[rs(p)]*=lz2[p]%mod;lz1[rs(p)]%=mod;
	lz1[ls(p)]+=lz1[p]%mod;lz1[ls(p)]%=mod;
	lz1[rs(p)]+=lz1[p]%mod;lz1[rs(p)]%=mod;
	lz1[p]=0;lz2[p]=1;
	return;
}
il void build(int p,int l,int r)
{
	lz1[p]=0;lz2[p]=1;
	if(l==r){read(sum[p]);return;}
	re int mid=(l+r)>>1;
	build(ls(p),l,mid);
	build(rs(p),mid+1,r);
	pushup(p);return;
}
il void modify1(int p,int l,int r,int L,int R,ll x)
{
	if(l>R||r<L) return;
	if(l>=L&&r<=R)
	{
		lz1[p]+=x;lz1[p]%=mod;
		sum[p]+=(r-l+1)*x%mod;
		sum[p]%=mod;return;
	}
	pushdown(p,l,r);re int mid=(l+r)>>1;
	modify1(ls(p),l,mid,L,R,x);
	modify1(rs(p),mid+1,r,L,R,x);
	pushup(p);return;
}
il void modify2(int p,int l,int r,int L,int R,ll x)
{
	if(l>R||r<L) return;
	if(l>=L&&r<=R)
	{
		lz1[p]*=x;lz1[p]%=mod;
		lz2[p]*=x;lz2[p]%=mod;
		sum[p]*=x;sum[p]%=mod;
		return;
	}
	pushdown(p,l,r);re int mid=(l+r)>>1;
	modify2(ls(p),l,mid,L,R,x);
	modify2(rs(p),mid+1,r,L,R,x);
	pushup(p);return;
}
il int query(int p,int l,int r,int L,int R)
{
	if(l>R||r<L) return 0;
	if(l>=L&&r<=R) return sum[p];
	pushdown(p,l,r);re int mid=(l+r)>>1;
	return (query(ls(p),l,mid,L,R)+query(rs(p),mid+1,r,L,R))%mod;
}
il void prt()
{
	for(re int i=1;i<=n;++i)
		printf("%d ",query(1,1,n,i,i));
	puts("");return;
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	read(n),read(m),read(mod);
	build(1,1,n);re int opt,l,r,x;
	while(m--)
	{
		read(opt);read(l);read(r);
		if(opt==1) read(x),modify2(1,1,n,l,r,x);
		if(opt==2) read(x),modify1(1,1,n,l,r,x);
		if(opt==3) print(query(1,1,n,l,r));
	}
    flush();return 0;
}
