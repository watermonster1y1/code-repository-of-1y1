#include <cstdio>
#include <cstring>

using namespace std;

#define il inline
#define re register

const int N=1e6+10;

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
}
}
using namespace FastIO;

char a[N],b[N];
int kmp[N];

int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	scanf("%s%s",a+1,b+1);
	re int j=0,n=strlen(a+1),m=strlen(b+1);
	for(re int i=2;i<=m;++i)
	{
		while(j&&b[j+1]^b[i]) j=kmp[j];
		kmp[i]=b[j+1]^b[i]?j:++j;
	}
	j=0;
	for(re int i=1;i<=n;++i)
	{
		while(j&&b[j+1]^a[i]) j=kmp[j];
		j=b[j+1]^a[i]?j:j+1;
		if(j==m) print(i-j+1),buf2[++p3]='\n',j=kmp[j];
	}
	for(re int i=1;i<=m;++i) print(kmp[i]),buf2[++p3]=' ';
	flush();return 0;
}