#include "set_dynamic.h"
#include<stdio.h>
//implémenter toutes les fonctions.

struct set set__empty(void){
  struct set ens;
  ens.s=NULL;
  ens.capacity=0;
  ens.size=0;
  return ens;
}
//i.e. que une structure vide contient un pointeur NULL en terme de tableau
//representatif avec capacity=0 et size=0.(capacity nulle car aucun
//element dont l'adresse suivant ens.s est allouée).

/*
diff --git a/dynamic/set_dynamic.c b/dynamic/set_dynamic.c::>>>
+int find(int const s[], int c, int begin, int end){
+  //s trie => utilisation de dichotomie possible.
+  while(end>begin){
+    int middle=(begin+end)/2;
+    if(s[middle]==c) return middle;
+    else if(s[middle]>c) return find(s,c,middle+1,end);
+    else return find(s,c,begin,middle);
+  }
+  if(end==begin) return begin;
+  else return -1;
+}
+
*/

int set__is_empty(const struct set* se){
  return se->s==NULL;
}

int find(int const s[], int c, int begin , int end){
  int j;
  for(j=begin;j<=end;j++){
    if(s[j]>=c) break;}
  if(j<=end) return j;
  return -1;//ens.s trié d'entiers positifs.
}//reste left_right depuis ./set_dynamic.h.

int set__find(const struct set* se, int c){
  for(int i=0;i<(int)se->size;i++){
    if(se->s[i]==c) return 1;
  }
  return 0;
}

size_t set__size(const struct set* se){
  return se->size;
}

void shift_right(int s[], int begin, int end){
  //decalage depuis begin tout en gardant s[begin] intact.
  for(int k=end+1;k>=begin+1;k--){
    s[k]=s[k-1];
  }
}

void shift_left(int s[], int begin, int end){
  for(int h=begin;h<end;h++){
    s[h]=s[h+1];
  }
}

int set__add(struct set* se, int c){
  if(c<0) return -1;
  else if(set__find(se,c)==1) return -1;//element deja existant.
  else if(set__is_empty(se)){//c>=0
    //i.e. que : se->s=NULL et capacity=size=0.
    se->capacity=1;
    se->size=1;
    int size__set=(int)se->size;
    se->s=(int*)malloc(sizeof(int)*size__set);
    *(se->s)=c;
    return 0;
  }
  else{//c>=0 et pas vide.
    if(se->size==se->capacity){
      se->capacity*=2;
      se->size++;
      //printf("------%zu\n",se->size);
      int capacity__set=(int)se->capacity;
      se->s=(int*)realloc(se->s,sizeof(int)*(capacity__set));
      int position=find(se->s,c,0,(int)(se->size-2));
      if(position!=-1){//i.e. que il existe p<=end telque: s[p]>=c
	//il faut inserer en p l'element c.
	shift_right(se->s,position,(int)(se->size-2));
	se->s[position]=c;
	return 0;
      }
      else{
	//p>end
	se->s[(int)(se->size-1)]=c;
	return 0;
      }
    }
    else{
      //se->capacity>se->size;
      se->size++;
      //int capacity__set=(int)se->capacity;
      int position=find(se->s,c,0,(int)(se->size-2));
      if(position!=-1){//i.e. que il existe p<=end telque: s[p]>=c
	//il faut inserer en p l'element c.
	shift_right(se->s,position,(int)(se->size-2));
	se->s[position]=c;
	return 0;
      }
      else{
	//p>end
	se->s[(int)(se->size-1)]=c;
	return 0;
      }
    }
  }
  return -1;
}

int set__remove(struct set* se, int c){
  if(c<0) return -1;//impossible de remover un element negatif
  //dans un tableau pareil.
  else if(set__is_empty(se)) return -1;
  else if(set__find(se,c)==0) return -1;
  else if(se->size==1){//*se non vide et l'element exite>= 0.
    set__free(se);
    return 0;
  }
  else{//element existant dans une structure non vide(test++/à DERNIER()).
    int position=find(se->s,c,0,(int)(se->size-1));
    //s[position]==c d'apres ce qu'on a dit avant (2 remarques).
    shift_left(se->s,position,(int)(se->size-1));
    //se->size--;
    //se->s[(int)(se->size-1)]= on s'en fiche de cet element (argument realloc).
    se->size--;
    if(2*(se->size)==se->capacity){
      se->capacity/=2;
      se->s=realloc(se->s,sizeof(int)* (int)(se->capacity));
    }
    return 0;
  }
}

void set__free(struct set* se){
  free(se->s);
  se->s=NULL;//c'est ca ou cela se joue
  //il faut faire un free qui liberera le contenu puis se->s qui reste une
  //adresse quelconque(()) = NULL pour faire un free_set correct aux tests.
  se->size=0;
  se->capacity=0;
}




