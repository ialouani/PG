#include "set_link.h"
#include "link.h"
#include<assert.h>
#include<stdio.h>

static void test_llm__is_end_mark(){
  struct link lien;
  struct lelement tete;
  tete.data=1;
  tete.next=SENTINEL;
  lien.head=&tete;
  assert(llm__is_end_mark(&tete)==0);
  assert(llm__is_end_mark(tete.next)==1);
  printf("OK(1)!: llm__is_end_mark\n");
}


static void test_llm__next(){
  struct link lien;
  struct lelement tete;
  struct lelement tete2;
  tete2.data=2;
  tete2.next=SENTINEL;
  tete.data=1;
  tete.next=&tete2;
  lien.head=&tete;
  assert(llm__next(&tete)->data==2);
  assert(llm__is_end_mark(llm__next(llm__next(&tete)))==1);
  printf("OK(2)!: llm__next\n");
}
  
static void test_lnk__empty(){
  struct link link1=lnk__empty();
  assert(llm__is_end_mark(link1.head)==1);
  printf("OK(3)!: lnk__empty\n");
}

static void test_lnk__first(){
  struct link link1;
  struct lelement tete1;
  struct lelement tete2;
  tete2.data=20;
  tete2.next=SENTINEL;
  tete1.data=10;
  tete1.next=&tete2;
  link1.head=&tete1;
  assert(lnk__first(&link1)->data==10);
  assert(llm__next(lnk__first(&link1))->data==20);
  assert(llm__is_end_mark(link1.head->next)==0);
  printf("OK(4)!: lnk__first\n");
}
  
static void test_lnk__add_head(){
  struct link lien;
  struct lelement e1;
  e1.data=12;
  struct lelement e2;
  e2.data=24;
  struct lelement e3;
  e3.data=36;
  e1.next=NULL;
  lien.head=&e2;
  e2.next=&e3;
  e3.next=SENTINEL;
  assert(lnk__add_head(&lien,&e1)==0);
  assert(lien.head->data==12);
  assert(lien.head->next->data==24);
  assert(lien.head->next->next->data==36);
  assert(llm__is_end_mark(llm__next(lien.head->next->next))==1);
  printf("OK(5)!: lnk__add_head\n");
}

static void test_lnk__remove_head(){
  struct link lien;
  struct lelement e1;
  e1.data=12;
  struct lelement e2;
  e2.data=24;
  struct lelement e3;
  e3.data=36;
  e1.next=&e2;
  lien.head=&e1;
  e2.next=&e3;
  e3.next=SENTINEL;
  assert(lnk__remove_head(&lien)!=NULL);
  assert(lien.head->data==24);
  assert(lien.head->next->data==36);
  assert(llm__is_end_mark(llm__next(lien.head->next))==1);
  assert(lnk__remove_head(&lien)->data==36);
  assert(llm__is_end_mark(lien.head->next)==1);
  assert(e1.next==NULL);
  lnk__add_head(&lien,&e2);lnk__add_head(&lien,&e1);
  struct lelement *E2=lien.head;
  lnk__remove_head(&lien);
  assert(E2->next==NULL);
  printf("OK(6)!: lnk__remove_head\n");
}

static void test_lnk__add_after(){
  struct link lien;
  struct lelement e1;
  e1.data=12;
  struct lelement e2;
  e2.data=24;
  struct lelement e3;
  e3.data=36;
  e1.next=NULL;
  lien.head=&e3;
  e2.next=SENTINEL;
  e3.next=&e2;
  assert(lnk__add_after(&lien,&e3,&e1)==0);
  assert(lien.head->next->data==12);
  assert(lien.head->next->next->data==24);
  assert(llm__is_end_mark(lien.head->next->next->next));
  printf("OK(7)!: lnk__add_after\n");
}

static void test_lnk__remove_after(){
  struct link lien;
  struct lelement e1;
  e1.data=12;
  struct lelement e2;
  e2.data=24;
  struct lelement e3;
  e3.data=36;
  e1.next=&e2;
  lien.head=&e1;
  e2.next=&e3;
  e3.next=SENTINEL;
  assert(lnk__remove_after(&lien,&e1)!=NULL);
  assert(lien.head->data==12);
  assert(lien.head->next->data==36);
  assert(llm__is_end_mark(lien.head->next->next)==1);
  assert(e2.next==NULL);
  printf("OK(8)!: lnk__remove_after\n");
}


static void test_set__empty(){
  struct set s1=set__empty();
  assert(set__is_empty(&s1)==1);
  printf("OK 1 pour \t set__empty && set__is_empty\n");
}



  int main(){
  printf("%s\n",__FILE__);
  test_llm__is_end_mark();
  test_llm__next();
  test_lnk__empty();
  test_lnk__first();
  test_lnk__add_head();
  test_lnk__remove_head();
  test_lnk__add_after();
  test_lnk__remove_after();
  test_set__empty();
  return 0;
}


/*

#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "link.h"


static void test_llm__is_end_mark(){
  struct lelement llm;
  llm.data=__INT_MAX__-1;
  llm.next=&llm;
  // printf("%p\n",&sentinel);//qui vaut sentinel en MAJ./
  assert(llm__is_end_mark((llm.next))==1);
  //free(llm.next);(c'etait TRES avant)
  printf("llm__is_end_mark OK!\n");
}

static void test_llm__next(){
  struct lelement lm3;
  lm3.data=__INT_MAX__;
  lm3.next=&lm3;
  struct lelement lm2;
  lm2.data=3;
  lm2.next=&lm3;
  struct lelement lm1;
  lm1.data=2;
  lm1.next=&lm2;
  struct lelement llm;
  llm.data=1;
  llm.next=&lm1;
  assert(llm__next(llm.next)->data==3);
  assert(llm__next(llm.next->next)->data==__INT_MAX__);
  assert(llm__is_end_mark(llm.next->next->next)==1);
  printf("llm__next OK!\n");
}


static void test_lnk__empty(){
  struct link lnk=lnk__empty();
  assert(lnk.head->data==__INT_MAX__);
  assert(lnk.head->next==lnk.head);
  //free(lnk.head);//car au fond le .head il est alloue DYNAMIQUEMENT suivant une
  //AUTRE procédure.
  //car changement allocation automatique pour les valeurs locales
  //de fonctions des tests unitaires.
  printf("lnk__empty OK!\n");
}*/
/*

static void test_lnk__first(){
  struct link lnk;
  struct lelement llm;
  lnk.head=&llm;
  struct lelement lm3;
  lm3.data=__INT_MAX__;
  lm3.next=&lm3;
  struct lelement lm2;
  lm2.data=3;
  lm2.next=&lm3;
  struct lelement lm1;
  lm1.data=2;
  lm1.next=&lm2;
  llm.data=1;
  llm.next=&lm1;
  struct lelement lm4;
  lm4.data=__INT_MAX__;
  lm4.next=&lm4;
  struct lelement llm2;
  llm2.data=__INT_MAX__-1;
  llm2.next=&lm4;
  assert(lnk__first(&lnk)->data==1);
  assert(lnk__first(&lnk)->next->data==2);
  assert(lnk__first(&lnk)->next->next->data==3);
  lnk.head=&llm2;
  assert(lnk__first(&lnk)->data==__INT_MAX__-1);
  assert(llm__is_end_mark(lnk__first(&lnk)->next)==1);
  /*
  free(llm.next->next->next);
  free(llm.next->next);
  free(llm.next);
  free(llm2.next);
  */ //pour la meme raison ; voir ce qu'on a dit avant la derniere ci-dessus fonction.
  // free(llm2.next->next);//meme si sentinelle donc meme adresse ca reste un pointeur sur qlq chose qu'on devrait la ou il pointe liberer lespace.
  //printf("lnk__first OK!\n");//RESTE 4 FREEs A GERER!!!.

//}*/
/*
static void test_lnk__add_head(){
  struct link lnk;
  struct lelement llm;
  lnk.head=&llm;
  struct lelement lm3;
  lm3.data=__INT_MAX__;
  lm3.next=&lm3;
  struct lelement lm2;
  lm2.data=3;
  lm2.next=&lm3;
  struct lelement lm1;
  lm1.data=2;
  lm1.next=&lm2;
  llm.data=1;
  llm.next=&lm1;
  struct lelement lm4;
  lm4.data=__INT_MAX__;
  lm4.next=&lm4;
  struct lelement llm2;
  llm2.data=0;
  llm2.next=NULL;
  //on va ajouter a la valeur du type link le pointage vers un head different
  //ici: llm2 au lieu de llm.
  assert(lnk__first(&lnk)->data==1);
  assert(lnk__add_head(&lnk,&llm2)==0);
  assert(lnk__first(&lnk)->data==0);
  assert(lnk__first(&lnk)->next->data==1);
  assert(lnk__first(&lnk)->next->next->data==2);
  assert(lnk__first(&lnk)->next->next->next->data==3);
  assert(llm__is_end_mark(lnk__first(&lnk)->next->next->next->next));
  /*free(llm.next->next->next);
  free(llm.next->next);
  free(llm.next);*///(meme cause)
/*printf("lnk__add_head OK!\n");
}

static void test_lnk__remove_head(){
  struct link lnk;
  struct lelement llm;
  lnk.head=&llm;
  struct lelement lm3;
  lm3.data=__INT_MAX__;
  lm3.next=&lm3;
  struct lelement lm2;
  lm2.data=3;
  lm2.next=&lm3;
  struct lelement lm1;
  lm1.data=2;
  lm1.next=&lm2;
  llm.data=1;
  llm.next=&lm1;
  struct lelement lm4;
  lm4.data=__INT_MAX__;
  lm4.next=&lm4;*/
/*
  assert(lnk__remove_head(&lnk)!=NULL);
  assert(lnk__first(&lnk)->data==2);
  assert(lnk__first(&lnk)->next->data==3);
  assert(lnk__remove_head(&lnk)->next==NULL);
  assert(lnk__first(&lnk)->data==3);
  assert(llm__is_end_mark(lnk.head)==0);*/
  //assert(lnk__remove_head(&lnk)->data==3);
  //assert(llm__is_end_mark(lnk.head)==1);(tests verifies)!/////
//  assert(lnk__first(&lnk)->data=3);//lnk__remove_head(&lnk);
  //assert(lnk__remove_head(&lnk)==NULL);
  //printf("lnk__remove_head OK!\n");
  //free(llm.next);
//}
/*
static void test_lnk__add_after(){
  struct link lnk;
  struct lelement llm;
  lnk.head=&llm;
  struct lelement lm3;
  lm3.data=__INT_MAX__;
  lm3.next=&lm3;
  struct lelement lm2;
  lm2.data=4;
  lm2.next=&lm3;
  struct lelement lm1;
  lm1.data=2;
  lm1.next=&lm2;
  llm.data=1;
  llm.next=&lm1;
  struct lelement llm2;
  llm2.data=3;
  llm2.next=NULL;
  assert(lnk__add_after(&lnk,llm.next,&llm2)==0);
  assert(lnk__first(&lnk)->data==1);
  assert(lnk__first(&lnk)->next->data==2);
  assert(lnk__first(&lnk)->next->next->data==3);
  assert(lnk__first(&lnk)->next->next->next->data==4);
  printf("lnk__add_after OK!\n");
  /*free(llm.next->next->next->next);
  free(llm.next->next->next);  
  free(llm.next);*/ //(pour la meme raison)
  // free(llm.next->next);//ici on fait un free du plus grand et si il ya un autre
  //grand similaire a l'interieur on lui fait un free(..).....
  //mais genere d'autres erreurs de valgrind..///
//}
//*/
/*
static void test_lnk__remove_after(){
  struct link lnk;
  struct lelement llm;
  lnk.head=&llm;
  struct lelement lm3;
  lm3.data=__INT_MAX__;
  lm3.next=&lm3;
  struct lelement lm2;
  lm2.data=4;
  lm2.next=&lm3;
  struct lelement lm1;
  lm1.data=2;
  lm1.next=&lm2;
  llm.data=1;
  llm.next=&lm1;
  struct lelement llm2;
  llm2.data=4;
  llm2.next=NULL;
  assert(lnk__remove_after(&lnk,llm.next)->data==4);
  lnk__add_after(&lnk,llm.next,&llm2);
  assert(lnk__remove_after(&lnk,llm.next)->next==NULL);
  assert(lnk__first(&lnk)->data==1);
  assert(lnk__first(&lnk)->next->data==2);
  assert(llm__is_end_mark(lnk__first(&lnk)->next->next));
  printf("lnk__remove_after OK!\n");
  /* free(llm.next->next);
     free(llm.next);*///(encore!!!)
  // free(llm2.next);
//}

/*
  int main(){
  printf("%s\n",__FILE__);
  test_llm__is_end_mark();
  test_llm__next();
  //test_lnk__empty();
  test_lnk__first();
  test_lnk__add_head();
  test_lnk__remove_head();
  test_lnk__add_after();
  test_lnk__remove_after();
  return 0;
}
*/
