#include <stdio.h>
#include <string.h>

typedef long long ll;
ll H[100005]; int hn=0;
void hpush(ll x){int i=hn++;H[i]=x;
 while(i&&H[(i-1)/2]>H[i]){ll t=H[i];H[i]=H[(i-1)/2];H[(i-1)/2]=t;i=(i-1)/2;}}
ll hpop(){ll r=H[0];H[0]=H[--hn];int i=0;
 for(;;){int l=2*i+1,m=i,q=l+1;
  if(l<hn&&H[l]<H[m])m=l; if(q<hn&&H[q]<H[m])m=q; if(m==i)break;
  ll t=H[i];H[i]=H[m];H[m]=t;i=m;}
 return r;}
char s[100005],r[100005]; int cnt[256];
int main(){
 int K; scanf("%100000s %d",s,&K); if(K<1)K=1;
 int n=strlen(s);
 for(int i=0;i<n;i++) cnt[(unsigned char)s[i]]++;
 for(int c=0;c<256;c++) if(cnt[c]) hpush(-((ll)cnt[c]*256+c));
 for(int i=0;i<n;i++){
  if(i>=K){int c=(unsigned char)r[i-K]; if(cnt[c]>0) hpush(-((ll)cnt[c]*256+c));}
  if(!hn){puts("\"\"  (impossible)");return 0;}
  ll x=-hpop(); int c=x%256; r[i]=c; cnt[c]--;
 }
 r[n]=0; puts(r);
}