#include "genericheap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int generic_compare_int(void* a, void* b){
	if ( *((int*) a) < *((int*) b) ){
		return 1;
	} else {
		return 0;
	}
}

int generic_compare_string(void* a, void* b){
	if (strcmp((char*) a, (char*) b) < 0 ) {
		return 1;
	} else {
		return 0;
	}	
}

int generic_compare_float(void* a, void* b){
	if ( *((float*) a) < *((float*) b) ){
		return 1;
	} else {
		return 0;
	}
}

void print_int(void* a){
	printf("%d", *((int*) a));
}

void print_string(void* a){
	printf("%s", (char*) a);
}

void print_float(void* a){
	printf("%f", *((float*)a) );
}

int main()
{
	heap *a_heap;
	//a_heap = make_heap(generic_compare_int, print_int, sizeof(int), 10);
	//a_heap = make_heap(generic_compare_string, print_string, sizeof(char*),10);
	a_heap = make_heap(generic_compare_float, print_float, sizeof(float), 1);
	printf("heap max size: %zd size of elements: %zd heap_size: %zd\n", a_heap->heap_max_size, a_heap->element_size, a_heap->heap_size);
	
	//int* insert = (int*)malloc(sizeof(int)*5);
	//insert[0] = 40; insert[1] = 20; insert[2] = 18; insert[3] = 15; insert[4] = 9; insert[5] = 5;

	/*char* insert[5];

	insert[0] = "e";
	insert[1] = "d";
	insert[2] = "c";
	insert[3] = "b";
	insert[4] = "a";*/

	float insert[5];

	insert[0] = 999.99; insert[1] = 200.19; insert[2] = 178.89; insert[3] = 1000.1; insert[4] = 99.1; 

	for(int i = 0; i < 5; ++i){
		insert_heap(a_heap, (void*)(insert+i));
	}

	printf("a heap: ");
	print_heap(a_heap);

	printf("removendo...\n");
	void* dest = malloc(a_heap->element_size);
	for(int i = 0; i < 4; ++i){
		extract_heap(a_heap, dest);
		//printf("removed: %d\n", *((int*)dest));
		print_heap(a_heap);
	}

	return 0;
}