#ifndef MINHEAP_H
#define MINHEAP_H

#include "node.h"
#include <vector>
#include <memory>

namespace huff{
	class MinHeap
	{
	public:

		//Heap é implantado como um vetor de nós
		std::vector<Node> members;

		//Construtores, tanto usando vetor quanto usando array de nós
		MinHeap() = default;
		MinHeap(std::vector<Node> list);
		MinHeap(Node* list, int tamanho);

		//Retorna as posições relativas ao elemento do índice i
		int pai(int i);
		int filho_esq(int i);
		int filho_dir(int i);

		int heap_size();

		//Função pra extrair o menor elemento do heap
		Node extrair_min();
		//Função para inserir um elemento no heap e consertá-lo de acordo com a inserção
		void inserir_heap(Node n);
		//Funções usadas nas operações de extrair e de inserir
		void subir_no_heap(int i);
		void descer_no_heap(int i);

		//Printa o heap no stdout para debug
		void print_heap();

		~MinHeap() = default;
		
	};
}

#endif