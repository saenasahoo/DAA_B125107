#include <stdio.h>
#define INF 1000000000000LL
typedef long long ll;
int L[2100],R[2100],dep[2100]; ll W[2100];
void dfs(int u,int d){ if(L[u]<0){dep[u]=d;return;} dfs(L[u],d+1); dfs(R[u],d+1); }
int main(){
 int n; scanf("%d",&n);
 ll sw[2100]; int sn[2100]; int m=0;
 sw[m]=INF; sn[m++]=-1;
 for(int i=0;i<n;i++){scanf("%lld",&W[i]);L[i]=R[i]=-1;sw[m]=W[i];sn[m++]=i;}
 sw[m]=INF; sn[m++]=-1;
 int nodes=n; ll cost=0;
 while(m>3){
  int k=2; while(sw[k-1]>sw[k+1]) k++;
  ll s=sw[k-1]+sw[k]; cost+=s;
  L[nodes]=sn[k-1]; R[nodes]=sn[k]; int id=nodes++;
  for(int i=k+1;i<m;i++){sw[i-2]=sw[i];sn[i-2]=sn[i];}
  m-=2;
  int j=k-2; while(sw[j]<s) j--;
  for(int i=m;i>j+1;i--){sw[i]=sw[i-1];sn[i]=sn[i-1];}
  sw[j+1]=s; sn[j+1]=id; m++;
 }
 dfs(sn[1],0);
 printf("Min cost sum(w*depth) = %lld\nDepths:",cost);
 for(int i=0;i<n;i++) printf(" %d",dep[i]);
 puts("");
}