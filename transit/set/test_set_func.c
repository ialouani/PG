 #include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#if defined SENTINEL
#include "../sentinel/set_sentinel.h" // FIXME
#elif defined DYNAMIC
#include "../dynamic/set_dynamic.h"
#elif defined LINK
#include "../link/set_link.h"
#include "../link/link.h"
#else
#error "A set implementation has to be defined" // -Wfatal-errors
#endif

static void test_create_set (void) {
  printf("%s", __func__);

  struct set st = set__empty();
  //printf("%p %p\n",(struct lelement*)st.l->head,SENTINEL);

  //printf("%p %p\n",(const struct lelement*)st.l->head->next,(const struct lelement*)st.l->head);
   assert(set__is_empty(&st)==1);
 
  // FIXME : should free the contents of st some day
   
   set__free(&st);
  
   printf("\tOK\n");
}

static void test_set__add(){
  struct set s1=set__empty();
  set__add(&s1,1);
  size_t len=set__size(&s1);
  assert(set__find(&s1,1)==1);
  set__add(&s1,2);
  assert(set__size(&s1)==len+1);
  set__add(&s1,1);
  assert(set__size(&s1)==len+1);
  //set__remove pareil et via set__find necessite un retour structurel de
  //set__add ce qui est pas le cas ici..////
  set__free(&s1);
  printf("Ok pour le test fonctionnel(part___ONE) de:  SET__ADD.\n");
}


int main () {
   printf("%s\n", __FILE__);
   test_create_set();
   //test fonctionnel commun car abstraction du type set donc verification axiomes
   //toujours via compilation(voir makefile)).
   test_set__add();
  return 0;
}
