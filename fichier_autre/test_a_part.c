#include "tout.h"
#include<stdio.h>
#define SET__SIZE 10
#define SET_BOUND -1

struct set{
  int s[SET__SIZE];
};
int test_vide(struct set* st){
  return st->s[0]==-1;
}
int size_list(struct set* st){
  int i=0;
  while(st->s[i]>=0) i++;
  return i;
}
void afficher(struct set* e){
  int i=0;
  while(i<SET__SIZE){//des 0 sinon().
    printf("%d\t",e->s[i]);
    i++;
  }
  printf("\n");
}
void set__add(struct set *st, int c){
  if(test_vide(st)){
    st->s[0]=c; st->s[1]=SET_BOUND; return;}
  //tableau trie.
  int j=0;
  while(st->s[j]<c) j++;
  //st->s[j]>=c
  //on doit inserer a la position j l'element c pour que l'ordre indique:
  //s[j-1]<c et s[j+1] le prochain(modifiable)>=c.
  int position=j;
  int limite=10;
  int len=size_list(st);
  st->s[len]=c;
  st->s[len+1]=-1;
  int y=len;
  for(int g=len;g>0;g--){
    if(st->s[g-1]>st->s[g]){
      int inter=st->s[g-1];
      st->s[g-1]=st->s[g];
      st->s[g]=inter;
    }
  }
  return;}
void set__remove(struct set* ss,int c){
  //on suppose que c existe i.e. il existe p tel que ss->s[p]===c.
  int i=0;
  while(ss->s[i]<c) i++;
  //i de sortie verifie: ss->s[i]===c.
  int s1[i+1];
  int j;
  for(j=0;j<i;j++){
    s1[j]=ss->s[j];
  }
  int y=0;
  while(ss->s[y]>=0) y++;
  //y==len(ss->s);;
  //=>s[y-1]==SET__BOUND;(y-1=k+1=>k=y-2)
  for(int k=j;k<y;k++){
    ss->s[k]=ss->s[k+1];
  }
  ss->s[y-1]=SET_BOUND;
  if(y-1<9){
    for(int u=y-1;u<9;u++) ss->s[u]=-1;
  }}
int main(){
   struct set se1={{1,2,4,5,SET_BOUND}};
   afficher(&se1);
   set__add(&se1,3);
   printf("-----------AJOUT d'un elt: ex:: 3 ->::: ---------------------\n\n");
   afficher(&se1);
   set__remove(&se1,4);
   printf("-----------SUPPRESSION d'un elt: ex:: 4 ->::: ---------------------\n\n");
   afficher(&se1);
   return 0;
}
