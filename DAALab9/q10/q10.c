#include <stdio.h>
#include <string.h>
#define N 20
#define LEN 4005
char s[N][LEN]; int dead[N];
int ov(char*a,char*b){
 int la=strlen(a),lb=strlen(b),m=la<lb?la:lb;
 for(int k=m;k>0;k--) if(!strncmp(a+la-k,b,k)) return k;
 return 0;
}
int main(){
 int n; scanf("%d",&n);
 for(int i=0;i<n;i++) scanf("%s",s[i]);
 for(int i=0;i<n;i++) for(int j=0;j<n;j++) if(i!=j&&!dead[j]&&!dead[i]){
  if(!strcmp(s[i],s[j])){ if(i>j) dead[i]=1; }
  else if(strstr(s[j],s[i])) dead[i]=1;
 }
 int alive=0; for(int i=0;i<n;i++) if(!dead[i]) alive++;
 while(alive>1){
  int bi=-1,bj=-1,bo=-1;
  for(int i=0;i<n;i++) if(!dead[i]) for(int j=0;j<n;j++) if(j!=i&&!dead[j]){
   int o=ov(s[i],s[j]); if(o>bo){bo=o;bi=i;bj=j;}
  }
  strcat(s[bi],s[bj]+bo); dead[bj]=1; alive--;
 }
 for(int i=0;i<n;i++) if(!dead[i]) printf("%s\nLength = %zu\n",s[i],strlen(s[i]));
}