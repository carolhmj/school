#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "quicksort.h"

int partition(int* V, int start, int end, int pivot_index){
	/*Índice que usamos ao final da função para indicar qual será a posição do vetor, todos os elementos 
	menores ou iguais que o vetor estão em posição anterior a esse índice*/
	int pivot_position = start;

	//Troca o elemento que está no pivô com o elemento que está no final
	int aux;
	aux = V[end];
	V[end] = V[pivot_index];
	V[pivot_index] = aux;

	/*Percorre o vetor, comparando o elemento atual com o pivô; se for menor, troca-o com a atual posição
	imaginada para o pivô e aumenta a posição do pivô em uma unidade, pois achamos mais um elemento menor 
	que ele*/

	for (int i = start; i < end; ++i)
	{
		if (V[i] < V[end]){
			aux = V[pivot_position];
			V[pivot_position] = V[i];
			V[i] = aux;

			pivot_position++;
		}
	}

	/*Ao final, depois de colocarmos todos os números menores que o pivô em posições anteriores a ele,
	colocamos o pivô na primeira posição à seguir, e retornamos essa posição*/

	aux = V[end];
	V[end] = V[pivot_position];
	V[pivot_position] = aux;

	return pivot_position;
}

int partition_pointer(int* V, int start, int end, int pivot_index){
	//Ponteiro que usamos para indicar a posição do pivô, ponteiro para o fim do vetor, ponteiro que percorre o vetor
	int *pivot_position_p, *end_p, *i;

	pivot_position_p = V+start;
	i = V+start;
	end_p = V+end;

	//Coloca o pivô no final do vetor	
	int aux = *end_p;
	*end_p = *(V+pivot_index);
	*(V+pivot_index) = aux;

	for (; i <= end_p; ++i)
	{
		if (*i < *end_p){
			aux = *pivot_position_p;
			*pivot_position_p = *i;
			*i = aux;

			pivot_position_p++;
		}
	}

	aux = *end_p;
	*end_p = *pivot_position_p;
	*pivot_position_p = aux;

	return pivot_position_p - V;
}

int* tripartition(int *V, int start, int end, int pivot_index){
	int *partition_positions, pivot, aux = 0, part_menor, part_maior, i;
	part_menor = i = start;
	part_maior = end;
	pivot = V[pivot_index];

	while (i<=part_maior){
		if (V[i] < pivot){
			aux = V[part_menor];
			V[part_menor] = V[i];
			V[i] = V[part_menor];

			part_menor++;
			i++; 
		} else if (V[i] > pivot) {
			aux = V[part_maior];
			V[part_maior] = V[i];
			V[i] = V[part_maior];

			part_maior--;
		} else {
			i++;
		}
	}

	partition_positions = (int*) malloc(sizeof(int)*2);
	partition_positions[0] = part_menor;
	partition_positions[1] = i;

	return partition_positions;
}

void insertionsort(int *V, int start, int end){
	int x, j;
	for (int i = start+1; i <= end; ++i)
	{
		x = V[i];
		j = i;
		while ((j>start) && (V[j-1] > x)){
			V[j] = V[j-1];
			j--;
		}
		V[j] = x;
	}
}


int selection(int *V, int start, int end, int k){
	//n é a quantidade de elementos do vetor considerado
	int n = end - start + 1; 
	if (n <= 5){
		//Se n é muito pequeno, ordenamos o vetor e pegamos o elemento correspondente 
		insertionsort(V, start, end);
		return V[k];
	} else {
		//É a quantidade de partições com 5 números em que iremos dividir o vetor
		int qtde_part = n/5;

		//Se não pudermos dividir n por 5, temos que adicionar mais uma partição para colocar os valores restantes
		if (n%5 != 0) {
			qtde_part++;
		}

		/*a e b são o começo e o fim da partição considerada, aux é um valor auxiliar, median é o 
		valor médio entre a e b, medianas_part marca o fim da partição onde as medianas de cada
		grupo serão colocadas */
		int a, b, aux, median, medianas_part = start;

		for (int i=0; i < qtde_part; ++i){
			a = start+5*i;
			b = a+4;
			if (b > end) {
				b = end;
			} 

			insertionsort(V, a, b);

			median = (a+b)/2;
			aux = V[medianas_part];
			V[medianas_part] = V[median];
			V[median] = aux;

			medianas_part++;
		}
		//Como, ao mover a última mediana para a partição, aumentamos um no valor de medianas_part, devemos diminui-lo agora
		medianas_part--;

		int mediana_local = (medianas_part+start)/2;
		selection(V, start, medianas_part, mediana_local);

		int pivot_position = partition(V, start, end, mediana_local);

		if (pivot_position == k) {
			return V[pivot_position];
		} else if (k < pivot_position) {
			return selection(V, start, pivot_position-1, k);
		} else {
			return selection(V, pivot_position+1, end, k);
		}
	}
}

int selection_tripartition(int *V, int start, int end, int k, int *partition_start, int *partition_end){
	int n = end - start + 1;

	if (n <= 5){
		insertionsort(V, start, end);
		int start_part = k, end_part = k;

		for (int i = k-1; i >= start; --i)
		{
		 	if (V[i] == V[k]) {
		 		start_part--;
		 	}
		}

		for (int i = k + 1; i <= end; ++i)
		 {
		 	if (V[i] == V[k]) {
		 		end_part++;
		 	}
		 }

		*partition_start = start_part;
		*partition_end = end_part;  
		return V[k];
	} else {
		int qtde_part = n/5;

		if (n%5 != 0) {
			qtde_part++;
		}

		int a, b, aux, median, medianas_part = start;

		for (int i=0; i < qtde_part; ++i){
			a = start+5*i;
			b = a+4;
			if (b > end) {
				b = end;
			} 
			insertionsort(V, a, b);

			median = (a+b)/2;
			aux = V[medianas_part];
			V[medianas_part] = V[median];
			V[median] = aux;

			medianas_part++;
		}

		medianas_part--;

		int *pivot_position, mediana_local = (medianas_part+start)/2;
		selection_tripartition(V, start, medianas_part, mediana_local, partition_start, partition_end);
		pivot_position = tripartition(V, start, end, medianas_part);

		*partition_start = pivot_position[0];
		*partition_end = pivot_position[1];
			
		if ((k >= pivot_position[0]) && (k <= pivot_position[1])) {
			return V[k];
		} else if (k < pivot_position[0]) {
			return selection_tripartition(V, start, pivot_position[0]-1, k, partition_start, partition_end);
		} else {
			return selection_tripartition(V, pivot_position[1]+1, end, k, partition_start, partition_end);
		}
	}
}

void quicksort_naive(int *V, int start, int end, int *calls, int *max){
	if (start<end){
		(*calls)++;
		if (*calls > *max){
			*max = *calls;
		} 
		//No caso, escolhemos o índice médio do vetor para usarmos na partição
		int p = partition(V, start, end, (start+end)/2);
		//Realizamos o procedimento novamente nas duas partes do vetor
		quicksort_naive(V,start,p-1,calls,max);
		quicksort_naive(V,p+1,end,calls,max);
		(*calls)--;
	}
}

void quicksort_naive_tripartition(int *V, int start, int end, int *calls, int *max){
	if (start<end){
		(*calls)++;
		if (*calls > *max){
			*max = *calls;
		}
		int *pivots;
		pivots = tripartition(V,start,end,(start+end)/2);

		quicksort_naive_tripartition(V,start,pivots[0]-1,calls,max);
		quicksort_naive_tripartition(V,pivots[1]+1,end,calls,max);
		(*calls)--;
	}
}

void quicksort_naive_selection(int *V, int start, int end, int *calls, int *max){
	if (start<end){
		(*calls)++;
		if (*calls > *max){
			*max = *calls;
		}
		int median = (start+end)/2;

		selection(V, start, end, median); 

		quicksort_naive_selection(V, start, median-1, calls,max);
		quicksort_naive_selection(V, median+1, end, calls,max);
		(*calls)--;
	}	
}

void quicksort_naive_selection_tripartition(int *V, int start, int end, int *calls, int *max){
	if (start<end){
		(*calls)++;
		if (*calls > *max){
			*max = *calls;
		}
		int partition_start, partition_end, median = (start+end)/2;

		selection_tripartition(V, start, end, median, &partition_start, &partition_end);
		quicksort_naive_selection_tripartition(V, start, partition_start-1, calls,max);
		quicksort_naive_selection_tripartition(V, partition_end+1, end, calls,max);
		(*calls)--;
	}	
}

void quicksort_naive_insertion(int *V, int start, int end, int *calls, int *max){
	if (start<end){
		(*calls)++;
		if (*calls > *max){
			*max = *calls;
		}
		if (end-start+1 <= INSERTION_LIMIT) {
			//Se o tamanho do intervalo for menor que INSERTION_LIMIT, utilizamos uma ordenação por inserção
			insertionsort(V, start, end);
		} else {
			int p = partition(V, start, end, (start+end)/2);

			quicksort_naive_insertion(V, start, p-1, calls,max);
			quicksort_naive_insertion(V, p+1, end, calls,max);
		}
		(*calls)--;
	}
}

void quicksort_naive_pointer(int *V, int start, int end, int *calls, int *max){
	if (start<end){
		(*calls)++;
		if (*calls > *max){
			*max = *calls;
		}
		int p = partition_pointer(V, start, end, (start+end)/2);

		quicksort_naive_pointer(V, start, p-1, calls,max);
		quicksort_naive_pointer(V, p+1, end, calls,max);
		(*calls)--;
	}
}

void quicksort_opt1(int *V, int start, int end, int *calls, int *max){
	while (start<end){
		(*calls)++;
		if (*calls > *max){
			*max = *calls;
		}
		//No caso, escolhemos o índice médio do vetor para usarmos na partição
		int p = partition(V, start, end, (start+end)/2);
		/*Realizamos o procedimento na parte direita do vetor, a outra parte não é necessária pois a chamada recursiva foi
		transformada em iteração*/
		quicksort_opt1(V,start,p-1,calls,max);
		//Estabelecemos o novo ponto de início como a parte esquerda
		start = p+1;
		(*calls)--;
	}
}
void quicksort_opt2(int *V, int start, int end, int *calls, int *max){

	while(start<end){
		(*calls)++;
		if (*calls > *max){
			*max = *calls;
		}
		//No caso, escolhemos o índice médio do vetor para usarmos na partição
		int p = partition(V, start, end, (start+end)/2);
		/*Determinamos a parte de comprimento menor resultante da partição, nela aplicamos a recursão, e aplicamos a iteração na
		parte */
		if ((p - start) < (end - p)){
			quicksort_opt2(V, start, p-1, calls,max);
			start = p+1;
		} else {
			quicksort_opt2(V, p+1, end,calls,max);
			end = p-1;
		}
		(*calls)--;

	}
}

void quicksort_opt2_tripartition(int *V, int start, int end, int *calls, int *max){

	while(start<end){
		(*calls)++;
		if (*calls > *max){
			*max = *calls;
		}

		int *pivots;
		pivots = tripartition(V,start,end,(start+end)/2);
		
		if ((pivots[0] - start) < (end - pivots[1])){
			quicksort_opt2_tripartition(V, start, pivots[0]-1,calls,max);
			start = pivots[1]+1;
			free(pivots);
		} else {
			quicksort_opt2_tripartition(V, pivots[1]+1, end, calls,max);
			end = pivots[0]-1;
			free(pivots);
		}
		(*calls)--;
	}
}

void print_values(int *V, int start, int end){
	printf("[");
	for (int i = start; i <= end; ++i)
	{
		printf("%d ", V[i]);
	}
	printf("]\n");
}

void popular_vetor(int* V, int tamanho){
	srand(time(NULL));
	for (int i = 0; i < tamanho; ++i)
	{
		V[i] = rand();
	}
}

bool ordenado(int *V, int tamanho){
	
	if (tamanho == 1) {
		return true;
	}

	for (int i = 1; i < tamanho; ++i)
	{
		if (V[i] < V[i-1]) {
			return false;
		}
	}

	return true;
}

void executa_quicksort(quicksort_type q, int *V, int start, int end){
	clock_t comeco, fim;
	int chamadas = 0;
	int max = 0;
	double tempo;

	comeco = clock();
	q(V, start, end, &chamadas, &max);
	fim = clock();

	tempo = ((double)(fim-comeco))/CLOCKS_PER_SEC;

	if (ordenado(V, start-end+1)){
		printf("\tA ordenação do vetor está correta!\n");
	} else {
		printf("\tA ordenação do vetor está errada!\n");
	}
	printf("\tTempo de execução: %f\n\tTamanho máximo da pilha: %d\n", tempo, max);

}