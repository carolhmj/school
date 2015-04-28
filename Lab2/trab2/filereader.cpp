#include "filereader.h"
#include "minheap.h"
#include "node.h"
#include "hufftree.h"
#include <limits>
#include <fstream>
#include <iostream>

void huff::compress(const char* input, const char* output){
	const int qtde_char = std::numeric_limits<unsigned char>::max();
	int qtde_num_escritos = 0;
	std::array<int,qtde_char> frequencias {0};
	std::ifstream entrada(input, std::ios::binary);
	char current;

	while(entrada.read(&current,1)){
		frequencias[(unsigned char) current]++;
	}

	std::vector<Node> lista_nos;
	for (int c = 0; c <= qtde_char; c++){
		//std::cout << c << " " << (char)c << "\n";
		if (frequencias[c] != 0){
			lista_nos.push_back(Node((char) c, frequencias[c]));
			qtde_num_escritos++;
		}
	}

	entrada.close();

	huff::MinHeap input_heap(lista_nos);
	huff::HuffTree input_tree(input_heap);

	std::ofstream saida(output, std::ios::binary);

	saida << qtde_num_escritos;
	for (std::vector<Node>::iterator i = lista_nos.begin(); i != lista_nos.end(); ++i)
	{
		//saida << "[" << i->info[0] << "|" << i->frequency << "]";
		saida << i->info[0]; 
		saida << i->frequency;
	}

	

	saida.close();
}

void huff::decompress(const char *input, const char* output){

	std::ifstream entrada(input, std::ios::binary);
	int qtde_num_escritos;
	std::vector<Node> lista_nos;

	entrada >> qtde_num_escritos;

	while (qtde_num_escritos > 0){
		char info;
		int frequency;

		//entrada >> "[" >> info >> "|" >> frequency >> "]";
		entrada >> info; 
		entrada >> frequency;

		lista_nos.push_back(Node(info,frequency));
		qtde_num_escritos--;
	}

	entrada.close();

	huff::MinHeap input_heap(lista_nos);
	huff::HuffTree input_tree(input_heap);
	//input_tree.print_tree(input_tree.root);	 
}