#include <assert.h>
#include <limits.h>
#include <stdlib.h>

#include "link.h"



int llm__is_end_mark(const struct lelement *e){
  return e->data==__INT_MAX__;
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
  //struct link *E2=l;[-Wuned-variable]::: enabled frag.//////
  l->head->next=NULL;
  l->head=E;
  return EE;
}

int lnk__add_after(struct link* l, struct lelement* after, struct lelement* add){
  if(after==NULL || add ==NULL) return -1;
  else if(after->next==NULL || add->next!=NULL) return -1;
  //else if(after->next==after || add->next==add) return -1;
  else if(after->data==__INT_MAX__ || add->data==__INT_MAX__) return -1;
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
    return EEE;//E->next mais pour EVITER des contradictions de nous..(et bien non car after->next devient after ->n ext->nex t precedent qui correspond pas a la cellule qu'on veut suprimer)
  }//autre facon on considere une variable soit un pointeur qui pointe vers le meme element qui sera bien sur lelement a supprimer en question car on manipule par l juste les champs donc l en terme d'adresse ne chage pas et donc a priori l'application sur after qui se manipule suivant un pointeur intermediaire sur lui meme note E(pointant VERS:::: after a la fin):=> after reste  intact   =>after qui contient le champ next ; le champ en general resumons: after->next ne change PAS.
}













