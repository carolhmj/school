#include "genericheap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

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

int qsort_compare (const void * a, const void * b)
{
  if ( *(int*)a <  *(int*)b ) return -1;
  if ( *(int*)a == *(int*)b ) return 0;
  if ( *(int*)a >  *(int*)b ) return 1;
}

int main()
{
	int el_num = 1000000;
	int v[el_num];

	printf("Populando o vetor... com %d elementos\n", el_num);
	//Preenchendo o vetor
	for (int i = 0; i < el_num; i++){
		v[i] = el_num - i;
	}

	printf("Ordenando...\n");
	//Chamando a qsort e guardando o tempo
	clock_t starttime = clock(); 
	int* vord = (int*) heap_sort((void*)v, generic_compare_int, print_int, sizeof(int), el_num);
	clock_t endtime = clock();

	//Verificando a ordenação
	int ordenado = TRUE;
	for (int i = 1; i < el_num; i++){
		if (vord[i-1] > vord[i]) {
			ordenado = FALSE;
		}
	}

	//Imprimindo como está a ordenação usando o heap sort
	char* ordenacao = ordenado ? "ordenado" : "não-ordenado";
	double totaltime = (double)(endtime - starttime) / CLOCKS_PER_SEC;

	printf("O vetor está %s e o tempo que levou foi %.5lf segundos\n", ordenacao, totaltime);
	
	//Imprimindo como está a ordenação usando o qsort
	clock_t starttime_qsort = clock(); 
	qsort((void*)v, el_num, sizeof(int), qsort_compare);
	clock_t endtime_qsort = clock();
	double totaltime_qsort = (double)(endtime_qsort - starttime_qsort) / CLOCKS_PER_SEC;

	printf("A ordenação usando qsort levou %.5lf segundos\n", totaltime_qsort);

	return 0;
}