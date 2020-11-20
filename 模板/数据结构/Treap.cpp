#include <ctime>
#include <cstdio>
#include <cstdlib>

using namespace std;

#define il inline
#define re register

const int N=1.5e6+100;

namespace IO
{
char buf[1<<21],buf2[1<<21],*p1=buf,*p2=buf;
int p,p3=-1;
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
	do{a[++p]=x%10+48;}while(x/=10);
	do{buf2[++p3]=a[p];}while(--p);
}
}
using namespace IO;

int rt,pool;
int son[2][N],siz[N],val[N],cnt[N],pri[N];
#define ls(x) (son[0][x])
#define rs(x) (son[1][x])
#define pushup(x) (siz[x]=siz[ls(x)]+siz[rs(x)]+cnt[x])
il void zig(int &x)
{
	re int k=ls(x);
	ls(x)=rs(k);rs(k)=x;
	pushup(x);pushup(k);
	x=k;
}
il void zag(int &x)
{
	re int k=rs(x);
	rs(x)=ls(k);ls(k)=x;
	pushup(x);pushup(k);
	x=k;
}
il void ins(int &x,int v)
{
	if(!x)
	{
		x=++pool;
		ls(x)=rs(x)=0;val[x]=v;
		cnt[x]=siz[x]=1;pri[x]=rand();
		return;
	}
	++siz[x];
	if(val[x]==v){++cnt[x];return;}
	if(val[x]<v)
	{
		ins(rs(x),v);
		if(pri[rs(x)]>pri[x]) zag(x);
	}
	else
	{
		ins(ls(x),v);
		if(pri[ls(x)]>pri[x]) zig(x);
	}
}
il void del(int &x,int v)
{
	if(val[x]==v)
	{
		if(cnt[x]>1) --cnt[x],--siz[x];
		else if(!ls(x)||!rs(x)) x=ls(x)|rs(x);
		else if(pri[ls(x)]>pri[rs(x)]) zig(x),del(x,v);
		else zag(x),del(x,v);
		return;
	}
	--siz[x];
	if(val[x]<v) del(rs(x),v);
	else del(ls(x),v);
	return;
}
il int query_rnk(int key)
{
	re int p=rt,res=0;
	while(p)
	{
		if(val[p]==key) return res+siz[ls(p)];
		if(val[p]>key) p=ls(p);
		else res+=siz[ls(p)]+cnt[p],p=rs(p);
	}
	return res;
}
il int query_kth(int key)
{
	re int p=rt;
	while(p)
	{
		if(siz[ls(p)]<key&&siz[ls(p)]+cnt[p]>=key) return val[p];
		else if(siz[ls(p)]>=key) p=ls(p);
		else key-=siz[ls(p)]+cnt[p],p=rs(p);
	}
	return 0;
}

int n,m,x,opt,lst=0,ans=0;

int main()
{
	srand(time(0));
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	read(n),read(m);
	for(re int i=1;i<=n;++i) read(x),ins(rt,x);
	for(re int i=1;i<=m;++i)
	{
		read(opt),read(x);x^=lst;
		if(opt==1) ins(rt,x);
		if(opt==2) del(rt,x);
		if(opt==3) lst=query_rnk(x)+1;
		if(opt==4) lst=query_kth(x);
		if(opt==5) lst=query_kth(query_rnk(x));
		if(opt==6) lst=query_kth(query_rnk(x+1)+1);
		if(opt>2) ans^=lst;
	}
	print(ans);
	flush();return 0;
}