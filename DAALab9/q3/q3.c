#include <stdio.h>
#include <stdlib.h>

typedef long long ll;
ll H[100005]; int hn=0;
void hpush(ll x){int i=hn++;H[i]=x;
 while(i&&H[(i-1)/2]>H[i]){ll t=H[i];H[i]=H[(i-1)/2];H[(i-1)/2]=t;i=(i-1)/2;}}
ll hpop(){ll r=H[0];H[0]=H[--hn];int i=0;
 for(;;){int l=2*i+1,m=i,q=l+1;
  if(l<hn&&H[l]<H[m])m=l; if(q<hn&&H[q]<H[m])m=q; if(m==i)break;
  ll t=H[i];H[i]=H[m];H[m]=t;i=m;}
 return r;}
typedef struct{ll d,f;}S;
int cmp(const void*a,const void*b){ll x=((S*)a)->d,y=((S*)b)->d;return (x>y)-(x<y);}
int main(){
 int n; ll D,F; scanf("%d %lld %lld",&n,&D,&F);
 S s[n]; for(int i=0;i<n;i++) scanf("%lld %lld",&s[i].d,&s[i].f);
 qsort(s,n,sizeof(S),cmp);
 ll reach=F; int i=0,stops=0;
 while(reach<D){
  while(i<n&&s[i].d<=reach) hpush(-s[i++].f);
  if(!hn){puts("-1 (unreachable)");return 0;}
  reach+=-hpop(); stops++;
 }
 printf("%d\n",stops);
}