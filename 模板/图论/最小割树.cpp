#include <queue>
#include <cmath>
#include <cstdio>

using namespace std;
#define re register
#define il inline

const int N=550;
const int M=1550;
const int inf=0x3f3f3f3f;

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
	do{buf2[++p3]=a[p];} while (--p);
	buf2[++p3]='\n';
}
}
using namespace FastIO;

il int min(int a,int b){return a<b?a:b;}
il void swap(int &a,int &b){re int tmp=a;a=b;b=tmp;}
int n,m,q;

namespace dinic
{
int cnt=1,h[N],cur[N];
struct edge{int v,res,nxt;}e[M<<2];
il void add(int u,int v,int w){e[++cnt]=(edge){v,w,h[u]};h[u]=cnt;}
il void init()
{
	for(re int i=2;i<=cnt;i+=2)
		e[i].res+=e[i^1].res,e[i^1].res=0;
}
int dep[N];
il bool bfs(int s,int t)
{
	for(re int i=1;i<=n;++i) cur[i]=h[i],dep[i]=0;
	queue<int>q;q.push(s);dep[s]=1;
	while(!q.empty())
	{
		re int u=q.front();q.pop();
		for(re int i=h[u],v;i;i=e[i].nxt)
			if(!dep[v=e[i].v]&&e[i].res)
				dep[v]=dep[u]+1,q.push(v);
	}
	return dep[t]>0;
}
int dfs(int u,int flow,int t)
{
	if(!flow||u==t)  return flow;
	int tmp=0,v,f;
	for(re int i=cur[u];i;i=e[i].nxt)
	{
		cur[u]=i;
		if(dep[v=e[i].v]>dep[u]&&(f=dfs(v,min(flow-tmp,e[i].res),t)))
		{
			e[i].res-=f;e[i^1].res+=f;
			tmp+=f;
			if(!(flow-tmp)) break;
		}
	}
	return tmp;
}
il int ans(int s,int t)
{
	int res=0;init();
	while(bfs(s,t)) res+=dfs(s,inf,t);
	return res;
}
}
namespace GHT
{
int cnt=0,h[N];
struct edge{int v,w,nxt;}e[N<<1];
il void add(int u,int v,int w){e[++cnt]=(edge){v,w,h[u]};h[u]=cnt;}
int node[N],tmp1[N],tmp2[N];
void build(int l,int r)
{
	if(l==r) return;
	re int u=node[l],v=node[l+1];
	re int w=dinic::ans(u,v);
	add(u,v,w);
	add(v,u,w);
	re int cnt1=0,cnt2=0;
	for(re int i=l;i<=r;++i)
	{
		if(dinic::dep[node[i]]>0) tmp1[++cnt1]=node[i];
		else tmp2[++cnt2]=node[i];
	}
	for(re int i=l;i<=l+cnt1-1;++i) node[i]=tmp1[i-l+1];
	for(re int i=l+cnt1;i<=r;++i) node[i]=tmp2[i-cnt1-l+1];
	build(l,l+cnt1-1);build(l+cnt1,r);
}
int lg;
int fa[10][N],dep[N];
int st[10][N];
void dfs(int x,int f)
{
	dep[x]=dep[f]+1;
	fa[0][x]=f;
	for(re int i=1;i<=lg;++i)
	{
		fa[i][x]=fa[i-1][fa[i-1][x]];
		st[i][x]=min(st[i-1][fa[i-1][x]],st[i-1][x]);
	}
	for(re int i=h[x],v;i;i=e[i].nxt)
		if(e[i].v^f)
		{
			st[0][e[i].v]=e[i].w;
			dfs(e[i].v,x);
		}
}
il int query(int u,int v)
{
	re int res=inf;
	if(dep[u]<dep[v]) swap(u,v);
	for(re int i=lg;i>=0;--i)
		if(dep[fa[i][u]]>=dep[v])
		{
			res=min(res,st[i][u]);
			u=fa[i][u];
		}
	if(u==v) return res;
	for(re int i=lg;i>=0;--i)
		if(fa[i][u]^fa[i][v])
		{
			res=min(res,st[i][u]);
			u=fa[i][u];
			res=min(res,st[i][v]);
			v=fa[i][v];
		}
	res=min(res,st[0][u]);
	res=min(res,st[0][v]);
	return res;
}
}
int main()
{
	read(n),read(m);GHT::lg=log2(n)+1;
	for(re int i=1,u,v,w;i<=m;++i)
	{
		read(u),read(v),read(w);
		dinic::add(u,v,w);dinic::add(v,u,0);
		dinic::add(v,u,w);dinic::add(u,v,0);
	}
	for(re int i=1;i<=n;++i) GHT::node[i]=i;
	GHT::build(1,n);GHT::dfs(1,0);
	read(q);re int u,v;
	while(q--) read(u),read(v),print(GHT::query(u,v));
	flush();return 0;
}