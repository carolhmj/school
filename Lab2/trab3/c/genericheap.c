#include "genericheap.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

heap* make_heap(compare_function comp, print_function pf, size_t element_size, size_t initial_max_size){
	if (initial_max_size == 0){
		printf("Heap não pode ter tamanho 0\n");
		return NULL;
	} else {
		heap *new_heap = (heap*) malloc (sizeof(heap));
		int max_size = initial_max_size * 2;
		new_heap -> heap_max_size = max_size;
		new_heap -> heap_size = 0;
		new_heap -> comp = comp;
		new_heap -> pf = pf;
		new_heap -> element_size = element_size;
		new_heap -> element_array = (void*) malloc (element_size * max_size);
		return new_heap;
	}  
}

void insert_heap(heap* h, void* obj){

	if (obj == NULL){

		printf("Não inserir valores nulos!\n");

	} else {
		
		size_t insert_index = h->heap_size;
		char* insert_array = (char*)h->element_array;
		void* insert_position = (void*)(insert_array + h->element_size*insert_index);
		memcpy(insert_position, obj, h->element_size);
		sift_up(h, insert_index);
		h->heap_size += 1;
		
		if (h->heap_size == h->heap_max_size){
			size_t new_heap_max_size = h->heap_max_size * 1.5;
			void* temp;
			temp = realloc(h->element_array, h->element_size * new_heap_max_size);
			if (temp != NULL) {
				h->element_array = temp;
				h->heap_max_size = new_heap_max_size;
			} else {
				printf("Não foi possível aumentar a heap. Cancelando inserção...\n");
				return;
			}
		} 
	}
}

void extract_heap(heap* h, void* dest){
	if (h -> heap_size == 0){

		printf("Heap vazia!\n");
	
	} else {
		void *remove_position = h->element_array;
		memcpy(dest, remove_position, h->element_size);
		void *temp_root_element = (void*)((char*)h->element_array + h->element_size*(h->heap_size - 1));
		memcpy(remove_position, temp_root_element, h->element_size);
		h->heap_size -= 1;
		sift_down(h, 0);

	}
}

void sift_up(heap* h, size_t position){

	size_t el_size = h->element_size;

	char* array = (char*) h->element_array;
	void* pfather = (void*)(array+FATHER(position)*el_size);
	void* pactual = (void*)(array+position*el_size);

	while( (position>0) && ( h->comp(pfather, pactual) == 0 ) ){

		swap(pactual, pfather, el_size);
		position = FATHER(position);
		pfather = (void*)(array+FATHER(position)*el_size);
		pactual = (void*)(array+position*el_size);
	} 
}

void sift_down(heap* h, size_t pos){

	size_t chosen = pos;
	size_t h_size = h->heap_size;
	size_t el_size = h->element_size;

	char* array = (char*) h->element_array;

	void* pactual = (void*)(array + pos * el_size);
	void* pleft = (void*)(array + LEFTCHILD(pos) * el_size);
	void* pright = (void*)(array + RIGHTCHILD(pos) * el_size);
	void* pchosen = pactual;

	//printf("pos: %zd\n", pos);
	//printf("atual, left, right, chosen: %d %d %d %d\n", *((int*) pactual), *((int*) pleft), *((int*) pright), *((int*) pchosen));
	//print_heap(h);
	if ((LEFTCHILD(pos) < h_size) && ( h->comp(pleft, pactual) == 1 ) ) {
		chosen = LEFTCHILD(pos);
		pchosen = pleft;
	}
	if ((RIGHTCHILD(pos) < h_size) && ( h->comp(pright, pchosen) == 1 ) ){
		chosen = RIGHTCHILD(pos);
		pchosen = pright;
	}
	if (chosen != pos){
		swap(pchosen, pactual, el_size);
		sift_down(h, chosen);
	}	 
}

void print_heap(heap* h){
	char *cur = (char*)h->element_array, *end = (char*)h->element_array + h->element_size*h->heap_size;
	
	printf("heap: ");
	for (; cur < end; cur += h->element_size) {
		//printf(" %d ", *((int*) cur));
		h->pf((void*)cur);
		printf(" ");
	}
	printf("\n");
}

void free_heap(heap* h){

	free(h->element_array);
	h->element_array = NULL;
	h->comp = NULL;
	h->pf = NULL;
	h->heap_max_size = 0;
	h->heap_size = 0;
	free(h);

}

void swap(void* a, void* b, size_t bytes){

	void* aux = malloc(bytes);
	memcpy(aux, a, bytes);
	memcpy(a, b, bytes);
	memcpy(b, aux, bytes);
}