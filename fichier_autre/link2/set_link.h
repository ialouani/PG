#ifndef LINK
#define LINK

#include"set_link.h"

typedef enum{
  true,
false
}Bool;

struct lelement{
  int data;
  struct lelement *next;
};
struct link{
  struct lelement *head;
};
struct set{
  struct link* l;
};
struct link* link__empty();
int link__is_empty(struct link* s);
struct set* set__empty();
int set__is_empty(struct set* s);
Bool llm__is_end_mark(struct lelement* s);
struct lelement* link__first(struct link* s);
size_t set__size(struct set* s);
struct lelement* llm__next_2(struct lelement* s1);
int set__find(struct set* s, int e);
struct lelement* link__remove_after(struct link *S, struct lelement *s1);
void link__add_tail(struct link* s, struct lelement *s3);
void set__add(struct set *s, int e);
void set__remove(struct set *s, int e);
struct lelement* link__remove_head(struct link* s1);
struct set* creation_set_zero();
Bool set__find_w(struct set* s, int e);
void afficher(struct link *l);
void link__remove_tail(struct link *s);
#endif 
