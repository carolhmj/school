#ifndef GENERICHEAP_H
#define GENERICHEAP_H

#include <math.h>
#include <stdlib.h>

#define FATHER(N) (size_t)floor((N-1)/2)
#define LEFTCHILD(N) (size_t)2*N+1
#define RIGHTCHILD(N) (size_t)2*N+2

//uma função que retorna zero se os argumentos não estão em ordem
typedef int(*compare_function)(void*, void*);
//uma função que printa o elemento
typedef void(*print_function)(void*);

typedef struct heap_
{
	void** element_array;
	size_t heap_max_size;
	size_t heap_size;
	compare_function comp;
} heap;

heap* make_heap(compare_function comp, size_t initial_max_size);
void insert_heap(heap* h, void* obj);
void* extract_heap(heap* h);
void sift_up(heap* h, size_t position);
void sift_down(heap* h, size_t pos);
void free_heap(heap* h);
void print_heap(heap* h, print_function pf);

#endif