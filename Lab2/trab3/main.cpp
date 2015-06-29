#include "c/genericheap.h"
#include "c++/genericheap.h"
#include "comparations.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstring>

int main(){
	//Inicia gerador de números aleatórios
	std::srand(std::time(0));

	//Para medição de tempos
	clock_t comeco, fim;
	double duracao;

	//Gera vetor de inteiros gerados aleatóriamente 
	int num_vetor_tam = 1000000;
	int num_vetor[num_vetor_tam];
	for (int i = 0; i < num_vetor_tam; i++){
		num_vetor[i] = std::rand();
	}

	std::cout << "Para um vetor de " << num_vetor_tam << " inteiros gerados aleatoriamente, os tempos de ordenação são...\n";

	//Ordena os vetores usando diferentes funções de ordenação
	comeco = clock();
	void* ordenado_c = heap_sort((void*) num_vetor, generic_compare_int, print_int, sizeof(int), num_vetor_tam);
	fim = clock();
	duracao = (double)(fim-comeco)/CLOCKS_PER_SEC; 

	std::cout << "\tHeapsort com heap genérico em C: " << duracao << " segundos\n";

	comeco = clock();
	genheap::GenericHeap<int> heap((int*) num_vetor, num_vetor_tam);
	std::vector<int> ordenado_cplus = heap.heap_sort();
	fim = clock();
	duracao = (double)(fim-comeco)/CLOCKS_PER_SEC; 

	std::cout << "\tHeapsort com heap template em C++: " << duracao << " segundos\n";

	std::vector<int> num_vetor_2(num_vetor, num_vetor+num_vetor_tam);
	comeco = clock();
	std::sort(num_vetor_2.begin(), num_vetor_2.end());
	fim = clock();
	duracao = (double)(fim-comeco)/CLOCKS_PER_SEC; 

	std::cout << "\tHeapsort com a função sort definida no header algorithm do C++: " << duracao << " segundos\n";

	comeco = clock();
	std::qsort(num_vetor, num_vetor_tam, sizeof(int), qsort_compare_int);
	fim = clock();
	duracao = (double)(fim-comeco)/CLOCKS_PER_SEC; 

	std::cout << "\tHeapsort com a função qsort definida no stdlib do C: " << duracao << " segundos\n";


	//Agora criando o vetor de palavras 
	int char_vetor_tam;
	std::vector<char*> char_vetor;
	std::string arquivo_nome("wordsEn.txt");
	std::ifstream arquivo(arquivo_nome);
	
	if (arquivo.is_open()) {
		while (!arquivo.eof()){
			std::string lineread;
			std::getline(arquivo, lineread);

			char* line = (char*) malloc(sizeof(char)*(lineread.size()+1));
			strcpy(line, lineread.c_str());
			char_vetor.push_back(line);
		}
	}
	char_vetor_tam = char_vetor.size();
	std::cout << "Para um vetor de " << char_vetor_tam << " strings lidas do arquivo " << arquivo_nome << ", os tempos de ordenação são...\n";

	comeco = clock();
	void* ordenado_c_str = heap_sort((void*) char_vetor.data(), generic_compare_string, print_string, sizeof(char*), char_vetor_tam);
	fim = clock();
	duracao = (double)(fim-comeco)/CLOCKS_PER_SEC; 

	std::cout << "\tHeapsort com heap genérico em C: " << duracao << " segundos\n";

	comeco = clock();
	genheap::GenericHeap<char*> heap_str(char_vetor, generic_compare_string);
	std::vector<char*> ordenado_cplus_str = heap_str.heap_sort();
	fim = clock();
	duracao = (double)(fim-comeco)/CLOCKS_PER_SEC; 

	std::cout << "\tHeapsort com heap template em C++: " << duracao << " segundos\n";

	std::vector<char*> char_vetor_2(char_vetor.begin(), char_vetor.end());
	comeco = clock();
	std::sort(char_vetor_2.begin(), char_vetor_2.end());
	fim = clock();
	duracao = (double)(fim-comeco)/CLOCKS_PER_SEC; 

	std::cout << "\tHeapsort com a função sort definida no header algorithm do C++: " << duracao << " segundos\n";

	comeco = clock();
	std::qsort((void*) char_vetor.data(), char_vetor_tam, sizeof(char*), qsort_compare_string);
	fim = clock();
	duracao = (double)(fim-comeco)/CLOCKS_PER_SEC; 

	std::cout << "\tHeapsort com a função qsort definida no stdlib do C: " << duracao << " segundos\n";
}