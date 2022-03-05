#include <stdio.h>

#include "set.h"

//le code est un test == code client
//qui force la non affectation => compilateur ne sait pas
//la def. des structures => pas inclusion des set_??.h ici.

int main () {
  printf("creation de s1 avec 5 elements\n");
  struct set* s1 = set__empty();

  set__add(s1, 111);
  set__add(s1, 222);
  set__add(s1, 333);
  set__add(s1, 444);
  set__add(s1, 555);
  
  struct set* s2 = set__empty();
  printf("affectation : s2 = s1\n");
  // *s2 = *s1; //ne connait pas les champs => erreur de manipulation
  //profonde de type incmplet.(coherent ici) d'APRES en haut.///
  //rq: meme avec compilation de set_sentinel.c par exemple
  //car affectation2.o en gcc -c implique une affectation
  //a verifier pour la traduire donc connaissance des champs
  //donc impossible.(syntaxiquement par le compilateur
  //la traduit en champs==champs donc acces en lecture incomplet type
  //=>erreur meme en gcc des 2 fichiers en meme temps.)
  //ca rejoint la conclusion SUIVANTE: le code client
  //ne peut manipuler desormais que des pointeurs sur des struct set
  //instancies.
  s2=s1;
  printf("s2 nb element:resultat (5) -> %zu\n", set__size(s2));
 
  printf("\najouter 9 dans s1\n");
  set__add(s1, 9);

  printf("9 dans s2:resultat (NON) -> %s\n", set__find(s2, 9)? "OUI" : "NON");
  printf("s2 nb elements:resultat (5) -> %zu\n", set__size(s2));
  /*
  set__free(&s1);
  //set__free(&s2);
  */
  //set__free(s22);set__free(s11);
  return 0;
}

