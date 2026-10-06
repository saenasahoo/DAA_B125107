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
 ll mn=1LL<<60;
 for(int i=0;i<n;i++){ll x;scanf("%lld",&x); if(x&1)x*=2; if(x<mn)mn=x; hpush(-x);}
 ll ans=-H[0]-mn;
 while(!((-H[0])&1)){
  ll t=-hpop()/2;
  if(t<mn)mn=t;
  hpush(-t);
  if(-H[0]-mn<ans) ans=-H[0]-mn;
 }
 printf("%lld\n",ans);
}