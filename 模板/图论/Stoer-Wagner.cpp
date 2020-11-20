#include <cstdio>
#include <cstring>

using namespace std;

#define re register
#define il inline

const int N=6e2+10;

namespace IO
{
	char buf1[1<<21],buf2[1<<21],*p1=buf1,*p2=buf1;
	int p3,p4=-1;
	il int get_char(){return p1==p2&&(p2=(p1=buf1)+fread(buf1,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
	#define isdigit(ch) (ch>=48&&ch<=57)
	template <typename T>
	il void read(T &x)
	{

		x=0;re int f=0;re int ch=get_char();
		while(!isdigit(ch)) f|=ch=='-',ch=get_char();
		while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=get_char();
		x=f?-x:x;return;
	}
	il void Flush(){fwrite(buf2,1,p4+1,stdout);p4=-1;}
	template <typename T>
	il void print(T x)
	{
		if(p4>(1<<21)) Flush();
		if(x<0) buf2[++p4]='-',x=-x;
		re int tmp[50];
		do{tmp[++p3]=x%10+48;}while(x/=10);
		do{buf2[++p4]=tmp[p3--];}while(p3);
		return;
	}
}
using namespace IO;

il int min(int a,int b){return a<b?a:b;}

int n,m;

int g[N][N];

int dis[N],vis[N],del[N];
il int Contract(int &s,int &t)
{
	memset(dis,0,sizeof(dis));
	memset(vis,0,sizeof(vis));
	re int goal,MinCut=0;dis[0]=-1;
	for(re int i=1;i<=n;++i)
	{
		goal=0;
		for(re int j=1;j<=n;++j)
			if(!del[j]&&!vis[j]&&dis[j]>dis[goal])
				goal=j;
		if(!goal) return MinCut;
		s=t;t=goal;MinCut=dis[goal];vis[goal]=1;
		for(re int j=1;j<=n;++j)
			if(!vis[j]&&!del[j])
				dis[j]+=g[goal][j];
	}
	return MinCut;
}
il int Stoer_Wagner()
{
	re int s,t,res=0x3f3f3f3f;
	for(re int i=1;i<n;++i)
	{
		res=min(res,Contract(s,t));
		//printf("Contracted S: %d T: %d,Now MinCut = %d\n",s,t,res);
		del[t]=1;
		if(!res) return 0;
		for(re int j=1;j<=n;++j)
			if(!del[j]) g[s][j]=(g[j][s]+=g[j][t]);
	}
	return res;
}

int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	read(n),read(m);
	for(re int i=1,u,v,w;i<=m;++i)
	{
		read(u),read(v),read(w);
		g[u][v]=g[v][u]=w;
	}
	print(Stoer_Wagner());
	Flush();return 0;
}
