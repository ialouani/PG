#include "set_dynamic.h"
#include<stdio.h>


struct set* set__empty(void){
  struct set* ens=(struct set*)malloc(sizeof(*ens));
  ens->s=NULL;
  ens->capacity=0;
  ens->size=0;
  return ens;
}

int set__find(const struct set* se, void* c){
  for(int i=0;i<(int)se->size;i++){
    if(*(int*)(se->s[i])==*(int*)(c)) return 1;
  }
  return 0;
}


int set__is_empty(const struct set* se){
  return se->size==0;
}

int find(void* const s[], void* c, int begin , int end){
  int j;
  for(j=begin;j<=end;j++){
    if(*(int*)s[j]>=*(int*)c) break;}
  if(j<=end) return j;
  return -1;
}

size_t set__size(const struct set* se){
  return se->size;
}

void shift_right(void* s[], int begin, int end){
  for(int k=end+1;k>=begin+1;k--){
    s[k]=s[k-1];
  }
}

void shift_left(void* s[], int begin, int end){
  for(int h=begin;h<end;h++){
    s[h]=s[h+1];
  }
}

int set__add(struct set* se, void* c){
  if(*(int*)c<0) return -1;
  else if(set__is_empty(se)){
    se->capacity=1;
    se->size=1;
    int size__set=(int)se->size;
    se->s=(void**)malloc(size__set*sizeof(*se->s));
    (se->s)[0]=c;
    return 0;
  }
  else if(set__find(se,c)==1) return -1;
  else{
    if(se->size==se->capacity){
      se->capacity*=2;
      se->size++;
      int capacity__set=(int)se->capacity;
      se->s=(void**)realloc(se->s,sizeof(*se->s)*(capacity__set));
      int position=find(se->s,c,0,(int)(se->size-2));
      if(position!=-1){
	shift_right(se->s,position,(int)(se->size-2));
	se->s[position]=c;
	return 0;
      }
      else{
	se->s[(int)(se->size-1)]=c;
	return 0;
      }
    }
    else{
      se->size++;
      int position=find(se->s,c,0,(int)(se->size-2));
      if(position!=-1){
	shift_right(se->s,position,(int)(se->size-2));
	se->s[position]=c;
	return 0;
      }
      else{
	se->s[(int)(se->size-1)]=c;
	return 0;
      }
    }
  }
  return -1;
}

int set__remove(struct set* se, void* c){
  if(*(int*)c<0) return -1;
  else if(set__is_empty(se)) return -1;
  else if(set__find(se,c)==0) return -1;
  else if(se->size==1){
    se->size=0;
    se->capacity=0;
    free(se->s);
    se->s=NULL;
    return 0;
  }
  else{
    int position=find(se->s,c,0,(int)(se->size-1));
    shift_left(se->s,position,(int)(se->size-1));
    se->size--;
    if(2*(se->size)==se->capacity){
      se->capacity/=2;
      se->s=realloc(se->s,sizeof(*se->s)* (int)(se->capacity));
    }
    return 0;
  }
}

void set__free(struct set* se){
  se->capacity=0;se->size=0;
  free(se->s);
  free(se);
}




