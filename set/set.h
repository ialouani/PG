#ifndef __SET_H__
#include<stdlib.h>
#define __SET_H__

struct set;

// Return a struct set representing the empty set
struct set* set__empty(void);

// Returns non-zero if se is empty, 0 otherwise
int set__is_empty(const struct set* se);

// Returns non-zero if c belongs to se, 0 otherwise
int set__find(const struct set *se, void* c);

// Returns the number of elements in se
size_t set__size(const struct set *se);

// Adds c to se
// Returns 0 if c has been added to se, a negative value otherwise
// NB: se should not be modified if c cannot be added to se
int set__add(struct set *se, void* c);

// Removes c from se
// Returns 0 if c has been removed from se, a negative value otherwise
// NB: se should not be modified if c cannot be removed from se
int set__remove(struct set *se, void* c);
void set__free(struct set* se);

/*
struct set* set__filter2(const struct set* s);
struct set* set__filter(const struct set* s, int(*selection)(void*));
void set__debug_data(struct set* s, void(*print)(void*));
//void set__debug_data0(const struct set* s, void(*print)(int));
*/

//(a adapter apres).

//On veut pouvoir ecrire le code de set__debug_data sans pouvoir
//faire trop de details (comme generer un tmp puis test via llm__is_end_mark
//pour continuer ou non.. pour link(set_link)) ; donc ca serait
//plus judicieux de considérer le cursor comme partie independante de
//struct set sinon implicitement les operations sur le curseur
//manipule le struct set via les appels de fonctions dans set__debug_data(.V1).
//(*).//>>>>>>>>

//struct cursor;
/*size_t get_cursor(const struct set* s);
int get__data_cursor(const struct set* s);
void update_cursor(struct set* s);
int valid__data_cursor(struct set* s);*///(Version OU APPROCHE precedente(*))
//Rq: et donc, avec ceci:: les fonctions permettant de manipuler
//LE CURSEUR ne prendront pas la struct set en parametre->rejoint (*)!!./////
/*struct cursor* get_cursor(const struct set*);
//fonction de recuperation evaluee des le debut
//=>on a l'adresse du *&curseur donc apres que des operations dessus
//=>les 4 dernieres operations prendront en argument un struct cursor*
//au lieu d'un struct set*.
void set__crs_start(struct cursor* cr);
void set__crs_next(struct cursor* cr);
int set__crs_has_next(const struct cursor* cr);
int set__crs_data(const struct cursor* cr);
void set_crs_free(struct cursor* cr);*/
//voir folder ../transit2>> pour les tests sur le curseur.///(cf. TD3).///////
#endif // __SET_H__
