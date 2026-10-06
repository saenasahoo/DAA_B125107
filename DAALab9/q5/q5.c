#include <stdio.h>
int main(){
 int n; scanf("%d",&n);
 int r[n],c[n]; long long sum=0;
 for(int i=0;i<n;i++){scanf("%d",&r[i]);c[i]=1;}
 for(int i=1;i<n;i++) if(r[i]>r[i-1]) c[i]=c[i-1]+1;
 for(int i=n-2;i>=0;i--) if(r[i]>r[i+1]&&c[i]<=c[i+1]) c[i]=c[i+1]+1;
 for(int i=0;i<n;i++) sum+=c[i];
 printf("%lld\n",sum);
}