#ifndef __SET_SENTINEL_H__
#define __SET_SENTINEL_H__

#ifndef SET__SIZE
#define SET__SIZE 10
#endif

#define SET__BOUND (-1)  // sentinel

struct set {
  int s[SET__SIZE];
};

#include "../set/set.h"
#include <stdlib.h>

int set__is_empty(const struct set* se);

// returns the expected position of c in sorted array s. The returned value
// p is such that either s[p]==c, or s does not contain c and c should be
// inserted in position p to keep s sorted
size_t find(int const s[], int c);

// translates elements in s[begin..end] to s[begin+1..end+1] assuming all
// the indices are valid. The value in s[begin] is left unchanged
void shift_right(int s[], size_t begin);

// translates elements in s[begin..end] to [begin-1..end-1] assuming all
// the indices are valid. The value in s[end] is left unchanged
void shift_left(int s[], size_t end);

void set__free(struct set* s);

#endif //__SET_SENTINEL_H__
