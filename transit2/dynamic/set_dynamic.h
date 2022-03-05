#ifndef __SET_DYNAMIC_H__
#include <stdlib.h> //reconnaitre le type size_t
#define __SET_DYNAMIC_H__


struct cursor{
  size_t position;//en theorie il ne sert a rien juste a has_next
  //pour utiliser que le CURSEUR=>comparaison de la position avec
  //le champ du curseur:LEN.
  int len;//pas modifiable(const struct set*!!!!!).///
  int* ptr;
};


struct set {
  int* s;
  size_t capacity;//liée au nombre d'éléments alloués au début
  size_t size;//nombre d'éléments significatifs <= capacity(== || ok)
};//modifiables apres (les 2 champs apres 1er appel d'un test general).

#include "../set/set.h" //fonction abstraites a implementer dans 
//./set_sentinel.c.
#include <stdlib.h>//voir les formats macros #if,elseif,done dans ./set/set.h.
//fonctions specifiques au tableau de capacite variable.

//int set__is_empty(const struct set* se);//verifie si le tableau est vide.()
//2 fois declarées..(mais pas implementées).

int find(int const s[], int c, int begin, int end);
//return p entre begin et end tel que s[p]==c ou bien où il faudrait l'insérer
//i.e. p/s[p]>=c => insertion en position p. (on cherche entre begin et end: c).
//attention: s[p]>=c p --retour. (si pas existence donc s[end]<c 
//=>il faut que ca retourne end pour que ca signale qu'il faut
//augmenter la taille soit en terme de structure actuelle le champ
//size eventuellement capacity..)

void shift_right(int s[], int begin, int end);
//decalage a droite indices valides.
//le end represente l'indice du dernier element de s..

void shift_left(int s[], int begin, int end);
//begin est toujours 0.(())
//de meme mais a gauche.

#endif //__SET_DYNAMIC_H__
