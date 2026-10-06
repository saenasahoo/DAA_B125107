#include <stdio.h>
#define M 1024
int main(){
 int n; scanf("%d",&n);
 char c[M]; long long f[2*M]; int p[2*M],a[2*M],len[M],o[M];
 for(int i=0;i<n;i++) scanf(" %c %lld",&c[i],&f[i]);
 for(int i=0;i<2*n;i++){a[i]=i<n;p[i]=-1;}
 int m=n;
 for(int s=1;s<n;s++){
  int x=-1,y=-1;
  for(int i=0;i<m;i++) if(a[i]){
   if(x<0||f[i]<f[x]){y=x;x=i;}
   else if(y<0||f[i]<f[y]) y=i;
  }
  f[m]=f[x]+f[y]; p[x]=p[y]=m; a[x]=a[y]=0; a[m]=1; m++;
 }
 for(int i=0;i<n;i++){int l=0;for(int u=i;p[u]>=0;u=p[u])l++; len[i]=n==1?1:l; o[i]=i;}
 for(int i=1;i<n;i++){int k=o[i],j=i-1; // insertion sort by (len, symbol)
  while(j>=0&&(len[o[j]]>len[k]||(len[o[j]]==len[k]&&c[o[j]]>c[k]))){o[j+1]=o[j];j--;}
  o[j+1]=k;}
 unsigned long long code=0; long long cost=0;
 for(int k=0;k<n;k++){
  int s=o[k];
  if(k) code=(code+1)<<(len[s]-len[o[k-1]]);
  printf("%c : ",c[s]);
  for(int b=len[s]-1;b>=0;b--) putchar('0'+((code>>b)&1));
  putchar('\n'); cost+=f[s]*len[s];
 }
 printf("Weighted length = %lld\n",cost);
}