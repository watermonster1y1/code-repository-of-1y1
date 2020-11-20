#include <map>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <algorithm>

using namespace std;

#define il inline
#define re register
#define file(s) freopen(#s".in","r",stdin),freopen(#s".out","w",stdout)
#define mp(x,y) make_pair(x,y)

typedef double db;
typedef long long ll;
typedef pair<int,int> Pair;

const int N=1e6+10;

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
	re int f=0;x=0;re char ch=getc();
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
}
}
using namespace FastIO;

il int randomint(int l,int r){return rand()%(r-l+1)+l;}
// Get a random int number in [l,r]
il ll randomll(ll l,ll r){return (ll)rand()*rand()%(r-l+1)+l;}
// Get a random ll number in [l,r]

Pair e[N];
il void GenTree(int n,int hei,int Wei)
{
	for(re int i=1,fa;i<n;++i)
	{
		fa=randomint(1,i);
		if(i<hei) fa=i;
		e[i]=mp(i+1,fa);
	}
	for(re int i=1;i<n;++i) if(rand()&1) swap(e[i].first,e[i].second);
	random_shuffle(e+1,e+n);
	for(re int i=1;i<n;++i)
	{
		printf("%d %d",e[i].first,e[i].second);
		if(Wei) printf(" %d",randomint(1,Wei));
		puts("");
	}
	return;
}
// Generate a tree with a min_height_limit

map<Pair,int>vis;
il void GenGraph(int n,int m,int Wei)
{
	for(re int i=1,fa;i<n;++i)
	{
		fa=randomint(1,i);
		e[i]=mp(fa,i+1);
		vis[e[i]]=1;
	}
	for(re int i=n;i<=m;++i)
	{
		re int u=randomint(1,n-1);
		re int v=randomint(u,n);
		while(u==v||vis[mp(u,v)])
		{
			u=randomint(1,n-1);
			v=randomint(u,n);
		}
		e[i]=mp(u,v);
		vis[e[i]]=1;
	}
	for(re int i=1;i<=m;++i) if(rand()&1) swap(e[i].first,e[i].second);
	random_shuffle(e+1,e+m+1);
	for(re int i=1;i<=m;++i)
	{
		printf("%d %d",e[i].first,e[i].second);
		if(Wei) printf(" %d",randomint(1,Wei));
		puts("");
	}
	return;
}
// Generate a graph without repeated_edge and self_circle

il void GenSequence(int n,int Min,int Max)
{
	for(re int i=1;i<=n;++i)
		printf("%d ",randomint(Min,Max));
}
//Generate a sequence with element in [Min,Max]

int per[N];
il void GenPermutation(int n)
{
	for(re int i=1;i<=n;++i) per[i]=i;
	random_shuffle(per+1,per+n+1);
	for(re int i=1;i<=n;++i) printf("%d ",per[i]);
	return;
}
//Generate a permutation

il void GenInterval(int n,int m)
{
	for(re int i=1;i<=m;++i)
	{
		re int l=randomint(1,n);
		re int r=randomint(1,n);
		if(l>r) swap(l,r);
		printf("%d %d\n",l,r);
	}
}
//Generate m intervals in [1,n]

int main()
{
	flush();return 0;
}