#ifndef COMPARATIONS_H
#define COMPARATIONS_H

#include <string.h>
#include <stdio.h>

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
	printf("%.2f", *((float*)a) );
}

int qsort_compare_int (const void * a, const void * b)
{
  if ( *(int*)a <  *(int*)b ) return -1;
  if ( *(int*)a == *(int*)b ) return 0;
  if ( *(int*)a >  *(int*)b ) return 1;
}

int qsort_compare_string(const void *a, const void *b){
	return strcmp((char*) a, (char*) b);
}

#endif