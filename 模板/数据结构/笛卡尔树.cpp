#include <cstdio>

using namespace std;

#define re register
#define il inline

typedef long long ll;

const int N=1e7+10;

namespace IO
{
	char buf1[1<<21],buf2[1<<21],*p1=buf1,*p2=buf1;
	il int get_char(){return p1==p2&&(p2=(p1=buf1)+fread(buf1,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
	#define isdigit(ch) (ch>=48&&ch<=57)
	template <typename T>
	il void read(T &x)
	{
		x=0;re int f=0,ch=get_char();
		while(!isdigit(ch)) f|=ch=='-',ch=get_char();
		while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=get_char();
		x=f?-x:x;return;
	}
	int p3,p4=-1;
	il void Flush(){fwrite(buf2,1,p4+1,stdout);p4=-1;return;}
	template <typename T>
	il void print(T x)
	{
		if(p4>(1<<20)) Flush();
		if(x<0) buf2[++p4]='-',x=-x;
		re int tmp[50];
		do{tmp[++p3]=x%10+48;}while(x/=10);
		do{buf2[++p4]=tmp[p3--];}while(p3);
		buf2[++p4]=' ';return;
	}
}
using namespace IO;

int n;
int a[N];

int st[N],top;
int ls[N],rs[N];

ll ans1,ans2;
int main()
{
	read(n);
	for(re int i=1;i<=n;++i) read(a[i]);
	for(re int i=1;i<=n;++i)
	{
		while(top&&a[st[top]]>a[i]) ls[i]=st[top--];
		if(top) rs[st[top]]=i;
		st[++top]=i;
	}
	for(re int i=1;i<=n;++i) ans1^=(ll)i*(ls[i]+1);
	for(re int i=1;i<=n;++i) ans2^=(ll)i*(rs[i]+1);
	print(ans1);print(ans2);
	Flush();return 0;
}
