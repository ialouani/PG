#include <assert.h>
#include <stdio.h>

#include "set_sentinel.h"


static void test_set__remove_with_shift (void) {
  //declaration de structure et tests successives structurels par
  //des shift implicites via des removes (shift left dans notre implementation
  //pour etre precis) et ca revient a utiliser find(set__find~) && set__is_
  //empty non pas set__add( le contraire) implicitement.
  //  printf("%s", __func__);

  struct set st = {{1,2,3,4, SET__BOUND}};

  set__remove(&st, 3);
  assert(st.s[0] == 1);
  assert(st.s[1] == 2);
  assert(st.s[2] == 4);
  assert(st.s[3] == SET__BOUND);
  
  set__remove(&st, 4);
  assert(st.s[0] == 1);
  assert(st.s[1] == 2);
  assert(st.s[2] == SET__BOUND);
  set__remove(&st, 1);
  assert(st.s[0] == 2);
  assert(st.s[1] == SET__BOUND);

  set__remove(&st, 2);
  assert(st.s[0] == SET__BOUND);

  printf("\tOK\n");
}


static void test_set__is_empty(){
  struct set s1={{1,2,3,SET__BOUND}};
  struct set s2={{-1,2,3}};
  struct set s3={{SET__BOUND}};
  struct set s4={{-1}};
  struct set s5={{SET__BOUND,-2,3,10}};
  assert(set__is_empty(&s1)==0);
  assert(set__is_empty(&s2)==1);
  assert(set__is_empty(&s3)==1);
  assert(set__is_empty(&s4)==1);
  assert(set__is_empty(&s5)==1);
  printf("\tOK pour SET__IS_EMPTY\n");
}

static void test_set__free(){
  struct set s1={{1,2,3,-1,6}};
  //set__free(&s1);
  //assert(set__is_empty(&s1));
  printf("\tOK pour SET__FREE\n");
}


static void test_find(){
  const int t1[5]={0,2,3,4,-1};//trié + respect de la limite par la sentinelle.
  const int t2[6]={4,7,9,10,-1,3};
  const int t3[4]={SET__BOUND,10,20,33};
  const int t4[4]={-1,-3,4,2};//apres la butée, c'est pas nécessaire d'avoir
  //les elements tries; celle-ci sert vraiment a donner de l'espace d'insertion
  //pour le type tableau qui est en machine infini.(limitation par SET__SIZE).
  //(voir les prochaines primitives(TAD ensemble set_sentinelle(en sentinelle))
  //pas abus de syantaxe: const int <=> int const.
  //=>ca revient a pas modifier l'adresse du premier element.
  assert(find(t1,3)==2);
  assert(find(t1,4)==3);
  assert(find(t1,1)==1);
  assert(find(t2,10)==3);
  assert(find(t2,8)==2);
  assert(find(t2,3)==0);
  assert(find(t1,0)==0);
  assert(find(t3,20)==0);
  assert(find(t3,10)==0);
  assert(find(t4,4)==0);
  assert(find(t4,-1)==10);
  //si l'ensemble est vide limite des le depart par la sentinelle
  //il faut evidemment l'inserer suivant une insertion en premier
  //elemenet d'un sous-tableau vide(convention) pour garder un retour
  //de fonction cohérent.
  printf("\tOK pour FIND\n");
}

static void test_shift_right(){
  struct set s1={{1,2,3,4,5,SET__BOUND}};
  int ss1[SET__SIZE];
  for(int l=0;l<=5;l++){
    ss1[l]=s1.s[l];
  }
  /*
  for(int l=5;l<SET__SIZE;l++){
    ss1[l]=SET__BOUND;
  }
  */
  shift_right(ss1,1);
  assert(ss1[0]==1);
  assert(ss1[1]==2);
  assert(ss1[2]==2);
  assert(ss1[3]==3);
  assert(ss1[4]==4);
  assert(ss1[5]==5);
  assert(ss1[6]==SET__BOUND);
  //assert(ss1[7]==SET__BOUND);(implique enlever le commentaire de la derniere
  //boucle for).
  assert(s1.s[8]==0 && s1.s[9]==0);
  //2ieme test
  struct set s2={{10,20,33,42,51,67,78,SET__BOUND}};
  int ss2[SET__SIZE];
  for(int ll=0;ll<=9;ll++){
    ss2[ll]=s2.s[ll];
  }
  //now, ss1 est un tableau de taille 10===SET__SIZE et comportant les memes
  //elements que s2.s + butée avec des zeros (initialisation d'entiers
  //suivant des tableaux en structure) donc on va tester le decalage de
  //la position 2 à 4.(pas de end donc decalage en translation depuis la
  //position 2).
  shift_right(ss2,2);
  assert(ss2[0]==10);
  assert(ss2[1]==20);
  assert(ss2[2]==33);
  assert(ss2[3]==33);
  assert(ss2[4]==42);
  assert(ss2[5]==51);
  assert(ss2[6]==67);
  assert(ss2[7]==78);
  assert(ss2[8]==SET__BOUND);
  assert(ss2[9]==0);
  //le decalage demarre depuis la sentinelle + end+1 a la fin pour terminer
  //la fonction donc s[begin] reste intacte la translation est faite sans perte
  //de s[end] qui prend la place de la sentinelle et la sentinelle se decale
  //sans size_t end en $2 ; ca va rien affecter du tout car ca demarre de
  //n===set.sentinelle.position à la valeur de type size_t: begin+1 (s[++begin]
  //=s[begin]). Et ouisque on fait s[++n]=SET__BOUND donc on preserve
  //le caractere sentinelle du tableau en relation avec la structure;les
  //elements restants des zeros par exemple si declaration(et ca serait ca)
  //comme ci-dessus ((test2));;  un zero manquera parmi les zeros dans les
  //valeurs des indices apres la sentinelle.
  printf("\tOK pour shift_right\n");
}

static void test_shift_left(){
  struct set s1={{1,2,3,4,5,SET__BOUND}};
  int ss1[SET__SIZE];
  for(int l=0;l<=9;l++){
    ss1[l]=s1.s[l];
  } 
  shift_left(ss1,4);
  assert(ss1[4]==5);
  assert(ss1[3]==5);
  assert(ss1[2]==4);
  assert(ss1[1]==3);
  assert(ss1[0]==2);
  assert(ss1[5]==SET__BOUND);
  assert(ss1[6]==0);
  assert(ss1[7]==0);
  
  //2ieme test
  struct set s2={{10,20,33,42,51,67,78,SET__BOUND}};
  int ss2[SET__SIZE];
  for(int ll=0;ll<=9;ll++){//dorénavent , on procède comme ca
    //car ces tableaux seront des elements de structure apres comme le nom du
    //fichier l'indique: set_sentinel.h.
    ss2[ll]=s2.s[ll];
  }
  shift_left(ss2,3);
  assert(ss2[3]==42);
  assert(ss2[2]==42);
  assert(ss2[1]==33);
  assert(ss2[0]==20);//10 perdu comme explique avant(sentinelle/set_sentinel.c)
  assert(ss2[4]==51);
  assert(ss2[5]==67);
  assert(ss2[6]==78);
  assert(ss2[7]==SET__BOUND);
  assert(ss2[8]==0 && ss2[9]==0);//dernieres valeurs(A TESTER)
  printf("\tOK pour shift_left\n");
}


static void test_set__find(){
  const struct set t1={{0,2,3,4,-1}};
  const struct set t2={{4,7,9,10,-1,3}};
  const struct set t3={{SET__BOUND,10,20,33}};
  const struct set t4={{-1,-3,4,2}};
  assert(set__find(&t1,3)==1);
  assert(set__find(&t1,4)==1);
  assert(set__find(&t1,1)==0);
  assert(set__find(&t2,10)==1);
  assert(set__find(&t2,8)==0);
  assert(set__find(&t2,3)==0);
  assert(set__find(&t1,0)==1);
  assert(set__find(&t3,20)==0);
  assert(set__find(&t3,10)==0);
  assert(set__find(&t4,4)==0);
  assert(set__find(&t4,-1)==0);
  printf("\tOK pour SET__FIND\n");
}

static void test_set__size(){
  const struct set t1={{0,2,3,4,-1}};
  const struct set t2={{4,7,9,10,-1,3}};
  const struct set t3={{SET__BOUND,10,20,33}};
  const struct set t4={{-1,-3,4,2}};
  assert(set__size(&t1)==(size_t)(4));
assert(set__size(&t2)==(size_t)(4));
assert(set__size(&t3)==(size_t)(0));
assert(set__size(&t4)==(size_t)(0));
 printf("\tOK pour SET__SIZE\n");
}

static void test_set__add(){
  struct set se1={{1,2,4,5,SET__BOUND}};
  struct set set11={{SET__BOUND,10,20,33}};
  struct set set22={{4,7,9,10,-1,3}};
  assert(set__add(&set22,5)==0);
  assert(set__add(&set11,11)==0);
  assert(find(set11.s,11)==0);
  assert(find(set22.s,5)==1);
  assert(set__find(&set11,11)==1);
  assert(set__find(&set22,5)==1);
  set__add(&se1,3);
  assert(se1.s[0]==1);
  assert(se1.s[1]==2);
  assert(se1.s[2]==3);
  assert(se1.s[3]==4);
  /*for(int l=1;l<=4;l++){
  assert(se1.s[l-1]==l);
  }*/
  assert(se1.s[5]==SET__BOUND);
  set__add(&se1,3);
  assert(set__add(&se1,3)==-1);//adding element twice return error code integer.
  struct set se2={{1,20,40,50,SET__BOUND,4,56,12222}};
  set__add(&se2,4);
  set__add(&se2,45);
  set__add(&se2,42);
  set__add(&se2,30);
  assert(se2.s[0]==1);
  assert(se2.s[1]==4);
  assert(se2.s[2]==20);
  assert(se2.s[3]==30);
  assert(se2.s[4]==40);
  assert(se2.s[5]==42);
  assert(se2.s[6]==45);
  assert(se2.s[7]==50);
  //remarque: insertion;; on tulise uniquement shift_right donc decalage
  //vers la droite ce qui fait que tout est decale, rien de perte/à shift_left.
  assert(se2.s[8]==-1 && se2.s[9]==0);
  printf("\tOK pour SET__ADD\n");
}

static void test_set__remove(){
  
  struct set se1={{1,2,4,5,SET__BOUND}};
  set__remove(&se1,5);
  assert(se1.s[0]==1);
  assert(se1.s[1]==2);
  assert(se1.s[2]==4);
  assert(se1.s[3]==SET__BOUND);
  assert(se1.s[4]==0);
  struct set se2={{1,20,40,50,SET__BOUND,4,56,12222}};
  set__remove(&se2,1);
  set__remove(&se2,40);
  assert(se2.s[0]==20);
  assert(se2.s[1]==50);
  assert(se2.s[2]==SET__BOUND);
  assert(se2.s[3]==4);
  assert(se2.s[4]==56);
  set__remove(&se2,50);
  set__remove(&se2,50);
  assert(se2.s[0]==20);
  assert(se2.s[1]==SET__BOUND);
  assert(se2.s[2]==4);
  assert(se2.s[3]==56 && se2.s[4]==12222 && se2.s[5]==0);
  for(int ppp=6;ppp<SET__SIZE;ppp++){
    assert(se2.s[ppp]==0);
  }
  struct set set111={{-1,10,20}};
  assert(set__remove(&set111,10)==-1);
  assert(set__remove(&set111,11)!=0);
  set__add(&set111,10);
  set__add(&set111,13);//pour qu'elle soit non vide => 2 tests a prevoir.
  assert(set__remove(&set111,-1)==-1);
  assert(set__remove(&set111,-2)==-1);//test de remove sur une liste non vide
  //suite de if else if dans le programme.
  printf("\tOK pour SET__REMOVE\n");
}

static void test_set__filter(){
  struct set* s1=set__empty();
  set__add(s1,1);
  set__add(s1,2);
  set__add(s1,3);
  set__add(s1,4);
  set__add(s1,5);
  struct set* s222=set__filter2(s1);
  assert(set__find(s222,1)==0);
  assert(set__find(s222,2)==1);
  assert(set__find(s222,3)==0);
  assert(set__find(s222,4)==1);
  assert(set__find(s222,5)==0);
  set__free(s1);set__free(s222);
  printf("OK pour le set filter(critere de selection fixe)!!\n");
}

static void test_set__filter2(){
  int paire(int a){
    return a%2==0;
  }
  struct set* s1=set__empty();
  set__add(s1,1);
  set__add(s1,2);
  set__add(s1,3);
  set__add(s1,4);
  set__add(s1,5);
  struct set* s222=set__filter(s1,paire);
  assert(set__find(s222,1)==0);
  assert(set__find(s222,2)==1);
  assert(set__find(s222,3)==0);
  assert(set__find(s222,4)==1);
  assert(set__find(s222,5)==0);
  set__free(s1);set__free(s222);
  printf("OK pour le set filter(critere de selection NN fixe)!!\n");
}

static void test_set__debug_data(){
  struct set* s1=set__empty();
  set__add(s1,1);
  set__add(s1,2);
  set__add(s1,3);
  set__add(s1,4);
  set__add(s1,5);
  void print2(int b){
    printf("%d\t",b);
  }
  set__debug_data(s1,print2);
  printf("\n");
  set__free(s1);
  printf("Ok pour le test de set_debug_data avec affichage parametre\n");
}
  
int main(){//on appelera les tests ici.
  printf("%s\n", __FILE__);
  //fonctions specifiques a la structure via ../sentinel/set_sentinel.h.
  test_set__remove_with_shift();//donnée.
  
  test_set__is_empty();
  test_find();//attention..
  test_shift_right();
  test_shift_left();
  test_set__free();//a revoir..
  //fonctions generales via set/set.h.
  printf("\n\n");
  test_set__find();
  test_set__size();
  test_set__add();
  test_set__remove();test_set__filter();test_set__filter2();
  test_set__debug_data();
  return 0;
}
