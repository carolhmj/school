#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "quicksort.h"


int main(int argc, char const *argv[])
{
	//Tamanho do vetor, vetor populado aleatoriamente e uma cópia desse vetor, a ser usada na ordenação
	int tamanho, *vetor_original, *vetor_a_ordenar;
	//Lista de ponteiros para funções de quicksort
	quicksort_type lista_funcoes[] = {quicksort_naive, quicksort_naive_tripartition, quicksort_naive_selection, quicksort_naive_selection_tripartition, quicksort_naive_insertion, quicksort_naive_pointer, quicksort_opt1, quicksort_opt2, quicksort_opt2_tripartition};
	// Lista de nomes de funções de quicksort
	char *nome_funcoes[] = {"quicksort ingênuo", "quicksort ingênuo usando a tripartição", "quicksort ingênuo que usa o seleção como escolha do pivô", "quicksort ingênuo que usa o seleção com tripartição", "quicksort ingênuo que ordena o vetor por insertion sort para valores pequenos", "quicksort ingênuo que percorre o vetor por ponteiro", "quicksort com otimização de iteração e recursão sempre de um lado", "quicksort com otimização de iteração e recursão no menor lado", "quicksort com otimização de iteração, recursão no menor lado e tripartição"};
	size_t tamanho_vetor;

	do {
		printf("======================================\n");
		printf("Quantos números terá o vetor?: ");
		scanf("%d", &tamanho);
		printf("======================================\n");
	} while (tamanho < 1);

	tamanho_vetor = sizeof(int)*tamanho;

	vetor_original = (int*) malloc(tamanho_vetor);
	vetor_a_ordenar = (int*) malloc(tamanho_vetor);
		
	popular_vetor(vetor_original, tamanho);
	
	for (int i = 0; i < QTDE_FUNCOES; ++i){
		memcpy(vetor_a_ordenar, vetor_original, tamanho_vetor);

		printf("\t ---\n");
		printf("Para a função %s:\n", nome_funcoes[i]);
		executa_quicksort(lista_funcoes[i], vetor_a_ordenar, 0, tamanho-1);
	}	

	free(vetor_original);
	free(vetor_a_ordenar);
}
