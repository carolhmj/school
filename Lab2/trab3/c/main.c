#include "genericheap.h"
#include <stdio.h>
#include <stdlib.h>

int generic_compare_int(void* a, void* b){
	if ( *((int*) a) < *((int*) b) ){
		return 1;
	} else {
		return 0;
	}
}

void print_int(void* a){
	printf(" %d ", *((int*) a));
}

int main(int argc, char const *argv[])
{
	heap *a_heap;
	a_heap = make_heap(generic_compare_int,10);
	printf("%zd %zd\n", a_heap->heap_max_size, a_heap->heap_size);
	int *e1 = (int*)malloc(sizeof(int));
	*e1 = 20;
	insert_heap(a_heap, (void*)e1 );
	int *e2 = (int*) malloc (sizeof(int));
	*e2 = 19;
	insert_heap(a_heap,  (void*) e2);
	int *e3 = (int*) malloc (sizeof(int));
	*e3 = 18;
	insert_heap(a_heap, (void*) e3);
	int e4 = 10;
	insert_heap(a_heap, (void*)(&e4));
	int e5 = 15;
	insert_heap(a_heap, (void*)(&e5));

	//print_heap(a_heap, print_int);
	//printf("%d %d %d %d %d\n", *((int*) a_heap->element_array[0]), *((int*) a_heap->element_array[1]), *((int*) a_heap->element_array[2]), *((int*) a_heap->element_array[3]), *((int*) a_heap->element_array[4]));
	void* r1 = extract_heap(a_heap);
	//printf("%d\n", *((int*) r1));
	//printf("%d %d %d %d\n", *((int*) a_heap->element_array[0]), *((int*) a_heap->element_array[1]), *((int*) a_heap->element_array[2]), *((int*) a_heap->element_array[3]));
	print_heap(a_heap, print_int);
	return 0;
}