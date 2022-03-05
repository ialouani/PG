#include "set_sentinel.h"

//type incomplet dans set.h incluant set_sentinel.h ; ce dernier
//fixe par sa definition de struct set le TAD en terme de structure utilise.
//struct set{int s[SET_SIZE(10)];}; avec butée n'importe quel elmt<0 (-1
//pris par convention por la macro SET__BOUND qui délimite le champ du tableau)
//void set__debug_data(const struct set* s, void(*print)(int)){
/*void set__debug_data(struct set* s, void(*print)(int)){
  int i=0;
 while(s->s[i]!=SET__BOUND){
   print(s->s[i]);
   i++;}}*/

struct cursor* get_cursor(const struct set* s){
  struct cursor* crs=(struct cursor*)malloc(sizeof(*crs));
  crs->curseur=-1;//on reconnait tjrs LE FAIT que !set__is_empty.
  crs->limite_pointee=set__size(s);
  crs->ptr=&(((struct set*)s)->s[0]);//parentheses essentielles.
  //Rq: un passage par un int puis recuperation de l'adresse
  //ne marche pas car on recupere seulement la valeur
  //situee dans une case de la pile => pas meme adresse donc!
  //=>sur la meme ligne(debug) comme ##compilation_separée.
  return crs;
  //on recupere une adresse allouee qu'on considere comme un
  //repere pour le curseur de la struct set ; on l'a pas
  //encore initialise.
}

void set__crs_start(struct cursor* cr){
  cr->curseur=0;
}

void set__crs_next(struct cursor* cr){
  cr->curseur++;
  cr->ptr++;
}

int set__crs_has_next(const struct cursor* cr){
  return ((int)cr->curseur) < ((int)cr->limite_pointee);
}

void set_crs_free(struct cursor* cr){
  free(cr);
}

int set__crs_data(const struct cursor* cr){
  return *(cr->ptr);
}
  
void set__debug_data(struct set* s, void(*print)(int)){
  struct cursor* cr=get_cursor(s);
  set__crs_start(cr);
  while(set__crs_has_next(cr)){
    print(set__crs_data(cr));
    set__crs_next(cr);
  }
  free(cr);
}




//details mais implicitement => structure (+//) definissant le curseur
//independante i.e. n'entre pas dans les champs de la struct set.
/*
size_t get_cursor(const struct set* s){
  return s->cursor;
}
int get__data_cursor(const struct set* s){
  return s->s[(int)s->cursor];
}
void update_cursor(struct set* s){
  s->cursor++;
}
int valid__data_cursor(struct set* s){
  return s->s[(int)s->cursor]!=SET__BOUND;
}
void set__debug_data(struct set* s, void(*print)(int)){
  while(valid__data_cursor(s)){
    print(get__data_cursor(s));
    update_cursor(s);
  }
}
*/
  
struct set* set__filter2(const struct set* s){
  struct set* ss=set__empty();int i=0;
  while(s->s[i]!=SET__BOUND){
    if(s->s[i]%2==0) set__add(ss,s->s[i]);
    i++;}
  return ss;
}

struct set* set__filter(const struct set* s,int(*selection)(int)){
  struct set* ss=set__empty();int i=0;
  while(s->s[i]!=SET__BOUND){
    if(selection(s->s[i])) set__add(ss,s->s[i]);
    i++;}
  return ss;
}


void set__free(struct set* se){
  se->s[0]=-1;
  free(se);
}

struct set* set__empty(void){
  //on doit retourner une liste vide possible car on retourne pas &locale.
  struct set* set_empty=(struct set*)malloc(sizeof(*set_empty));
  set_empty->s[0]=SET__BOUND;
  for(int i=1;i<SET__SIZE;i++){
    set_empty->s[1]=0;
  }
  //on retourne first element -1 ca impose que les autres non significatifs
  //donc:->   len(set_empty->s)===0.
  // set_empty->cursor=0;
  return set_empty;
}

int set__is_empty(const struct set* se){
  //*se est vide si la butée est en position 1.
  return se->s[0]==SET__BOUND;
}

size_t find(int const s[], int c){
  if(c<0) return 10;
  else if(s[0]==SET__BOUND) return 0;
  //inserer un non unsigned int est impossible =>
  //retour valeur extreme dans le tabelau des positions qui est 10.
  /*size_t i=0;
  struct set ss=(const struct set)set__empty();
  for(int k=0;k<SET__SIZE;k++){//le s passe en parametre relie avec une
    //structure=>len<=SET__SIZE.
    ss.s[k]=s[k];
    }*/
  /*if(set__is_empty(&ss)) return (size_t)0;*/
  //sinon le ss n'est pas vide ; essayons de chercher la position p
  //tel que s[p]==c avec la condition de: s[i]:=SET__BOUND.
  /* while(s[i]!=SET__BOUND){
    if(s[i]==c) return i;
    i++;
    }*/
  //pas de retour de i le i a la sortie verifie: s[i]==SET__BOUND
  //en d'autres termes, le i a la fin si pas de retour est tel que
  //pour tout j<i s[j]>=0 vraie valeur du tableau s.
  // size_t j;//on a pas trouve et l'ensemble est vide => insertion a la place
  //de la sentinelle.(voir apres la gestion avec le add)
  /*for(j=0;j<i;j++){
    if(s[j]>=c) return j;
    }*/
  //le cas particulier ici si pas de retour de var :=j indique que tous
  //les elements avant la butée sont < à c;
  // return j;
  //le probleme de retour en int au lieu de size_t (long unsigned int)
  //a ete declare a la fin comme celui des $3 end/begin right/left lors
  //de la seance 1.
  size_t i=0;
  for(i=0;s[(int)i]!=SET__BOUND && s[i]<c;i++){
  }
  return i;
}

void shift_right(int s[], size_t begin){
  int n=0;
  //on va supposer que le tableau est non vide sinon ca ne sert a rien.
  //demarche: depuis la butée en position n on applique: s[h]=s[h-1] avec h--
  //ca permet d'eviter l'écrasement de valeurs EN COURS pour h>=begin+1 car
  //il faut que s[begin] reste intacte.
  while(s[n]!=SET__BOUND) n++;//a la fin: s[n]==-1<0.
  for(size_t h=n;h>=begin+1;h--){
    s[h]=s[h-1];
  }
  //puis il manque la derniere valeur qui a ete ecrasee par le tout au debut
  //donc vu tableau => ajout en n+1 de la valeur SET_BOUND pour conserver la
  //la relation avec la structure struct set_sentinelle(en___senTINELLE).
  s[n+1]=SET__BOUND;
  //le tableau est derive de la structure donc le decalage a droite va remplacer
  //la valeur set__bound par l'avant dernierer valeur et la valeur en n+1
  //(existe vu SET__SIZE et pas de depassement au niveau de end+1 comme prévu
  //avant) va receuillir au lieu de 0 (voir explication fichier test) set__bound
  //les autres valeurs suivantes si ils existent restent inchangeables car la
  //translation faite ici demarre depuis la sentinelle seulement et meme si
  //elle demarre depuis la fin (indice 9) ca va rien changer car on aura que des
  //0 pour les valeurs en position > set.sentinelle.position.
  //resume: test2.
}
/*
void shift_left(int s[], size_t end){//s[end] ne precise pas l'arrivée a la
  //sentinelle.
  int ss[SET__SIZE];//il y a end+1 elements a manipuler.
  int p=0;int end2=(int)end;
  for(p=0;p<=end2;p++){
    ss[p]=s[end2-p];
  }
 // for(int e=end2+1;e<SET__SIZE;e++){
    ss[e]=SET__BOUND;
 //   } //probleme de valgrind...
  //on considère que vu l'utilisation ulterieure que s[end]!=SET__BOUND
  //i.e. que: p a la fin ne verifie pas s[p]==SET__BOUND. => reste des elements
  //a ajouter a ss.
  int pp=p;
  int demarrage=end2;
  demarrage--;
  int demarrage2=0;
  while(pp<=end2){//il faut pas faire while ss[p]!=SET_BOUND
    //car suivant la boucle precedente, il fallait remplir bien le tableau
    //donc la condition doit etre sur une variable initialisée seulement!!!
    ss[p]=s[p];
    pp=pp+1;
  }
  while(demarrage>=0){
    s[demarrage]=ss[demarrage2];
    demarrage2++;
    demarrage--;
  }
}
*/

void shift_left(int s[], size_t end){
  for(int mn=0;mn<(int)end;mn++) s[mn]=s[mn+1];
}


//attention: le tableau est en relation avec la structure et le end
//ne marque pas la sentinelle (ca sert a rien de faire un decalage depuis une
//valeur pas significative pour le struct du tad set_en_sentinnelle) et s[end]
//ne change pas; on passe par un tableau intermediaire et on change les
//elements pas a pas en sautant le premier (principe du shift_left) car en
//en right la liberte d'ajout par une taille grande limitée par la sentinelle
//nous permet le contraire. (on detient begin/end comme prévues dans l'énoncé)


//structure ok.
//implémentation des fonctions de prototypes generalistes(changent pas
//par implementation via un header d'un TAD représentant le type ensemble
//MATHEMATIQUE)
//On doit les faire ici obligé pour permettre des tests fonctionnels
//en incluant le header set_sentinel.h et en passant en compilation separée
//le set_sentinel.o avec test_func_( .. ).o.
//Ainsi on pourrait faire les tests d'un exemple d'abstraction pour ce type
//de données SIMPLE => ### par rapport aux tests structurels qui teste
//les fonctionnalités limitées à la nature de la structure elle-meme.


int set__find(const struct set* se, int c){
  //size_t find(int const s[], int c)
  //return (int)find(se->s,(size_t)c);
  //difference avec cette fonction attention!!!
  /*int i=0;
  while(se->s[i]!=SET__BOUND){
    if(se->s[i]==c) return 1;
    i++;
  }
  return 0;
  }*/
  for(int i=0;se->s[i]!=SET__BOUND;i++){
    if(se->s[i]==c) return 1;
  }
  return 0;
}

size_t set__size(const struct set* se){
  /* int a=0;
  while(se->s[a]!=SET__BOUND) a++;
  return a;
  }*/
  int a;
  for(a=0;se->s[a]!=SET__BOUND;a++){}
  return a;
}

int set__add(struct set* se, int c){
  /*
  if(set__size(se)==SET__SIZE-1) return -1;
  //  if(set__size(se)==SET__SIZE-1) return 0;
  //
  //cas important a ne pas oublier: si l'element existe ca doit retourner
  //un code erreur car le tableau est trié d'une facon stricte!
  if(set__find(se,c)==1) return -1;
//a ne pas oublier.
  if(c<0) return -1;
  */
  if(set__size(se)==SET__SIZE-1 || set__find(se,c)==1 || c<0) return -1;
  else if(set__is_empty(se)){
    shift_right(se->s,0);
    se->s[0]=c;
    return 0;
  }
  else if(set__size(se)==SET__SIZE) return 0;//possible si on omet le test
  //premier en /* */.
  //set__size(se)<SET__SIZE et comprend au moins un element.
  else if(find(se->s,c)==(size_t)(SET__SIZE-1)) return -1;//de meme..
  else{
    int position=(int)find(se->s,c);
    if(se->s[position]==c) return 0;
    shift_right(se->s,(size_t)position);
    se->s[position]=c;
    return 0;
  }
}

int set__remove(struct set* se, int c){
  if(c<0) return -1;
  else if(set__is_empty(se)) return -1;//attention type de retour
  //indique que c'est pas possible./////
  //rien a faire (voire definition
  //primitive enlevement element liste vide).
  //pour set__find on peut pas avoir 10 car cela voudrait dire
  //que tous les elements sont inferieurs a 10 avec une se->s tab. !empty
  //donc rien a remover mais on retourne -1!
  else if(find(se->s,c)==SET__SIZE-1) return -1;//pas necessaire voir plus bas.
  //modification CAR SET__SIZE en test n'est pas tjrs 10 (macro..///)
  else{//pas 10 et pas 0 (cas de set__is_empty(se)) donc
    //soit possiblite insertion soit p exact: s[p]===c.
    int position2=find(se->s,c);//position de c future ou non ..
    if(se->s[position2]==c)
      {
      int ss3[SET__SIZE];
      int b=0;
      while(position2+b<SET__SIZE){
	ss3[b]=se->s[position2+b];
	b++;}
      //ss2 a decaler a droite
      shift_left(ss3,SET__SIZE-position2-1);
      for(int c=position2;c<SET__SIZE;c++) se->s[c]=ss3[c-position2];
      return 0;}//retour de $? en cas de succes.
    return -2;
  }}
	
//certains commentaires ont ete omis en lecture derniere car ils comportent
//des explications sur des choses corrigées apres mais dont les commentaires
//ont reste les memes mais cela explique notre demarche v1.0 de set//sentinel.







    

