#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

#define il inline
#define re register

typedef long double db;

const int N=110;

int n;
db a[N][N];
il void Guass_Jordan()
{
	re int goal;re db tmp;
	for(re int i=1;i<=n;++i)
	{
		goal=i;
		for(re int j=i+1;j<=n;++j)
			if(fabs(a[goal][i])<fabs(a[j][i]))
				goal=j;
		if(goal^i) swap(a[goal],a[i]);
		if(fabs(a[i][i])<(1e-6)){puts("No Solution");exit(0);}
		for(re int j=1;j<=n;++j)
			if(j^i)
			{
				tmp=a[j][i]/a[i][i];a[j][i]=0;
				for(re int k=i;k<=n+1;++k)
					a[j][k]-=a[i][k]*tmp;
			}
	}
	for(re int i=1;i<=n;++i) a[i][n+1]/=a[i][i];
}


int main()
{
	freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=n+1;++j)
			scanf("%Lf",&a[i][j]);
	Guass_Jordan();
	for(re int i=1;i<=n;++i)
		printf("%.2Lf\n",a[i][n+1]);
	return 0;
}