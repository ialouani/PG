#ifndef __SET_DYNAMIC_H__
#include <stdlib.h> 
#define __SET_DYNAMIC_H__



struct set {
  void** s;
  size_t capacity;
  size_t size;
};

#include "../set/set.h"  

#include <stdlib.h>
int find(void* const s[], void* c, int begin, int end);
void shift_right(void* s[], int begin, int end);

void shift_left(void* s[], int begin, int end);


#endif //__SET_DYNAMIC_H__
