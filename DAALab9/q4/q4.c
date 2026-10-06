#include <stdio.h>

typedef long long ll;
ll H[100005]; int hn=0;
void hpush(ll x){int i=hn++;H[i]=x;
 while(i&&H[(i-1)/2]>H[i]){ll t=H[i];H[i]=H[(i-1)/2];H[(i-1)/2]=t;i=(i-1)/2;}}
ll hpop(){ll r=H[0];H[0]=H[--hn];int i=0;
 for(;;){int l=2*i+1,m=i,q=l+1;
  if(l<hn&&H[l]<H[m])m=l; if(q<hn&&H[q]<H[m])m=q; if(m==i)break;
  ll t=H[i];H[i]=H[m];H[m]=t;i=m;}
 return r;}
int main(){
 int n; scanf("%d",&n);
 for(int i=0;i<n;i++){ll x;scanf("%lld",&x);hpush(x);}
 ll cost=0;
 while(hn>1){ll a=hpop(),b=hpop();cost+=a+b;hpush(a+b);}
 printf("%lld\n",cost);
}