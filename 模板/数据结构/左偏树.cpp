#include <cstdio>
#include <algorithm>

using namespace std;

#define il inline
#define re register

const int N=1e5+10;

namespace FastIO
{
char buf[1<<21],buf2[1<<21],*p1=buf,*p2=buf;
int p,p3=-1;
il int getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
il void flush(){fwrite(buf2,1,p3+1,stdout),p3=-1;}
#define isdigit(ch) (ch>=48&&ch<=57)
template <typename T>
il void read(T &x)
{
	re bool f=0;x=0;
	re char ch=getc();
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
	do{a[++p]=x%10+48;}while(x/=10);
	do{buf2[++p3]=a[p];}while(--p);
	buf2[++p3]='\n';
}
}
using namespace FastIO;

int n,m;

int fa[N],dis[N],son[2][N],w[N];
#define ls(x) (son[0][x])
#define rs(x) (son[1][x])
il int merge(int x,int y)
{
	if(!x||!y) return x|y;
	if(w[x]>w[y]||(w[x]==w[y]&&x>y)) swap(x,y);
	rs(x)=merge(rs(x),y);
	fa[rs(x)]=fa[x];
	if(dis[rs(x)]>dis[ls(x)]) swap(ls(x),rs(x));
	dis[x]=rs(x)?dis[rs(x)]+1:0;
	return x;
}
il int getanc(int x){return fa[x]=(fa[x]^x?getanc(fa[x]):x);}
il void Merge(int x,int y)
{
	if(w[x]==-1||w[y]==-1) return;
	if(getanc(x)==getanc(y)) return;
	fa[x]=fa[y]=merge(getanc(x),getanc(y));
	return;
}
il int query(int x)
{
	if(w[x]==-1) return -1;
	x=getanc(x);
	re int res=w[x];
	fa[ls(x)]=ls(x);
	fa[rs(x)]=rs(x);
	w[x]=-1;fa[x]=merge(ls(x),rs(x));
	return res;
}

int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	read(n);read(m);
	for(re int i=1;i<=n;++i) read(w[i]);
	for(re int i=1;i<=n;++i) fa[i]=i;
	re int opt,x,y;
	while(m--)
	{
		read(opt);read(x);
		if(opt==1) read(y),Merge(x,y);
		else print(query(x));
	}
	flush();return 0;
}
