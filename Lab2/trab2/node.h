#ifndef NODE_H
#define NODE_H

#include <vector>
#include <memory>

namespace huff{
	class Node
	{
	public:

		//Info é o caractere de um nó folha, se não for folha info é uma lista com todos os caracteres daquele caminho
		std::vector<char> info;
		//Frequência do nó
		int frequency;
		//Nós pai, filho esquerdo e filho direito
		std::shared_ptr<Node> p, e, d;

		//Construtor padrão, gerado com a keyword do C++11 default
		Node() = default;
		//Construtor cópia
		Node(const Node& n);
		//Constutor que pega um char e uma frequência, usa para nós folha
		Node(char info_c, int frequency_c);
		//Construtor que pega um vetor de chars e uma frequência, usa para nós não folha
		Node(std::vector<char> info_v, int frequency_c);
		//Destrutor padrão
		~Node() = default;

		//Printa esse nó!
		void print_node();

		//Retorna ponteiro para um nó que é a combinação de dois nós de entrada
		static std::shared_ptr<Node> combine_nodes(std::shared_ptr<Node> a, std::shared_ptr<Node> b);
		//Procura determinado caractere no info de um nó
		bool char_in_node(char character);
		
	};
}

#endif