#include<stdlib.h>
#ifndef __F
#define __F
#include "set_link.h"
#include<limits.h>
#include<stdio.h>
#include "link.h"
#endif
/*
void set__debug_data(const struct set* s, void(*print)(int)){
  struct lelement* tmp=s->l->head;
  while(!llm__is_end_mark(tmp)){
    print(tmp->data);
    tmp=tmp->next;
  }
}
*/
//En vrai, si on reflechit bien les 2 methodes premieres
//se rapprochent trop => on se reduit a struct via dynamic et link
//seulement SELON<++ la question demandee!.///////

struct cursor* get_cursor(const struct set* s){
  struct cursor* crs=(struct cursor*)malloc(sizeof(*crs));//attention...
  crs->position=s->l->head;
  crs->fin=NULL;
  return crs;}
void set__crs_start(struct cursor* cr){
  cr->fin=SENTINEL;}
void set__crs_next(struct cursor* cr){
  cr->position=cr->position->next;}
int set__crs_has_next(const struct cursor* cr){
  return cr->position->next!=SENTINEL;}
int set__crs_data(const struct cursor* cr){
  return cr->position->data;}
void set_crs_free(struct cursor* cr){
  free(cr);
}

void set__debug_data(struct set* s, void(*print)(int)){
  struct cursor* cr=get_cursor(s);
  set__crs_start(cr);
  while(set__crs_has_next(cr)){
    print(set__crs_data(cr));
    set__crs_next(cr);
  }
  free(cr);
}
//il faut avoir VOIRE DIRE AU DEBUT conserver le meme code.C'est ca le but.(2)


struct set* set__filter2(const struct set* s){
  struct set* ss=set__empty();
  struct lelement* tmp=s->l->head;
  while(!llm__is_end_mark(tmp)){
    if(tmp->data%2==0) set__add(ss,tmp->data);
    tmp=tmp->next;
  }
  return ss;
}

struct set* set__filter(const struct set* s,int(*selection)(int)){
  struct set* ss=set__empty();
  struct lelement* tmp=s->l->head;
  while(!llm__is_end_mark(tmp)){
    if(selection(tmp->data)) set__add(ss,tmp->data);
    tmp=tmp->next;
  }
  //  set__add(ss,tmp->data);(deja prise en charge par set__empty())./
  return ss;
}


struct set* set__empty(void){
  struct set* s=(struct set*)malloc(sizeof(*s));
  s->l=calloc(1,sizeof(struct link));
  (s->l)->head=calloc(1,sizeof(struct lelement));
  (s->l)->head->data=__INT_MAX__;
  (s->l)->head->next=SENTINEL;
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
    struct lelement *add0=malloc(sizeof(*add0));
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


    
