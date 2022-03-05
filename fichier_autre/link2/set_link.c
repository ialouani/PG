#include<stdio.h>
#include<stdlib.h>
#include"set_link.h"


struct link* link__empty(){
  return NULL;
}
struct set* set__empty(){//ondef. set__empty comme un set /existe pas -<>.
  struct set* s=malloc(sizeof(*s));
  s->l=link__empty();
  return s;
}
int link__is_empty(struct link* s){
  return s==NULL || s->head==NULL ; //attention aux cas treees particuliers.
}
int set__is_empty(struct set* s){ //si s==NULL cela est equiv./à:-> s->l!().
  return s->l==NULL;
}
/*size_t set__size(struct set* s){
  int i=0;
  while(s->l->head!=s->l->head->next){i++;}
  return i;}*/ //version simple n'utilisant pas les ensembles delink.
struct lelement* link__first(struct link* s){
  return s->head; //..()
}
Bool llm__is_end_mark(struct lelement* s){
  if (s->next!=s) return 0;
  return 1;
}
size_t set__size(struct set* s){
  struct lelement* s1=malloc(sizeof(*s1));
  s1=link__first(s->l);
  int i=0;
  while (!llm__is_end_mark(s1)){i++;s1=s1->next;}
  return i+1;
}
/*int set__find(struct set* s, int e){
  struct link *s1=malloc(sizeof(*s1));
  s1->head=malloc(sizeof(struct lelement*));
  s1->head=s->l->head;
 while (s1->head->data!=e && s1->head!=s1->head->next){s1->head=s1->head->next;}
 if (s1->head!=s1->head->next) return 1;
 return 0;
 }*/ //version simple..
struct lelement* llm__next_2(struct lelement* s1){
  return s1->next;
}
int set__find(struct set* s, int e){
  //hypothese que set__find_w(s,e)==true;
  if (s->l->head->data == e) return 0;
  struct link* l1=malloc(sizeof(*l1));
  l1->head=s->l->head;
  l1->head->data=s->l->head->data;
  l1->head->next=s->l->head->next;
  int i=0;
  while(l1->head->next!=l1->head && l1->head->data!=e){
    l1->head=l1->head->next;i++;}
  l1->head=s->l->head;
  return i-1;
  if (l1->head->next->data==e) return i;
}
Bool set__find_w(struct set* s, int e){
 struct lelement *s1=malloc(sizeof(*s1));
  s1=s->l->head;
  int j=0;
  while (s1->data!=e && s1->next!=s1) {s1=llm__next_2(s1);j++;}
  if (s1->data == e) return 1;
  return 0;
}
void link__add_tail(struct link* s, struct lelement *s3){
 struct lelement* s2=malloc(sizeof(*s2));
  s2=s->head;
  while(s2->next!=s2){
    s2=s2->next;}
  s2->next=s3;
  s3->next=s3;
}
void set__add(struct set *s, int e){
  if (s->l==NULL) {fprintf(stderr,"erreur! .\n"); exit(0);}
  struct lelement *s4=malloc(sizeof(*s4));
  s4->data=e;
  link__add_tail(s->l,s4);
  //free(s3); cest facultatif.
};

struct lelement* link__remove_after(struct link *S, struct lelement *s1){
  struct lelement *s3=malloc(sizeof(*s3));
  s3->data=s1->next->data;
  s3=s1->next;
  s1->next=s1->next->next;
}//prob dans :main:::: S est tjrs le meme? ..(attention..())
struct lelement* link__remove_head(struct link* s1){
  if (s1==NULL) {fprintf(stderr,"error:.\n");exit(EXIT_FAILURE);}
  else{
    int a1=s1->head->data;
    struct lelement *s2=malloc(sizeof(*s2));
    s2->data=a1;
    s2->next=s1->head->next;
    s1->head=s1->head->next;
    return s2;}
}//a la fin pour jouer bien, il faut :main avoir:::: s->l->head=(ret.).
//nn.. ca marche dans main://tests of part1;tp1 /.
void set__remove(struct set* s, int e){
  //On suppose que set__find(s,e)==1.
  //le set__find retourne() l'indice..
  if(set__size(s)==1){s->l->head->data=0; return;}
  struct lelement *s1=malloc(sizeof(*s1));
  struct lelement *s2=malloc(sizeof(*s2));
  struct lelement *s5=malloc(sizeof(*s5));
  int k=set__find(s,e);
  if (s->l->head->data == e){s1=link__remove_head(s->l); return; }
  else if (k == set__size(s)-2 && k!=0) {link__remove_tail(s->l);}
  else{
    k=set__find(s,e);
    s2=s->l->head;
    s2->next=s->l->head->next;
    if (k==0) {s5=link__remove_after(s->l,s->l->head); return;}
    int h=0;
    while(h<k){
      s2=s2->next;
      h++;}
    s2->data=e;
    s5=link__remove_after(s->l,s2);
  }
}

void link__remove_tail(struct link* s){
struct lelement* s2=malloc(sizeof(*s2));
  s2=s->head;
  while(s2->next->next!=s2->next){
    s2=s2->next;}
  s2->next=s2;
}

struct set* creation_set_zero(){
  struct set* s=malloc(sizeof(*s));
  //return s; avec seulement ca on a un set vide (car l==0 par constrct.).
  struct link* l=malloc(sizeof(*l));
  struct lelement* S=malloc(sizeof(*S)); //allocation implique
  //declaration pour manipulation & !=NULL/ champs NULL(s).
  l->head=S;
  l->head->next=l->head;
  s->l=l;
  return s;
}
void afficher(struct link* l){
  struct link* l1=malloc(sizeof(*l1));
  l1->head=l->head;
  l1->head->data=l->head->data;
  l1->head->next=l->head->next;
  int i=0;
  while(l->head->next!=l->head){
    printf("%d--",l->head->data);
    l->head=l->head->next;i++;}
  printf("%d\n",l->head->data);
  l->head=l1->head;
}
 
