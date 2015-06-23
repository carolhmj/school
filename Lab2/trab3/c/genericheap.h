#ifndef GENERICHEAP_C_H
#define GENERICHEAP_C_H

#include <math.h>
#include <stdlib.h>

#define FATHER(N) (size_t)floor((N-1)/2)
#define LEFTCHILD(N) ((size_t)(2*N+1))
#define RIGHTCHILD(N) ((size_t)(2*N+2))

//uma função que retorna zero se os argumentos não estão em ordem
typedef int(*compare_function)(void*, void*);
//uma função que printa o elemento
typedef void(*print_function)(void*);

typedef struct heap_
{
	void* element_array;
	size_t heap_max_size;
	size_t heap_size;
	size_t element_size;
	compare_function comp;
	print_function pf;
} heap;

heap* make_heap(compare_function comp, print_function pf, size_t element_size, size_t initial_max_size);
void insert_heap(heap* h, void* obj);
void extract_heap(heap* h, void* dest);
void sift_up(heap* h, size_t position);
void sift_down(heap* h, size_t pos);
void free_heap(heap* h);
void print_heap(heap* h);
void swap(void* a, void* b, size_t bytes);
void* heap_sort(void* elements, compare_function comp, print_function pf, size_t element_size, size_t array_size);
#endif