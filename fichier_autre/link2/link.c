#include<stdio.h>
#include<stdlib.h>
#include"link.h"

struct link* link__empty(){
  return NULL;
}

struct lelement* link__first(struct link* s){
  if (s==NULL) return NULL;
  return s->head;
}

Bool llm__is_end_mark(struct lelement *s){
  if (s->next==s) return true;
  else{return false;}
}

void link__add_head(struct link* s1, struct lelement *s2){
  if (s1==NULL){s1->head=s2;s2->next=s2;return;}
  s2->next=s1->head;
  s1->head=s2;
};

struct lelement* link__remove_head(struct link* s1){
  if (s1==NULL) {fprintf(stderr,"error:.\n");exit(EXIT_FAILURE);}
  else{
    int a1=s1->head->data;
    struct lelement *s2=malloc(sizeof(*s2));
    s2->data=a1;
    s2->next=s1->head->next;
    s1->head=s1->head->next;
    return s2;}
}

struct lelement* llm__next_2(struct lelement* s1){
  if (s1==NULL) return NULL;
  else{return s1->next;}}

void link__add_after(struct link *S, struct lelement* s1, struct lelement *s2){
  if (S==NULL || S->head==NULL) {fprintf(stderr,"error:.\n");exit(EXIT_FAILURE);}
  s2->next=s1->next;
  s1->next=s2;
}

struct lelement* link__remove_after(struct link *S, struct lelement *s1){
  if(S==NULL || S->head==NULL || s1->next==NULL || s1->next==s1){fprintf(stderr,"error:.\n");exit(EXIT_FAILURE);}
  struct lelement *s3=malloc(sizeof(*s3));
  s3->data=s1->next->data;
  s3=s1->next;
  s1->next=s1->next->next;
  return s3;}

void link__add_tail(struct link* s, struct lelement *s3){
  struct lelement* s2=malloc(sizeof(*s2));
  s2=s->head;
  while(s2->next!=s2){
    s2=s2->next;}
  s2->next=s3;
  s3->next=s3;
}

void link__remove_tail(struct link* s){
struct lelement* s2=malloc(sizeof(*s2));
  s2=s->head;
  while(s2->next->next!=s2->next){
    s2=s2->next;}
  s2->next=s2;
}
