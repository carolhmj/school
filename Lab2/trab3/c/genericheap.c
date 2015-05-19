#include "genericheap.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

heap* make_heap(compare_function comp, size_t initial_max_size){
	if (initial_max_size == 0){
		printf("Heap não pode ter tamanho 0\n");
		return NULL;
	} else {
		heap *new_heap = (heap*) malloc (sizeof(heap));
		int max_size = initial_max_size * 2;
		new_heap -> heap_max_size = max_size;
		new_heap -> heap_size = 0;
		new_heap -> comp = comp;
		new_heap -> element_array = (void*) malloc (sizeof(void*) * max_size);
	}  
}

void insert_heap(heap* h, void* obj){

	if (obj == NULL){

		printf("Não inserir valores nulos!\n");

	} else {
		
		if (h->heap_size + 1 == h->heap_max_size){
			//Mudar depois!
			size_t new_heap_max_size = h->heap_max_size * 2;
			heap *aux = h;
			h = realloc(h, sizeof(void*) * new_heap_max_size);
			if (h == NULL) {
				printf("Não foi possível aumentar a heap. Cancelando inserção...\n");
				h = aux;
				return;
			}
		} 
		
		size_t insert_index = h->heap_size;
		h->element_array[insert_index] = obj;
		sift_up(h, insert_index);
		h->heap_size += 1;
		
	}
}

void* extract_heap(heap* h){
	if (h -> heap_size == 0){

		printf("Heap vazia!\n");
		return NULL;

	} else {

		void* r = h->element_array[0];
		h->element_array[0] = h->element_array[h->heap_size-1];
		h->heap_size -= 1;
		sift_down(h, 0);
		return r;

	}
}

void sift_up(heap* h, size_t position){

	while( (position>0) && ( h->comp(h->element_array[FATHER(position)], h->element_array[position]) == 0 ) ){
		void* aux = h->element_array[position];
		h->element_array[position] = h->element_array[FATHER(position)];
		h->element_array[FATHER(position)] = aux;
		position = FATHER(position);
	} 
}

void sift_down(heap* h, size_t pos){
	size_t chosen = pos;
	size_t size = h->heap_size;

	if ((LEFTCHILD(pos) < size) && ( h->comp(h->element_array[pos], h->element_array[LEFTCHILD(pos)]) == 0 ) ) {
		chosen = LEFTCHILD(pos);
	}
	if ((RIGHTCHILD(pos) < size) && ( h->comp(h->element_array[chosen], h->element_array[RIGHTCHILD(pos)]) == 0 ) ){
		chosen = RIGHTCHILD(pos);
	}
	if (chosen!=pos){
		void* aux = h->element_array[pos];
		h->element_array[pos] = h->element_array[chosen];
		h->element_array[chosen] = aux;
		sift_down(h, chosen);
	} 
}

void print_heap(heap* h, print_function pf){
	void *begin = h->element_array, *end = h->element_array + h->heap_size - 1;
	void *cur = begin;
	printf("\n");
	for (; cur < end; ++cur) {
		//printf(" %d ", *((int*) cur));
		pf(cur);
	}
	printf("\n");
}

void free_heap(heap* h){
	void *begin = h->element_array, *end = h->element_array + h->heap_size - 1;
	void *cur = begin;
	printf("\n");
	for (; cur < end; ++cur) {
		free(cur);
	}
	free(h->element_array);
	free(h->comp);
	h->heap_max_size = 0;
	h->heap_size = 0;
	free(h);
}