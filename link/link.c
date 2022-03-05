#include <assert.h>
#include <limits.h>
#include <stdlib.h>

#include "link.h"



int llm__is_end_mark(const struct lelement *e){
  return *(int*)e->data==__INT_MAX__;
}

struct lelement* llm__next(const struct lelement* e){
  return e->next;
}

struct link lnk__empty(void){
  struct link lien;
  lien.head=SENTINEL;
  return lien;
}

struct lelement* lnk__first(const struct link* l){
  return l->head;
}


int lnk__add_head(struct link* l, struct lelement* add){
  if(add->next!=NULL) return -1;
  else{
    add->next=l->head;
    l->head=add;
    return 0;
  }
}

struct lelement *lnk__remove_head(struct link *l){
  if(llm__is_end_mark(l->head)) return NULL;
  struct lelement *EE=l->head;
  struct lelement *E=l->head->next;
  l->head->next=NULL;
  l->head=E;
  return EE;
}

int lnk__add_after(struct link* l, struct lelement* after, struct lelement* add){
  if(after==NULL || add ==NULL) return -1;
  else if(after->next==NULL || add->next!=NULL) return -1;
  else if(*(int*)after->data==__INT_MAX__ || *(int*)add->data==__INT_MAX__) return -1;
  else{
    struct lelement* E=l->head;
    while(E!=after) E=E->next;
    add->next=E->next;
    after->next=add;
    return 0;
  }
}

struct lelement *lnk__remove_after(struct link *l, struct lelement *after){
  struct lelement* EEE=after->next;
  if(llm__is_end_mark(after->next) || llm__is_end_mark(after) || after->next==NULL) return NULL;
  else{
    struct lelement* E=l->head;
    while(E!=after) E=E->next;
    struct lelement* EE=E->next->next;
    E->next->next=NULL;
    after->next=EE;
    return EEE;
  }
}

















