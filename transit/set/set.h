#ifndef __SET_H__
#include<stdlib.h>
#define __SET_H__

struct set;

// Return a struct set representing the empty set
//git checkout pour transit 'partiel' repository..//
struct set set__empty(void);

// Returns non-zero if se is empty, 0 otherwise
int set__is_empty(const struct set* se);

// Returns non-zero if c belongs to se, 0 otherwise
int set__find(const struct set *se, int c);

// Returns the number of elements in se
size_t set__size(const struct set *se);

// Adds c to se
// Returns 0 if c has been added to se, a negative value otherwise
// NB: se should not be modified if c cannot be added to se
int set__add(struct set *se, int c);

// Removes c from se
// Returns 0 if c has been removed from se, a negative value otherwise
// NB: se should not be modified if c cannot be removed from se
int set__remove(struct set *se, int c);
void set__free(struct set* se);
#endif // __SET_H__
