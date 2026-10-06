#include <stdio.h>
int main(){
 int n; double W; scanf("%d %lf",&n,&W);
 double v[n],w[n],l[n]; int u[n];
 for(int i=0;i<n;i++){scanf("%lf %lf %lf",&v[i],&w[i],&l[i]);u[i]=0;}
 double t=0,tot=0;
 while(W>1e-12){
  int b=-1; double bd=0;
  for(int i=0;i<n;i++) if(!u[i]){
   double d=v[i]/w[i]-l[i]*t;
   if(d>bd){bd=d;b=i;}
  }
  if(b<0)break;
  double take=w[b]<W?w[b]:W;
  tot+=bd*take; W-=take; t+=take; u[b]=1;
  printf("item %d fraction %.3f (density %.3f)\n",b+1,take/w[b],bd);
 }
 printf("Total value = %.4f\n",tot);
}