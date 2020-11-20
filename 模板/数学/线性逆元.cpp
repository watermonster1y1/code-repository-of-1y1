#include <cstdio>

using namespace std;

#define il inline
#define re register

typedef long long ll;

const int N=3e6+10;

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

int n;
ll mod,inv[N];

int main()
{
	read(n);read(mod);inv[1]=1;
	for(re int i=2;i<=n;++i) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(re int i=1;i<=n;++i) print(inv[i]);
	flush();return 0;
}