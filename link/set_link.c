#include<stdlib.h>
#ifndef __F
#define __F
#include "set_link.h"
#include<limits.h>
#include<stdio.h>
#include "link.h"
#endif



struct set* set__empty(void){
  struct set* s=(struct set*)malloc(sizeof(*s));
  s->l=calloc(1,sizeof(struct link));
  (s->l)->head=calloc(1,sizeof(struct lelement));
  (s->l)->head->data=data_fin_A;
  (s->l)->head->next=SENTINEL;
  return s;
}

int set__is_empty(const struct set* se){
  return llm__is_end_mark(se->l->head);
}

int set__find(const struct set* se, void* c){
  struct lelement* tete=se->l->head;
  while(!llm__is_end_mark(tete)){
    if(*(int*)tete->data==*(int*)c) return 1;
    tete=tete->next;
  }
  return 0;
}

size_t set__size (const struct set* se){
  size_t len=0;
  struct lelement* tete=se->l->head;
  while(!llm__is_end_mark(tete)){
    len++;
    tete=tete->next;
  }
  return len;
}

struct lelement* find(struct link* l, void* f){
  if(*(int*)f<0) return NULL;
  else if(*(int*)l->head->data==*(int*)f) return l->head; 
  else{
    struct lelement* tete=l->head;
    while(tete->next!=SENTINEL && *(int*)tete->next->data < *(int*)f) tete=tete->next;
    if(tete->next!=SENTINEL && *(int*)tete->next->data >= *(int*)f) return tete;
  }
  return NULL;
}


int set__add(struct set *se, void* c){
  if(*(int*)c<0) return -1;
  else if(!set__is_empty(se) && set__find(se,c)==1) return -1;
  else if(set__is_empty(se) || *(int*)se->l->head->data >= *(int*)c){
    struct lelement *add0=malloc(sizeof(struct lelement));
    add0->data=c;
    add0->next=NULL;
    lnk__add_head(se->l,add0);
    return 0;
  }
  else{
    struct lelement *add0=malloc(sizeof(*add0));
    add0->data=c;
    add0->next=NULL;
    struct lelement* apres_ceci=find(se->l,c);
    lnk__add_after(se->l,apres_ceci,add0);
    return 0;
  }
}

int set__remove(struct set* se, void* c){
  if(*(int*)c<0) return -1;
  else if(set__is_empty(se)) return -1;
  else if(!set__find(se,c)) return -1;
  else if(*(int*)se->l->head->data==*(int*)c){
    struct lelement* removed=lnk__remove_head(se->l);
    free(removed);
    return 0;
  }
  else{
    struct lelement* apres_ceci=find(se->l,c);
    struct lelement* removed=lnk__remove_after(se->l,apres_ceci);
    free(removed);
    return 0;
  }
}

void set__free(struct set* se){
  if(set__is_empty(se)){
    free(se->l->head);free(se->l);free(se);return;
  }
  else{
   struct lelement* tete=se->l->head;
  while(tete->next!=tete){
    struct lelement* tete2=tete->next;
    free(tete);
    tete=tete2;
  }
  free(se->l);
  }
  free(se);
}


    
