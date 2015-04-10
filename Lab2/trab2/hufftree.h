#ifndef HUFFTREE_H
#define HUFFTREE_H

namespace huff{
	class HuffTree
	{
	public:

		Node *root;

		HuffTree();
		//Constrói uma árvore de Huffman a partir de um heap base
		HuffTree(Heap base);
		//Constrói uma árvore de Huffman a partir de uma descrição textual da árvore
		HuffTree(char* description);

		//Função que dado um caractere retorna o código apropriado
		std::string find_code(char character);


		~HuffTree();
		
	};
}

#endif