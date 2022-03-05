folder opt..///
~fichier readme:
1.test set_sentinel: complexites/structurels/fonctionnels:: OK .

->complexite en boucle de tests add/remove dans une fonction est
 de complexite de 0(n**2).

->tests structurels: test de la structure shift_left/right + find/set__is_empty/set__free car specifiques au fonctionnement de la structure set implementee de la facon specifiee dans sentinel/set_sentinel.h.

->test fonctionnels: test de set__add/remove && set_is__empty/;set__find; set__size fonctions abstraites car vont etre utilisees tout au long des differentes implementations de la structure set.

Rq: developpeur Alouani Ismail
    date 27/01/2022
    fichier README a modifier au fur et a mesure..

typedef int data
<=>
#define data int 

//typedef struct person data
4)-Noms de fonctions probleme.
(solution: changer tous les noms (duplication))

Feuille4.2ème_Partie:
	typedef void* data
		=>passer de int au void* pour inclure indirectement 2 implémentations possibles:
			    en struct person->struct person* && int->int*. 
-------------------------------

_Meilleur moyen: passer le pointeur de fonction servant a la comparaison non pas aux fonctions en entier mais juste a set__empty().
_Et on le colle a la structure: par exemple pour la comparaison pour deferencer les void* via des conversions en int* ; il faudrait passer ce qui faudrait faire cad. la fonction de comparaison:
       	  	int (*compare)(void*,void*);
_En le stockant dans la structure , on a acces aux futurs nouveaux parametres de fonctions pour les manipuler (deferencer les void* par top abstraction (+ now)).

-----------------------------------------
//c'est celui le client du tad dans problem1.c qui connait le type d'ou la zone memoire a segmenter pour connaitre la vraie valeur. D'ou le passage du pointeur du pointeur de fonction dans set__empty au niveau du main, vu le retour struct set* => malloc => set->s dans le tas bien sur et les autres elements le tableau et v5 dans la pile. 
//l'utilisateur qui connait donc conversion en *(int*)a avec a est declaree en void* a ce qui fera une conversion en int* => dans le fichier qui contient le main donc le client du tad donc il le connait d'avance ET avec des macros en compilation on parametre TOUT.
=>NOUVEAU PROTOTYPE:
struct set set__empty();
->passage[3]: struct set* set__empty();//!!!sur le tas.
->passage[4]: struct set* set__empty(int(*cmp)(void*,void*));
//Comment on fait? on ajoute un pointeur de comparaison fonctionnelle generique manipulant des void* fixé par le client du TAD apres dans la struct set.Voilà.

Remarque: La sentinelle définit la butée à NULL avec ceci.

Remarque2: 2 fonctions de comparaison + ajout du passage du nouveau parametre au niveau du main soit des int a manipuler (le client qui choisit) donc on passe compare_int qui retourne *(int*)a-*(int*)b soit compare_struct__person qui fait la meme chose avec un typecasting VIA DES struct person*. (..)

----------------------------
-----------------------------------
---------------------------------------------------
Remarque3: grace a la fonction de comparison, on a un comportement attendu par comparison de valeur et non pas d'adresse, un meme 7 ajoute a s1 et s2 avec set__find sans un passage d'un ptr_function retourne vrai/faux mais avec le pointeur de fonction il compare via ce dernier les valeur d'ou les 2 valeurs finales: vrai/vrai.(problem2.c)

*****************
*****************************************
En passant une seule fonction op DE COMPARAISON, on resoud tous les 3.
->problem3.c:
avec set__add sans &op => ca trie sur les adresses
=>avec set_debug_data on se retrouve avec un non trie 
MAIS le passage dans set__add de la fonction de comparaison permet de les declasser en terme de valeurs dans le tableaud e départ sur la pile(intermediaire) au lieu des valeurs en suivi du tableau par comparaison des adresses (dernier element plus grande adresse).
*************************
**************************************
*********************************************************************
//pas la peine de passer OP dans set__add car il le recupere depuis set avec set value * -> cmp.///++.
->problem4.c: ajouter le champ copy via le prototype suivant:(l'ajouter comme 2ème parametre de set__empty)
	      	      void* (*copy)(void*);
;;
Et comme allocation dynamique (pas de retour d'adresse de variable locale)=>ajout de set__free22 en fonction de l'implémentation donc un champ pointeur de fonction qui est de prototype generique suivant:
   	 	    void (*fr)(void*);
;;
3 nouveaux CHAMPS (pointeurs de fonctions (utilite ci-dessus)) dans la struct set dans toutes les 3 implémentations: sentinel/dynamic/link..///.///

//COPIE intermediaire pour copie l'ADRESSE (on change la facon de voir le sujet) au profit du non ecrasement des super-donnees(initiales).


GIT:
**git checkout (numero du commit (patch))
**git reset --hard (renvoie en local le commit correspondant au checkout resultant).
**git push prigin HEAD:master;;
c'est fini.
reste la derniere seance.////////////


