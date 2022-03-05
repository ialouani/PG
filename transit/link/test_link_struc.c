#include "link.h"
#ifndef __Z
#define __Z
#include "set_link.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#endif


static void test_set__empty(){
  struct set s1=set__empty();
  assert(set__is_empty(&s1)==1);
  set__free(&s1);
  printf("OK 1 pour \t set__empty && set__is_empty\n");
}

static void test_set__find(){
  struct set s2=set__empty();
  s2.l->head->data=2;
  s2.l->head->next=SENTINEL;
  struct set s1=set__empty();
  (s1.l)->head->data=1;
  (s1.l)->head->next=(s2.l)->head;
  assert(set__find(&s1,1)==1);
  assert(set__find(&s1,1)==1);
  assert(set__find(&s1,2)==1);//de meme -- (***)
  set__free(&s1);
  free(s2.l);
  printf("OK 2 pour \t set__find\n");
}


static void test_set__size(){
  struct set s2=set__empty();
  s2.l->head->data=2;
  s2.l->head->next=SENTINEL;
  struct set s1=set__empty();
  (s1.l)->head->data=1;
  (s1.l)->head->next=(s2.l)->head;
  assert(set__size(&s1)==2);
  assert(set__size(&s1)==2);
  assert(set__size(&s2)==1);//tests effets de bord..(***)_--+++++++.(+ALL.//)~
  set__free(&s1);
  free(s2.l);
  printf("OK 3 pour \t set__size\n");
}

static void test_find(){
  struct set s2=set__empty();
  s2.l->head->data=3;
  s2.l->head->next=SENTINEL;
  struct set s1=set__empty();
  (s1.l)->head->data=1;
  (s1.l)->head->next=(s2.l)->head;
  assert(find(s1.l,2)->data==1);
  assert(find(s1.l,2)->next->data==3);
  assert(find(s1.l,2)->data==1);
  assert(llm__is_end_mark(find(s1.l,2)->next->next)==1);
  set__free(&s1);
  free(s2.l);
  printf("OK 4 pour \t find\n");
}

static void test_set__add(){
  struct set s2=set__empty();
  s2.l->head->data=3;
  s2.l->head->next=SENTINEL;
  struct set s1=set__empty();
  (s1.l)->head->data=1;
  (s1.l)->head->next=(s2.l)->head;
  set__add(&s1,2);
  assert(s1.l->head->data==1);
  assert(s1.l->head->next->data==2);
  assert(s1.l->head->next->next->data==3);
  set__free(&s1);
  free(s2.l);
  struct set s3=set__empty();
  set__add(&s3,11);
  set__add(&s3,6);
  assert(s3.l->head->data==6);
  assert(llm__is_end_mark(s3.l->head->next->next)==1);
  assert(set__size(&s3)==2);
  /*free(s3.l->head->next->next);
  free(s3.l->head->next);
  free(s3.l->head);
  free(s3.l);*/
  set__free(&s3);
  printf("OK 5 pour \t set__add\n");
}

static void test_set__remove(){
  struct set s2=set__empty();
  s2.l->head->data=2;
  s2.l->head->next=SENTINEL;
  struct set s1=set__empty();
  (s1.l)->head->data=1;
  (s1.l)->head->next=(s2.l)->head;
  set__remove(&s1,1);
  assert(s1.l->head->data==2);
  assert(llm__is_end_mark(s1.l->head->next)==1);
  set__free(&s2);
  free(s1.l);
  printf("OK 6 pour \t set__remove\n");
}



int main(){
  printf("%s\n",__FILE__);
  test_set__empty();
  test_set__find();
  test_set__size();
  test_find();
  test_set__add();
  test_set__remove();
  return 0;
}
