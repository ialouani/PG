#include <assert.h>
#include <stdio.h>

#include "set_dynamic.h"

static void create_set__empty(){
  struct set s1=set__empty();
  assert(set__is_empty(&s1)==1);
  printf("\t OK (1): creation_empty_set\n");
}


static void test_set__find(){
  int* t1=(int*)calloc(10,sizeof(int));//au moins 2*size(les elements
  //significatifs.
  //!(non_garbage__date)=>en autres indices 0
  //=>si on se limite à l'ajout d'un !0 par principe du triage
  //donc: la boucle se finira automatiquement au niveau de cet indice..///
  t1[0]=1;t1[1]=2;t1[2]=3;t1[3]=4;t1[4]=6;
  //int t1[]={1,2,3,4,6};
  int t2[10];
  for(int l=0;l<9;l++) t2[l]=*(t1+l);
  assert(find(t2,5,0,5)==4);
  assert(find(t2,7,0,5)==-1);
  assert(find(t2,5,0,3)==-1);
  free(t1);
   printf("\t OK (2): finding_position__pour_insertion_eventuelle_\n");
   }

static void test_find(){
  int* s1=(int*)malloc(sizeof(int)*2);
  struct set s2={s1,2,2};
  s2.s[0]=1;
  s2.s[1]=9;
  s2.capacity=2;
  s2.size=2;
  assert(set__find(&s2,1)==1);
  assert(set__find(&s2,8)==0);
  assert(set__find(&s2,9)==1);
  assert(set__find(&s2,100)==0);
  free(s1);
  printf("\t OK (3): finding_element__boolean\n");
}
  
static void set__size_test(){
   int* s1=(int*)malloc(sizeof(int)*2);
  struct set s2={s1,2,2};
  s2.s[0]=1;
  s2.s[1]=9;
  s2.capacity=2;
  s2.size=2;
  assert(set__size(&s2)==2);
  free(s1);
  printf("\t OK (4): size_of___set\n");
}

static void test_shift_right(){
  int t[]={1,2,3,4};
  shift_right(t,1,3);
  assert(t[0]==1);
  assert(t[1]==2);
  assert(t[2]==2);
  assert(t[3]==3);
  assert(t[4]==4);
  printf("\t OK (5): shift_right__TEST\n");
}

static void test_shift_left(){
  int t[]={1,2,3,4};
  shift_left(t,0,2);
  assert(t[0]==2);
  assert(t[1]==3);
  assert(t[2]==3);
  assert(t[3]==4);
  printf("\t OK (5): shift_left__TEST\n");
}


static void adding_elmt__set(){
  struct set ens1=set__empty();
  set__add(&ens1,1);
  assert(ens1.s[0]==1);
  //printf("%zu\n",ens1.size);
  assert(ens1.capacity==ens1.size && ens1.capacity==1);
  assert(set__add(&ens1,2)==0);
  //printf("%zu\n",ens1.size);
  assert(ens1.capacity==2 && ens1.size==2);
  set__add(&ens1,3);
  assert(ens1.capacity==4 && ens1.size==3);
  assert(ens1.s[0]==1 && ens1.s[1]==2 && ens1.s[2]==3);
  set__add(&ens1,4);assert(set__add(&ens1,-1)==-1);
  assert(ens1.capacity==4 && ens1.size==4);
  assert(ens1.s[2]==3 && ens1.s[3]==4);
  printf("\t OK (6): add_to__SET\n");
  free(ens1.s);
  }

static void removing_elmt__set(){
  struct set s1=set__empty();
  set__add(&s1,1);
  set__add(&s1,2);
  set__add(&s1,3);
  set__add(&s1,4);
  //a ce stade vu ce qui precede immediat__ on a: capacity==size==4( && ).
  set__remove(&s1,2);
  assert(s1.s[0]==1 && s1.s[1]==3 && s1.s[2]==4);
  assert(s1.size==3 && s1.capacity==4);
  printf("\t OK (7): removing_from__SET\n");
  free(s1.s);
  }

static void free__SET(){
  struct set s1=set__empty();
  set__add(&s1,1);
  set__add(&s1,2);
  set__add(&s1,3);
  set__add(&s1,4);
  set__free(&s1);
  assert(set__is_empty(&s1)==1);
  //free(s1.s);(ca sert a rien (voir remarque fichier correspondant));
  printf("\t OK (8): free_of_SET\n");
  }

int main(){
  printf("%s\n",__FILE__);
  create_set__empty();
  test_set__find();
  test_find();
  set__size_test();
  test_shift_right();
  test_shift_left();
  adding_elmt__set();
  removing_elmt__set();
  free__SET();
   return 0;
}
