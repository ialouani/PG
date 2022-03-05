#include "set_sentinel.h"

void set__free(struct set* se){
  se->s[0]=NULL;
  free(se);
}

struct set* set__empty(void){
  struct set* set_empty=(struct set*)malloc(sizeof(*set_empty));
  set_empty->s[0]=SET__BOUND;
  for(int i=1;i<SET__SIZE;i++){
    set_empty->s[1]=SET__BOUND;
  }
  return set_empty;
}

int set__is_empty(const struct set* se){
  return se->s[0]==SET__BOUND;
}

size_t find(void* const s[], void* c){
  if(*(int*)c<0) return 10;
  else if(s[0]==SET__BOUND) return 0;
  size_t i=0;
  for(i=0;s[(int)i]!=SET__BOUND && *(int*)s[i]<*(int*)c;i++){
  }
  return i;
}

void shift_right(void* s[], size_t begin){
  int n=0;
  while(s[n]!=SET__BOUND) n++;
  for(size_t h=n;h>=begin+1;h--){
    s[h]=s[h-1];
  }
  s[n+1]=SET__BOUND;
}

void shift_left(void* s[], size_t end){
  for(int mn=0;mn<(int)end;mn++) s[mn]=s[mn+1];
}

int set__find(const struct set* se, void* c){
  for(int i=0;se->s[i]!=SET__BOUND;i++){
    if(*(int*)se->s[i]==*((int*)c)) return 1;
  }
  return 0;
}

size_t set__size(const struct set* se){
  int a;
  for(a=0;se->s[a]!=SET__BOUND;a++){}
  return a;
}

int set__add(struct set* se, void* c){
  if(set__size(se)==SET__SIZE-1 || set__find(se,c)==1 || *(int*)c<0) return -1;
  else if(set__is_empty(se)){
    shift_right(se->s,0);
    se->s[0]=c;
    return 0;
  }
  else if(set__size(se)==SET__SIZE) return 0;
  else if(find(se->s,c)==(size_t)(SET__SIZE-1)) return -1;
  else{
    int position=(int)find(se->s,c);
    if(se->s[position]==c) return 0;
    shift_right(se->s,(size_t)position);
    se->s[position]=c;
    return 0;
  }
}

int set__remove(struct set* se, void* c){
  if(*(int*)c<0) return -1;
  else if(set__is_empty(se)) return -1;
  else if(find(se->s,c)==SET__SIZE-1) return -1;
  else{
    int position2=find(se->s,c);
    if(se->s[position2]==c)
      {
      void* ss3[SET__SIZE];
      int b=0;
      while(position2+b<SET__SIZE){
	ss3[b]=se->s[position2+b];
	b++;}
    
      shift_left(ss3,SET__SIZE-position2-1);
      for(int c=position2;c<SET__SIZE;c++) se->s[c]=ss3[c-position2];
      return 0;}
    return -2;
  }}
	




    

