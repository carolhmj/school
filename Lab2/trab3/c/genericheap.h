#ifndef GENERICHEAP_H
#define GENERICHEAP_H

#include <math.h>

#define FATHER(N) floor((i-1)/2);
#define LEFTCHLID(N) 2*i+1
#define RIGHTCHILD(N) 2*i+2

typedef (int)(*compare_function)(void*, void*);

void insert_heap(void* heap, compare_function compare, size_t bytes);
void* extract_heap(void* heap size_t bytes);
void sift_up(void* heap, size_t bytes, unsigned int position);
void sift_down(void* heap, size_t bytes, unsigned int position);

#endif