#ifndef __SET_LINK__
#define __SET_LINK__

#include "../set/set.h"


struct link;
//struct lelement; facultatif(()).
//pour savoir struct cursor quoi ? il faudrait revenir en arriere..
//sans le peu d'abstraction(abstraction ~inverse(via v?.||))
//struct set contiendrait la definition explicite-- du curseur...
//avant(les2) on avait un entier ou un pointeur sur un entier
//car dans la 1ere: l'indice qui est incremente
//et dans la deuxieme le deferencement avec incrementation du pointeur
//representant le curseur TOUT CELA POUR acceder a la donnee
//donc ici on doit avoir un struct element* pour acceder au champ
//->DATA.(* car la definition potentielle ici(revenir si besoin a la version
//de base) a struct lelement peut etre type incomplet=>pointeur
//dans les champs de la structure pour la COMPILATION<...  .//####       .
//si on veut le data encapsule via set__crs_data en argument un struct set*:>>
//IMPLIQUE: s->curseur qui va pouvoir recuperer le data
//=>s->curseur devrait etre de type: struct lelement* DONC>!!./////////
struct cursor{
  struct lelement* position;
  struct lelement* fin;
};
//au lieu d'un entier marquant la fin (len(struct set)); on aura
//pour la comparer avec la position courante une position de meme
//type marquant la fin => de type struct lelement* DONT la valeur
//sera à NULL dans get_cursor(struct set* s) et s'affectera à SENTINEL
//dans set__crs_begin(struct cursor* cr);;.///////  .//

struct set {
  struct link *l;
  //struct lelement* curseur;
};

// Find a struct lelement after which f can be inserted, or returns
// the head if the element must be inserted in head.
// pre-condition:  l sort by increasing order.
struct lelement * find(struct link *l, int f);


#endif /* __SET_LINK__ */
