#include "hufftree.h"
#include "minheap.h"
#include "node.h"
#include <iostream>
#include <stdexcept>
#include <memory>
#include <fstream>
#include <string>

huff::HuffTree::HuffTree(huff::MinHeap base){
	std::shared_ptr<huff::Node> elem_a;
	std::shared_ptr<huff::Node> elem_b;
	std::shared_ptr<huff::Node> root_n;

	while (base.heap_size() > 1){
		//Extrai os dois menores elementos do heap sucessivamente
		elem_a = std::shared_ptr<Node>(new Node(base.extrair_min()));
		elem_b = std::shared_ptr<Node>(new Node(base.extrair_min()));
		
		std::shared_ptr<Node> new_node = huff::Node::combine_nodes(elem_a,elem_b);
		new_node->e = elem_a;
		new_node->d = elem_b;

		elem_a->p = new_node;
		elem_b->p = new_node;
		//Inserir o novo nó no heap
		base.inserir_heap(*new_node);
 	}
 	if (base.heap_size() == 1) {
 		root_n = std::shared_ptr<Node>(new Node(base.extrair_min()));
 		
 		this->root = root_n;
 		this->empty = false;
 	}

}

bool huff::HuffTree::is_empty(){
	return this->empty;
}

std::string huff::HuffTree::find_code(char character){
	std::shared_ptr<Node> current = this->root;
	std::string codigo;

	while(current->e != nullptr || current->d != nullptr){
		if (current->e != nullptr && (current->e)->char_in_node(character)) {
			//Vai para o filho esquerdo então o código é 1
			codigo += "1";			
			current = current->e;
		} else if (current->d != nullptr && (current->d)->char_in_node(character)) {
			//Vai para o filho direito então o código é 0
			codigo += "0";
			current = current->d;	
		} else {
			//Não é pra fazer nada aqui
			std::cout << "Não deveria acontecer";
		}
	}
	//Chegou a um nó folha, acabamos!
	return codigo;
}

void huff::HuffTree::print_tree(std::shared_ptr<Node> current, std::string codigo, const char* debug){
	if (current!=nullptr) {

		if ((current->e == nullptr) && (current->d == nullptr)){

			std::ofstream debugf(debug, std::ios::app);
			debugf << "folha[ valor: " << current->info[0] << " frequencia: "  << current->frequency << " ] codigo:" << codigo << "\n";
			debugf.close();

		} else if (current->e == nullptr) {

			print_tree(current->d, codigo+"0", debug);

		} else if (current->d == nullptr) {

			print_tree(current->e,codigo+"1",debug);

		} else {

			print_tree(current->e,codigo+"1",debug);
			print_tree(current->d,codigo+"0",debug);

		}
	}
}
