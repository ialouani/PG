
struct set;
struct set* donner_vide(void);
int test_vide(struct set* st);
int size_list(struct set* st);
void set__add(struct set* st, int c);
void afficher(struct set* s);
void free_set(struct set* st);
void free_set2(struct set* st);
void set__remove(struct set* ss, int c);
