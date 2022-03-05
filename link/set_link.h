#ifndef __SET_LINK__
#define __SET_LINK__

#include "../set/set.h"


struct link;
struct set {
  struct link *l;
  
};

struct lelement * find(struct link *l, void* f);


#endif /* __SET_LINK__ */
