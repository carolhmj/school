#ifndef GenericHeap_H
#define GenericHeap_H

#include <vector>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <functional>

namespace genheap{

	template<typename T>
	class GenericHeap
	{
	public:

		//Heap é implantado como um vetor de nós
		std::vector<T> members;
		//std::function<bool(T,T)> compare;

		//Construtores, tanto usando vetor quanto usando array
		GenericHeap() = default;
		GenericHeap(T* list, int tamanho/*, std::function<bool(T,T)> compare*/);
		GenericHeap(std::vector<T> list/*, std::function<bool(T,T)> compare*/);

		//Retorna as posições relativas ao elemento do índice i
		int pai(int i);
		int filho_esq(int i);
		int filho_dir(int i);

		int heap_size();

		//Função pra extrair o menor elemento do heap
		T extrair();
		//Função para inserir um elemento no heap e consertá-lo de acordo com a inserção
		void inserir_heap(T n);
		//Funções usadas nas operações de extrair e de inserir
		void subir_no_heap(int i);
		void descer_no_heap(int i);

		void print_heap();

		~GenericHeap() = default;
		
	};


	template <typename T>
	GenericHeap<T>::GenericHeap(std::vector<T> list){
		
		for (typename std::vector<T>::iterator i = list.begin(); i != list.end(); ++i)
		{
			inserir_heap(*i);	
		}
	}

	template <typename T>
	GenericHeap<T>::GenericHeap(T* list, int tamanho){

		T *search, *end = list+tamanho;
		for (search = list; search < end; ++search)
		{
			inserir_heap(*search);
		}
	}

	template <typename T>
	int GenericHeap<T>::pai(int i){
		return std::floor((i-1)/2);
	}

	template <typename T>
	int GenericHeap<T>::filho_esq(int i){
		return 2*i+1;
	}

	template <typename T>
	int GenericHeap<T>::filho_dir(int i){
		return 2*i+2;
	}

	template <typename T>
	int GenericHeap<T>::heap_size(){
		return (this->members).size();
	}

	template <typename T>
	void GenericHeap<T>::subir_no_heap(int i){
		//Compara o elemento de índice i com seu pai, se este for maior, troca os dois e continua recursivamente; senão, ou se chegar na raiz, para
		while( (i>0) && (this->members[pai(i)] > this->members[i]) ){
			T aux = this->members[i];
			this->members[i] = this->members[pai(i)];
			this->members[pai(i)] = aux;
			i = pai(i);
		} 
	}

	template <typename T>
	void GenericHeap<T>::descer_no_heap(int i){
		//Compara o elemento de índice i com seus filhos, se for maior que algum deles, troca com algum e continua recursivamente; senão, ou se chegar em uma folha, para
		int menor = i;
		if ((filho_esq(i) < heap_size()) && (this->members[i] > this->members[filho_esq(i)])) {
			menor = filho_esq(i);
		}
		if ((filho_dir(i) < heap_size()) && (this->members[menor] > this->members[filho_dir(i)])){
			menor = filho_dir(i);
		}
		if (menor!=i){
			T aux = this->members[i];
			this->members[i] = this->members[menor];
			this->members[menor] = aux;
			descer_no_heap(menor);
		} 
			
	}

	template <typename T>
	void GenericHeap<T>::inserir_heap(T n){
		this->members.push_back(n);
		subir_no_heap(heap_size()-1);
	}

	template <typename T> 
	T GenericHeap<T>::extrair(){
		if (heap_size() != 0) {
			T retorno = (this->members)[0];
			this->members[0] = (this->members)[heap_size()-1];
			(this->members).pop_back();
			descer_no_heap(0);
			return retorno;
		} else {
			throw std::range_error("Tentou remover de um heap vazio!"); 
		}
	}

	template <typename T>
	void GenericHeap<T>::print_heap(){
		std::vector<T> v = this->members;
		std::cout << "(\n";
		for (typename std::vector<T>::iterator i = v.begin(); i != v.end(); ++i)
		{
			std::cout << (*i) << " ";
		}
		std::cout << "\n)\n";
	}

}

#endif