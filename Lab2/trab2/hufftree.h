#ifndef HUFFTREE_H
#define HUFFTREE_H

#include "minheap.h"
#include "node.h"
#include <string>
#include <memory>

namespace huff{
	class HuffTree
	{
	public:

		std::shared_ptr<Node> root;
		bool empty = true;

		HuffTree() = default;
		//Constrói uma árvore de Huffman a partir de um heap base
		HuffTree(MinHeap base);
		//Constrói uma árvore de Huffman a partir de uma descrição dos caracteres e suas frequências
		HuffTree(char* description);

		bool is_empty();
		//Função que dado um caractere retorna o código apropriado
		std::string find_code(char character);

		//Imprime a árvore no stdout, para debug
		void print_tree(std::shared_ptr<Node> current, std::string codigo, const char* debug);

		~HuffTree() = default;
		
	};
}

#endif