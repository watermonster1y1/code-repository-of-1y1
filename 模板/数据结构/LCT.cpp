#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define il inline
#define re register

const int N=1e5+10;

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
using namespace IO;

int fa[N],son[2][N],val[N],w[N],tag[N];
#define ls(x) (son[0][x])
#define rs(x) (son[1][x])
#define ident(x,f) (rs(f)==x)
#define notrt(x) (ls(fa[x])==x||rs(fa[x])==x)
#define connect(x,f,s) (son[s][f]=x,fa[x]=f)
#define reverse(x) (swap(ls(x),rs(x)),tag[x]^=1)
#define pushup(x) (val[x]=w[x]^val[ls(x)]^val[rs(x)])
il void rotate(int x)
{
	re int f=fa[x],ff=fa[f],k=ident(x,f);
	connect(son[k^1][x],f,k);fa[x]=ff;
	if(notrt(f)) son[ident(f,ff)][ff]=x;
	connect(f,x,k^1);pushup(f);pushup(x);
	return;
}
il void pushdown(int x)
{
	if(!tag[x]) return;
	if(ls(x)) reverse(ls(x));
	if(rs(x)) reverse(rs(x));
	tag[x]=0;return;
}
int st[N],top;
il void pushall(int x)
{
	top=0;
	while(notrt(x)) st[++top]=x,x=fa[x];
	pushdown(x);
	while(top) pushdown(st[top--]);
	return;
}
il void splay(int x)
{
	pushall(x);re int f,ff;
	while(notrt(x))
	{
		f=fa[x],ff=fa[f];
		if(notrt(f)) rotate(ident(x,f)^ident(f,ff)?x:f);
		rotate(x);
	}
	return;
}
il void access(int x)
{
	for(re int y=0;x;x=fa[y=x])
		splay(x),rs(x)=y,pushup(x);
	return;
}
#define makert(x) (access(x),splay(x),reverse(x))
il int getrt(int x)
{
	access(x);splay(x);
	while(ls(x)) pushdown(x),x=ls(x);
	splay(x);return x;
}
il void link(int x,int y)
{
	makert(x);
	if(getrt(y)==x) return;
	fa[x]=y;return;
}
il void cut(int x,int y)
{
	makert(x);
	if(getrt(y)^x||fa[y]^x||ls(y)) return;
	fa[y]=rs(x)=0;pushup(x);return;
}
#define split(x,y) (makert(x),access(y),splay(y))
il void modify(int x,int y){splay(x);w[x]=y;pushup(x);return;}
il int query(int x,int y){split(x,y);return val[y];}

int n,m;

int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	read(n),read(m);re int opt,x,y;
	for(re int i=1;i<=n;++i) read(w[i]);
	while(m--)
	{
		read(opt);read(x);read(y);
		if(opt==0) print(query(x,y));
		if(opt==1) link(x,y);
		if(opt==2) cut(x,y);
		if(opt==3) modify(x,y);
	}
	flush();return 0;
}