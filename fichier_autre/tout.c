#include "tout.h"
#ifndef __T
#define __T
#include<stdio.h>
#include<stdlib.h>
#endif
#define SET_SIZE 10
#define SET_BOUND -1
struct set{
  int s[SET_SIZE];
};
//TAD: primitives via representation par structure et tableau d'un ensemble.
struct set* donner_vide(void){
  struct set* st=(struct set*)malloc(sizeof(struct set));
  //printf("L'ADRESSE: %p;%p",st, st->s);(evaluation plus rapide valgrind!!!)
  //ici c'est different (regardez le typecasting ci-dessus
  //car c'est comme une liste d'entiers (mais de taille non variable)
  //avec que des 0 comme pseudo-initialisation) ; c'est pour cela l'adresse
  //ne peut pas etre NULL car &=&(e1/tq:: e1 existe par garbage data e0 plutot
  //car on a fait une allocation donc e0=st->champ1(int);;;; + =>>>>  &e0=st->s.
  //donc => st->s!=NULL dans ce cas. (attention c avarie selon l a facon
  //dont on alloue).
  st->s[0]=-1;//espaces memoires accessibles par le processus via CALLOC.
  //-(60+30)=-90 errors de MOINS..///
  for(int i=1;i<10;i++) st->s[i]=0;//(redondence presque absolue
  //=>compense pas la resolution eventuelle des erreurs valgrind).//////
  return st;
}
int test_vide(struct set* st){
  if(st->s[0]!=-1) return 0;
  if(st==NULL) return 1;//si st via malloc puis st=NULL!==*~ &donner_vide
  //mais ca reste vide generalisation..(en depit du nombre de desorganisations
  //des fonctionnalites sur les blocks memoires du processus (par chainage)).
  return st->s[0]==-1;
}
int size_list(struct set* st){
  if(st==NULL) return 0;
  //if(st->s[0]==-1) return 0;
  if(test_vide(st)==1) return 0;//ajout
  int i=0;//car les valeurs sont tous >=0.
  while(i<10 && st->s[i]!=-1) i++;//plus de precision deja FAITE(ajoutee).//////
  return i;//i<10 au debut semantique evaluation des conditions sur C~JS.///
}
void set_add(struct set *st, int c){
  if(test_vide(st) && c>0){
    st->s[0]=c; st->s[1]=SET_BOUND; return;}
  //tableau trie.
  int j=0;//ajout de st->s[j] pour l'induction des +1({3 etapes (voir ci-dessus)})
  while(j<SET_SIZE && st->s[j]<c && st->s[j]>0) j++;//-16 erreurs de valgrind
  //car de MEME: on evite d'acceder a des valeurs
  //dont les adresses sont pas clean(s) => le processus ne doit pas y
  //toucher normalement car on a fait un malloc on ajoute 2 elements et ici
  //on peut parcourir donc deferencer des adresses logiquement inaccessibles
  //par le processus (type((casting)) d'allocation DYNAMIQUE) et donc
  //erreur en valgrind.[meme pour certains cas particuliers de *st ; ajout
  //de 100 par exemple puisque le DEBUT (ne parlons pas de la fin negligee par
  //la sentinelle) > max donc st->s[index_sentinelle-1]<100(rappel que le tableau est trie) donc il faudrait tester apres qui serait st->s[index_sentinelle]=-1<100 puis en finir jusqu'a set__bound mais les elements apres la sentinelle INDEX vulemain n'existent pas dans la memoire du processus.((logiquement on peut pas les lire sans les avoir initialiser apres l'allocation dynamique ce n'est pas une fuite memoire car la valeur dans le bloc adress existe mais le processus et ses pages memoires en pile/tas/System+argc+argv .. decoupees en nbr_adresses__TOTAL(processus(./exec3 |ici|)) / 2^64 (sur 64 bits nombre d'adresses possibles):::::cela donnerait le nombre de pages de 2^64 adresses possibles pas forcement referencees pour le processus d'execution ./exec3[1:] en COURS APRES demarrage after compilation en .o et tout a la fin de l'edition des liens (pas presente ici()()()). Remarque: pas de gdb car le tableau a une taille et on accede pas a un element en indice>=taille qui par deferencement ne peut plus corrspondre en terme de typage donc fuite memoire et core rejete (dumped) hexdump pour visualiser la suite des instructions binaires par acces ressources fonctionnelles via des adresses. Ou bien: a.c et b.c compiles separement avec c v.g. dans a.c et s'utilise comme fct. dans b.c => gcc a.o b.o va effectuer l'edition de liens donc rassemblement d'objets manquants aveuglement mais ./a.out va declencher suivant le fichier nm/objdump -t ./a.out(ca reste un binaire particluier) un saut d'adresse inconvenable suivant les instructions (chainage) donc depassement/forte reduction de lecture de bits => pas normale(contexte d'execution)=>segfault. C'est pour cela que le header est important si on inclut un c.h contenant le prototype de la fonction c dans a.c et b.c letape 2 -c va mal se derouler car le symbole sera de type texte par exemple alors qu'il doit etre apres le pre-processing dans le meme fichier suivant --une externe variable donc probleme=>gcc -c b.c (incluant c.h) ne compile pas. Attention; mais valgrind>gdb car detecte les acces possibles mais non ''autorises'' par LA MEMOIRE du processus qu'on joue avec avec des allocations.))  
  //st->s[j]>=c
  //on doit inserer a la position j l'element c pour que l'ordre indique:
  //s[j-1]<c et s[j+1] le prochain(modifiable)>=c.
   if(st->s[j]==-1){//Il faudrait l'inserer a la place de la sentinelle
    if(j<SET_SIZE-1){//la sentinelle peut encore se decaler a droite
      st->s[j]=c;
      st->s[j+1]=-1;
      return;}}//on rappelle que 3 conditions pour quitter la boucle...
  
   else if(j<SET_SIZE-1){//sortie de la boucle car en j;on a ::  st->s[j]>=c.
    //CORRECTION ERREUR car tous les tests +calculsvia_FONCTIONS dependent
    //de la butée=>a ne pas etre ecrasee=>en j il faut qu'il y ait un element
    //devant au max la butée (pire des cas, set_sentinel__TYPESS->s plein~~~~~)
    //donc a verifier sinon ecrasement de la butee et apres
    //en position 11 la butée qui dépasse la capacité allouée :ERROR::
    //Block was alloc'd at...(i.e. le block a ete alloue par malloc via un
    //appel de fonction externe qui rend de ce block un 'OUTIL' pour
    //effectuer des tests comme apres dans le main et n'arrivent plus a -1
    //blocquée par SET_SIZE===10 donc sortie sans avoir tester LOGIQUEMENT
    //le dernier block alloue explicitement ici ce qui devrait pas l'etre
    //car non concordance avec donner_vide() qui fixe la taille d'une structure
    //set allouée a 10 SEULEMENTTT./////////////
  int position=j;
  int limite=10;
  int len=size_list(st);
  st->s[len]=c;
  st->s[len+1]=-1;
  int y=len;
  for(int g=len;g>0;g--){
    if(st->s[g-1]>st->s[g]){
      int inter=st->s[g-1];
      st->s[g-1]=st->s[g];
      st->s[g]=inter;
    }
  }}
  //redondence peut exploser le nombre d'acces par des operations deja faites
  //et MAITRISEES donc attention au valgrind pour completer si pas sur
  //de la suite qui finalisera tout.
  return;}
void afficher(struct set* st){
  //  if(st->s[0]==0) return;(stupide)////
  /* if(test_vide(st)){ printf("Impossible, liste demarrant par la butée; donc VIDE!!\n");return ;}*/
  if(st==NULL){//2 fois en trop.. ../...      ..
    printf("Impossible: list===(nil)**\n"); return; }
  //si pas NULL donc malloc et pas de free ou bien sur la pile=>existe au moins
  //un element donc test_vide(st) marche sans errors MEMORY___CHECK=<<--+++++full.
  /* else if(test_vide(st)){printf("%s\n","-1|...(10 elmts)");
     printf("\n");}*/
  //Apparemment, si on regarde le main attentivement on affichera jamais une
  //structure vide depuis cet enlevement car redondence avec le suivant qui
  //vehicule bien l'info.//
  else if(st!=NULL){
    printf("passage par la!!!\n");
    for(int i=0;i<SET_SIZE && st->s[i]!=SET_BOUND;i++){//-3 erreurs en MOINS
      //pour l'outil de dvlmpt logiciel VALGRIND car on
      //evite d'afficher des valeurs pas affectees comme precise avant.
    printf("%d\t",st->s[i]);
  }
  /* if(i<SET_SIZE){
  for(int ii=i;ii<SET_SIZE;ii++){
    (ii==i)?printf("%d\t",-1):printf("%d\n",0);
  }
  }*///pris en charge par le chainage tres implicite de malloc.
    printf("%s\n","-1|...(10 elmts)");
    printf("\n");}
}
void free_set(struct set* st){
  st->s[0]=-1;
  for(int t=1;t<SET_SIZE;t++){
    st->s[t]=0;
  }
}
void free_set2(struct set* st){
  st=NULL;
  printf("la voici en valeur locale: %p\n",st);
  return;
}
void set_remove(struct set* ss,int c){
  //on suppose que c existe i.e. il existe p tel que ss->s[p]===c.
  int i=0;
  while(ss->s[i]<c) i++;//+condition non car par induction le set_add et
  //cas de base via set_empty qui retourne un pointeur sur un element reel du heap donc VOILA..///(on fait un remove de qlq chose deja existante en PLUS:!!); ///sinon cela ne servirait a rien.
  //i de sortie verifie: ss->s[i]===c.
  int s1[i+1];
  int j;
  for(j=0;j<i;j++){
    s1[j]=ss->s[j];
  }
  int y=0;
  while(ss->s[y]>=0) y++;
  //y==len(ss->s);;
  //=>s[y-1]==SET__BOUND;(y-1=k+1=>k=y-2)
  for(int k=j;k<y;k++){
    ss->s[k]=ss->s[k+1];
  }
  ss->s[y-1]=SET_BOUND;
  if(y-1<9){
    for(int u=y-1;u<9;u++) ss->s[u]=-1;
  }}

void afficher25(int t[], int len){
  for(int i=0;i<len;i++) printf("%d\t",t[i]);
  printf("\n\n\n");
}
int test_vide2(int t[]){
    if(t[0]==0) return 1;
    else if(t[0]==-1) return 1;
    return 0;
  }
int main(){
  //pouvoir 'initialiser un set(type set ??) vide.'
  //+ajouter/retrancher des elements selon certaines conditions.
  //en general c'est ca.
  //pouvoir le vider est aussi possible mais ca revient discretement au meme.
  struct set* s=donner_vide();
  if(s->s!=NULL && s!=NULL){
  printf("s->s de depart (tableau taille FIXE!!):\n");
  afficher(s);
  set_add(s,1);
  set_add(s,2);
  set_add(s,3);
  afficher(s);
  }
  printf("----------------\n");
  //ajout avec liste declaree depuis nous.
  struct set ss={{1,2,3,5,6,10,-1}};
  /* for(int aed2=7;aed2<SET_SIZE;aed2++) ss.s[aed2]=0;*/
  //&ss est l'adresse de ss donc apres avoir fait &ss=NULL;
  //on dispose plus d'adresse pour ss ce qui est faux car la declaration
  //de ss en variable locale sur la pile rend son adresse fixe ce qui fait
  //que ca serait pas une adresse de type dynamique c'est à dire comme les
  //autres & on alloue sur une zone qui pointe vers un entier par exemple
  //struct set3___1{int t1;}; puis &instance=new_adress pour dire que
  //on change d'adresse allouée c'est cette nouvelle qui pointera vers
  //le meme element DONC=>CAS DU programmeur gestionnaire !pas_____ici.
  //donc meme si &ss=NULL dans la fonction 1->impossible direct dans C
  //(voir PLUS BAS) et ss entrant en adresse dans la fonction est comme const
  //void* ptr=.. en declaration locale antereiure et DDOONNCC:->>>>>>>
  //   l'adresse est sur la pile deja devrait garder sa place sur la pile
  //meme si le programme marche pour des struct set* allouees dynamiquement
  //seulement donc meme si la fonction realise une affectation ca passe
  //inapercu car on manipule 2 memes types de donnees entree dortie (voir link
  //set___link SURTOUT) tout ce qui a ete fait est detruit : &ss garde sa valeur
  //la meme avant: la meme qui etait sur la pile et non sur le tas
  //=>fonctionnement de la fonction set_free2 pour 2 types de structures
  //en genre de declaration.
  afficher(&ss);
  set_add(&ss,4);
  set_add(&ss,7);
  afficher(&ss);
  free_set(&ss);
  afficher(&ss);
  printf("----------------\n");
   //free(s->s);(impossible;voirplus haut => c'est pour cela qu'elle genere
  //un maximum d'erreurs car on veut liberer un block qui forcement
  //a ete pris en charge par le systeme lui meme mais dont l'adresse est (###)
  //-1 l'adresse du contenant en TYPECASTING(ca reste le meme ~~~ordre_grandeur)
  //donc pas de gdb mais une erreur grosse qui va chercher dans toute la pile
  //ou la derniere fois s'est stocke chaque element pour vider cet espace
  //et celui qui pointe pointera vers une pile block qui prendra cette valeur
  //non par allocation et tout cela est impossible d'un point de vue processus
  //et la stack augmente considerablement le nombre d'erreurs./


  //si on veut le faire meme faux, ca serait avant.
  printf("%p###%p_____---------------------------\n",s,&(*(s->s)));
  free(s);
  //car ca va pointer vers la meme structure chainee dnc conservation de l'adresse.
  //afficher(&s);(que des 0 &new_ptr telque new_ptr=&s->s[0] qui pointera
  //vers heap element qui serait -1 deja occupe par un ptr___autre
  //qui pointe dessus.)NON!!!!!!!!!!!!!
  ///***************************  ****************************
  printf("-----test vide *s:(. \t)  %p###%p\n",/*test_vide2(s->s),*/s,(int*)&(*(s->s)));
	 //attention!!!
  //car les deux champs ont la meme adresse (& * (se -> s ) )
  //mais dans le fond les valeurs restent intacts car pas d'allocation de tableau et de free mais remplacement dans une autre zone memoire
  //c'est ce qu'on appelle: still reachable cad. données encore en libre d'acces
  //pas de probleme pour LUI mais dont la reference facultatif source a ete
  //remplacée=>still reachable ; cette 'erreur' ne doit pas du TOUT faire peur en en general.
  int* ptr_int=(int*)(&(*(s->s)));//copie conforme de l'adresse
  //valgrind se rend compte qu'il affiche des datas non prises en compte
  //=>affiche(s) apres free(s) fait autant d'erreurs que de printf (au moins..)
  //********************=>>>>
  ptr_int=(int*)calloc(10,sizeof(int));//initialisation incluse
  //allocation possible++ pour eviter des surprises car le free peut depointer
  //sur le chainage de la sentinelle et du coup deferencer tous les objets
  //en d'autres termes les rendre inaccessibles par le processeur dans la pile
  //ou dans le heap=>erreur de valgrind.
  //=>10 valeurs prises en compte automatiquement par la memoire du processus.
  //copie de la MEME adresse.
  afficher25(ptr_int,10);
  free(ptr_int);//garbage data avec pas de -1 sur size===10=>non_vide retourne 1.
  //elements donc aleatoires car plus de reference mais
  //avec still reachable inclus dans sbrk/ de malloc on retrouve un pointage
  //rendant de ces nombres des nombres en garbage data cest pour cela afficher
  //maximime jusqu'a 1 erreur prete~++ le nbr_ERRORS car il se retrouve avec
  //un processus qui pointe depuis des adresses dont le pointage n'est pas fixé
  //par l'utilisateur vu l'allocation de type dynamique tout en premier.
  printf("------//%p//----------!!!!!!!!!!!!!!!!!!!\n",&ss);
  free_set2(&ss);
  printf("------//%p//----------!!!!!!!!!!!!!!!!!!!\n",&ss);
  // &ss=NULL;(justification prq.)! ////
  //mais vu l'argument en fin; ca va tout expliquer.
  printf("le VOICI::::\n");
  afficher25(ss.s,10);
  //modification locale de st => modification du contenu => elements du tableau
  //change &*se->s reste la meme apres un free mais il y aura un autre ptr
  //telque *&ptr=new_value=>new_value=*((&))ptr_NEW{{}} qui sera par defaut le
  //premier alloué car pas de repousse dans le tas et recherche valeurs qui doivent etre affectees et suivant le tas donc retour a set__empty_____VALUES de depart donc.(les autres pointeurs sont occupes et free OK reste que des valeurs declarees dans le tas avec des pointages qui different SURTOUT apres un free ce qui change l'emplacement memoire via le nouveau pointage sur la valeur dans le tas donc la valeur du tableau en compte => reprise des valeurs classiques de la fonction qui retourne un set sentinel VIDE.)
  printf("-----test vide ss:  %d\n",test_vide(&ss));
  s=(struct set*)malloc(sizeof(struct set*));//espace memoire vide
  //reserve au processus pour le contenu de s plus particuliereument: s->s
  //=> -10 erros sinon on enleve le printf et on laisse le malloc(-//++++).///
  //s=(struct set*)0x7f56;//segmentation fault car s son adresse(possible
  //pas comme le cas &ss=NULL FAUX!! car::: s au lieu de mettre son potentiel
  //contenu ici on le mettra la (allocation DYNAMIQUE) mais l'adresse en tc
  //bien sur rend la tache difficile car s pointe vers une case memoire d'el-
  //ements non adaptee a struct set elle meme donc le parcours est de type
  //INFINI donc fuite memoire => core dumped.
  // printf("%d..%d...ETC\n",s->s[0],s->s[1]);//comme SIZE__SET int CHAMPS
  //donc tous a zero apres allocation et de meme dynamic comme ca
  //=>->s vaudrait NULL tout au debut.(voir exemple APRES!!!)
  struct set2{
    int* s2;
  };
  struct set2* ss22=(struct set2*)calloc(1,sizeof(struct set2*));//espace memoire vide
  //reserve au processus pour le contenu de s plus particuliereument: s->s
  //=> -10 erros sinon on enleve le printf et on laisse le malloc(-//++++).///
  //s=(struct set*)0x7f56;//segmentation fault car s son adresse(possible
  //pas comme le cas &ss=NULL FAUX!! car::: s au lieu de mettre son potentiel
  //contenu ici on le mettra la (allocation DYNAMIQUE) mais l'adresse en tc
  //bien sur rend la tache difficile car s pointe vers une case memoire d'el-
  //ements non adaptee a struct set elle meme donc le parcours est de type
  //INFINI donc fuite memoire => core dumped.
  // printf("%d..%d...ETC\n",s->s[0],s->s[1]);//comme SIZE__SET int CHAMPS
  //donc tous a zero apres allocation et de meme dynamic comme ca
  //=>->s vaudrait NULL tout au debut.(voir exemple APRES!!!)
  //free(&ss);impossible adresse non manipulable car non allouee
  //<=>adress no in the heap process.
  printf(" // %p. ;%p;   \n",ss22,ss22->s2);//(nil) et *(ss22->s2) fuite de mémoire
  //car necessite un deferencement d'un pointeur NULL sur une page memoire
  //reservee au processus non liée aux adresses effectives de meme typage
  //hyper complet en ROM.
  //de meme -1 erreur de valgrind
  //car DE MEME: garbage data se voit un espace clean pour le remplir PAR
  //AFFECTATION aussi mais reserve au processus pas pointe vers une adresse
  //soit UNE & qui est dans une bijection avec une adresse RAM/ROM
  //donc valgrind va vous dire que vous evrivez dans une zone pas specifiee
  //par votre processus meme si elle existe bien sur sur le tas
  //mais le vrai tas pas le tas en bijection n'a pas ete repousse tellement
  //pour sauvegarder soit-disant cette adresse par non prise en charge des l'-
  //allocation ; c'est le travail de calloc ; les 2 initialisent aux memes
  //mais calloc rend le contenu potentiellement des pointeurs accessibles par
  //lecture car inclus l'initialisation via l'allocation donc memoire
  //reservee par le processus et non pas pointage aleatoire et garbage data
  //au centre avec &source SEULEMENT donc acces aux champs_\\valeurs possible
  //mais pas prise en charge lors de l'allocation donc valgrind va nous dire
  //qu'on essaie de lire une valeur non initialisee(possiblement prise par
  //la memoire vraie mais pas tres interessant mais on peut pas lire 'value'
  //car malloc ne prend pas des cases cleans avec prise en charge (voir debut));
  //donc a retenir: valgrind peut se resoudre avec des calloc qui prennent
  //des places virtuelles en relation avec l'allocation via chainage en SOURCE
  //donc valid read of size 4 ne peut pas se faire ! par retour d'execution
  //EN valgrind.
  int i=0;
  s->s[0]=-1;
  printf("-----test vide *s:  %d\n",test_vide(s));
  //soit par pointeur apres free via set__bound soit non par pointeur
  //ce qui implique un free_set direct et un test_empty__set VALIDE.//
   struct set ss_2={{1,2,3,5,6,10,-1}};
   set_remove(&ss_2,3);
   set_remove(&ss_2,10);
   afficher(&ss_2);
   set_add(&ss_2,10);afficher(&ss_2);
   free_set(&ss_2);afficher(&ss_2);
   printf("Pour se convaincre(argument par explication syntaxique+^*^** ci-dessous\n");
   afficher25(ss_2.s,10);
   free(s);
   free(ss22);//###fait implicitement ci-haut.
   //toujours on remarque qu'apres un free() par exemple;<< free(&ss)
   //ss devient -1|10elmts.?? CAR:
   //on passe par adresse donc le contenu de certaines VALEURS relatives a cette
   //adresse vont changer si l'adresse change par exemple void swap(int*,int*)
   //;<///   si le contenu de $1 devient le contenu de $2 et reciproquement
   //ou exclusif pour eviter les 2 autres methodes1~~~2==+++++ va influencer sur la valeur de *$1 et *$2 a la sortie cest comme ici vu que st se modifie a l'interieur donc automatiquement les champs se mutent donc a la sortie la valeur des champs se verra modifiée(all).///////
  return EXIT_SUCCESS;
}
