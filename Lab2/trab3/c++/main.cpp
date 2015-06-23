#include "genericheap.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <string>
#include <algorithm>

int main()
{
	//Criando o vetor de elementos
	int el_num = 1000000;
	int v[el_num];
	for (int i = 0; i < el_num; i++){
		v[i] = (el_num - i);
	}


	//Criando a heap e a ordenação, e medindo o tempo
	clock_t starttime = clock(); 
	
	genheap::GenericHeap<int> heap((int*)v, el_num);
	std::vector<int> vord = heap.heap_sort();

	clock_t endtime = clock();
	double dif = (double)(endtime - starttime) / CLOCKS_PER_SEC;

	//Checando a ordenação
	bool ordered = true;
	for (int i = 1; i < el_num; i++){
		if (vord[i-1] > vord[i]){
			ordered = false;
		}
	}

	//Imprimindo o status da ordenação e o tempo 
	std::string ordenacao = ordered ? "ordenado" : "não-ordenado";
	std::cout << "O vetor está " << ordenacao << " e o tempo que levou é: " << dif << " segundos\n";

	//Usando o std::sort do header algorithm	

	/*clock_t starttime_sort = clock(); 
	
	std::sort(v.begin(), v.end());

	clock_t endtime_sort = clock();
	double dif_sort = (double)(endtime_sort - starttime_sort) / CLOCKS_PER_SEC;

	std::cout << "Usando o template std::sort do header algorithm, o tempo é: " << dif_sort << " segundos\n";*/

	return 0;
}
