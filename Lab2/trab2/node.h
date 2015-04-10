#ifndef NODE_H
#define NODE_H

#include <vector>

namespace huff{
	class Node
	{
	public:

		//Info é o caractere de um nó folha, se não for folha info é uma lista com todos os caracteres daquele caminho
		std::vector<char> info;
		//Frequência do nó
		int frequency;
		//Nós pai, filho esquerdo e filho direito
		Node *f, *e, *d;

		//Construtor padrão, gerado com a keyword do C++11 default
		Node() = default;
		//Constutor que pega um char e uma frequência, usa para nós folha
		Node(char info_c, int frequency_c);
		//Construtor que pega um vetor de chars e uma frequência, usa para nós não folha
		Node(std::vector<char> info_v, int frequency_c);

		//Printa esse nó!
		void print_node();

		~Node() = default;
		
	};
}

#endif