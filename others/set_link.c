#include<stdlib.h>
#ifndef __F
#define __F
#include "set_link.h"
#include<limits.h>
#include<stdio.h> //pour quelques petits petits debegguages .((de code))///
#include "link.h"
#endif

struct set set__empty(void){
  //struct link lien2=lnk__empty();//de la meme maniere
  //opposition a reduire les parametres pour passer du temps a penser au
  //global.
  struct set* s=(struct set*)malloc(sizeof(struct set));
  //s.l=&lien2;
  /* s.l->head=SENTINEL;
     int entier=SENTINEL->data;*/
  //s.l->head->data=entier;
  // s.l->head->next=s.l->head;
  s->l=(struct link*)malloc(sizeof(struct link));
  s->l->head=SENTINEL;
  return *s;
}


int set__is_empty(const struct set* se){
  return se->l->head==SENTINEL;
  // printf("%d\n",(struct lelement*)se->l->head==SENTINEL);
  //return ((struct lelement*)(se->l->head)==SENTINEL-1);
  // return (struct lelemet*)se->l->head->next==(struct lelement*)se->l->head;
}


struct lelement* find(struct link* l, int f){
  if(f<0) return NULL;
  else if(l->head->data>=f) return l->head;
  else{
    struct lelement* tete=l->head;
    while(!llm__is_end_mark(tete->next) && tete->next->data<f) tete=tete->next;
    if(tete->next->data>=f && !llm__is_end_mark(tete->next)) return tete;//<=f c'est la
    //ou on appliquera lnk__add_after(l,&(*element)).
    //si egalite va l'inserer avant: reste meme chose.
    //si pour SET__REMOVE: <= soit == si !!set__find(l->head,&(*element))
    //donc ca va retourner si >= l'indice de < soit apres lnk__remove_after
    //$2_func.() == index///en cet index on a une valeur < $2_func.().
    else return NULL;
  }
}



size_t set__size(const struct set* se){
  if(set__is_empty(se)) return 0;
  else if(se->l->head->data==__INT_MAX__) return 0;
  //bcp. de commentaires => on va faire un petit clean apres
  //pour en d'autres sortes LE BUT eviter les redondances
  //et classifier les confitions par forté et les regrouper au maximum
  //par des connecteurs logiques ; c'est MIEUX ET préférable.
  else{
    size_t length=0;
    struct lelement* se2=se->l->head;
    while(se2!=SENTINEL){
      se2=se2->next;
      length+=1;
    }
    return length;
  }
}



int set__find(const struct set* se, int c){
  if(c<0) return -1;
  if(se->l->head->data==c) return 1;
  else{
    int len=0;
    struct lelement* tete=se->l->head->next;
    while(tete!=SENTINEL && tete->data!=c)
      {tete=tete->next;len++;}
    if(tete->data==c && len<(int)set__size(se)) return 1;
    else return 0;
  }
  return -1;
}



int set__add(struct set *se, int c){
  if(c<0) return -1;
  else if(set__size(se)==0){
    se->l->head=(struct lelement*)malloc(sizeof(*(se->l->head)));
    //on dispose deja de se->l->Head qui vaut la sentinelle en & (SENTINEL)
    //donc as besoin de rellouer une deuxieme fois encore...
    se->l->head->data=c;
    se->l->head->next=SENTINEL;
    return 0;
  }
  //s->l->Head est de type adresse d'une encapsulation avec les autres fonctions
  //preliminaires on sent plus que ca on sent que ca ressemble a un int* s->l->Head en general comme structure chainee est comme un tableau dont chaque element possede un couple COMME valeur $2.;;couple///<=><=>adresse de l'element premier
  //du prochain qui le suit en general dans un tableau vu de loin donc le redimiosonnement reste necessaire en plus:!!(mais a maitriser)**********************
  else if (set__size(se)>0){
  struct lelement add0;
  add0.data=c;
  add0.next=NULL;
  struct lelement* ici=find(se->l,c);
  /*size_t grandeur =sizeof(*(se->l->head));
  grandeur++;
  se->l->head=(struct lelement*)realloc(se->l->head,grandeur);
  */
  if(ici==se->l->head) {lnk__add_head(se->l,&add0);return 0;}
  else{lnk__add_after(se->l,ici,&add0); return 0;}
  }
  //  free(add0);(c'etait au debut)
  return -1;
}//on a traite tous les cas pas la peine d'en rajouter un return -1 pour etreSur.(mais on doit car sinon on aurait le fameux warning qui est connu:
//control reaches end of non_void function..)



int set__remove(struct set* se, int c){
  if(c>=0 && set__find(se,c)==1 && set__size(se)==1){
    se->l->head=SENTINEL;
    //free(se->l);ca sert a rien car on veut se rapprocher d ela structure vide
    //cad. avec une adresse se->L valide mais se->l pointe vers la 'SENTINEL'
    return 0;
  }
  else if(c<0 || set__find(se,c)==0) return -1;//set__size(se)>=1
  else if(set__size(se)>0){
  struct lelement* ici=find(se->l,c);
    /*size_t grandeur =sizeof(*(se->l->head));
  grandeur--;
  se->l->head=(struct lelement*)realloc(se->l->head,grandeur);*/
  //induite directement...(on en detaille apres ce point par rapport
  //aux parmaetres de la dynamique).//////////
  if(se->l->head==ici) {lnk__remove_head(se->l);return 0;}
  else{lnk__remove_after(se->l,ici); return 0;}//attention car s->l->head est via s->l allouee e .. ;;  ->HEAD
  //aussi car pour se debarassser de sentinel faute de variable globale(il faut
  //en avoir plusieurs) et que lnk__empty peut pas etre utilise (raison2-) donc
  //il faut allouer les 2 et les maitriser en terde de size surtout non s->l qui
  //est une adresse seulement et !(surtout non )<=>   surtout s->l->head car
  //ca represente le commencement de la liste.(voir dans le remove pour plus d'explications);;
  }
  return -1;
  //de meme.(voir plus haut;fin de la fonction set__add);;///
}



void set__free(struct set* s){
  /*struct link lnk=lnk__empty();
    se->l=&lnk;*/ //(&varaiable locale depilee pour les futures images
  //des pages processus memoire--.
  // free(se->l->head);
  /*free(se->l);
   */
  //automatiquement deferencement des donnees comme se->l->head
  //donc vidage par desapointage dont la methode est fixee au depart.
  //  se->l->head=SENTINEL;(non car free => zone interdite desormais par
  //le processus jusqu'a future allocation) && free definit cela ici.////
  //se->l->head=SENTINEL;
  struct lelement* res=(s->l)->head;
  while(!llm__is_end_mark(res)){
    struct lelement tmp;
    tmp=*res;
    tmp=*(tmp.next);
    free(res);
  }
  free(s->l);  
}










  
