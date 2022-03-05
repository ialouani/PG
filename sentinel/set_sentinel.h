#ifndef __SET_SENTINEL_H__
#define __SET_SENTINEL_H__
#include<stdlib.h>
#ifndef SET__SIZE
#define SET__SIZE 10
#include <stdlib.h>
#endif

#define SET__BOUND NULL 
struct set {
  void* s[SET__SIZE];
};


#include "../set/set.h"
#include <stdlib.h>

int set__is_empty(const struct set* se);

size_t find(void* const s[], void* c);

void shift_right(void* s[], size_t begin);

void shift_left(void* s[], size_t end);

void set__free(struct set* s);

#endif //__SET_SENTINEL_H__
