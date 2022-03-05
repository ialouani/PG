#ifndef LINK
#define LINK

typedef enum{
  true,
  false
}Bool;

struct lelement{
  int data;
  struct lelement* next;
};
struct link{
  struct lelement* head;
};
struct link* link__empty();
struct lelement* link__first(struct link* s);
Bool llm__is_end_mark(struct lelement* s);
void link__add_head(struct link* s1, struct lelement* s2);
struct lelement* link__remove_head(struct link* s1);
struct lelement* llm__next_2(struct lelement* s1);
void link__add_after(struct link *S, struct lelement* s1, struct lelement *s2); 
struct lelement* link__remove_after(struct link *S, struct lelement *s1);
void link__add_tail(struct link* s, struct lelement *s3);
void link__remove_tail(struct link* s);
#endif
