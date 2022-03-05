#include<stdlib.h>
#ifndef __F
#define __F
#include "set_link.h"
#include<limits.h>
#include<stdio.h>
#include "link.h"
#endif

struct set set__empty(void){
  struct set s;
  s.l=calloc(1,sizeof(struct link));
  (s.l)->head=calloc(1,sizeof(struct lelement));
  (s.l)->head->data=__INT_MAX__;
  (s.l)->head->next=SENTINEL;
  return s;
}

int set__is_empty(const struct set* se){
  return llm__is_end_mark(se->l->head);
}

int set__find(const struct set* se, int c){
  struct lelement* tete=se->l->head;
  while(!llm__is_end_mark(tete)){
    if(tete->data==c) return 1;
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

struct lelement* find(struct link* l, int f){
  if(f<0) return NULL;
  else if(l->head->data==f) return l->head; 
  else{
    struct lelement* tete=l->head;
    while(tete->next!=SENTINEL && tete->next->data<f) tete=tete->next;
    if(tete->next!=SENTINEL && tete->next->data>=f) return tete;
  }
  return NULL;
}


int set__add(struct set *se, int c){
  if(c<0) return -1;
  else if(!set__is_empty(se) && set__find(se,c)==1) return -1;
  else if(set__is_empty(se) || se->l->head->data>=c){
    struct lelement *add0=malloc(sizeof(struct lelement));
    add0->data=c;
    add0->next=NULL;
    lnk__add_head(se->l,add0);
    return 0;
  }
  else{
    struct lelement *add0=malloc(sizeof(struct lelement));
    add0->data=c;
    add0->next=NULL;
    struct lelement* apres_ceci=find(se->l,c);
    lnk__add_after(se->l,apres_ceci,add0);
    return 0;
  }
}

int set__remove(struct set* se, int c){
  if(c<0) return -1;
  else if(set__is_empty(se)) return -1;
  else if(!set__find(se,c)) return -1;
  else if(se->l->head->data==c){
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
    free(se->l->head);free(se->l);return;
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
}


    
