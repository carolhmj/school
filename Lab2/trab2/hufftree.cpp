#include "hufftree.h"
#include "minheap.h"
#include "node.h"
#include <iostream>
#include <stdexcept>
#include <memory>

//Mudar a lógica pra uma coisa: quando o símbolo tem frequência 0, ignorá-lo!
huff::HuffTree::HuffTree(huff::MinHeap base){
	std::shared_ptr<huff::Node> elem_a;
	std::shared_ptr<huff::Node> elem_b;
	std::shared_ptr<huff::Node> root_n;

	while (base.heap_size() > 1){
		//Extrai os dois menores elementos do heap sucessivamente
		elem_a = std::shared_ptr<Node>(new Node(base.extrair_min()));
		elem_b = std::shared_ptr<Node>(new Node(base.extrair_min()));
		//Combina as informações dos dois nós
		std::vector<char> combined_elements(elem_a->info);
		combined_elements.insert(combined_elements.end(), (elem_b->info).begin(), (elem_b->info).end());
		int combined_frequency = elem_a->frequency+elem_b->frequency;

		//Criar o novo nó com as informações combinadas e fazê-lo apontar para os filhos
		std::shared_ptr<Node> new_node(new Node(combined_elements, combined_frequency));
		new_node->e = elem_a;
		new_node->d = elem_b;

		elem_a->p = new_node;
		elem_b->p = new_node;
		//Inserir o novo nó no heap
		base.inserir_heap(*new_node);
 	}
 	if (base.heap_size() == 1) {
 		root_n = std::shared_ptr<Node>(new Node(base.extrair_min()));
 		//root_n.print_node();
 		this->root = root_n;
 		this->empty = false;
 	}

}

bool huff::HuffTree::is_empty(){
	return this->empty;
}
huff::HuffTree::HuffTree(char* description){}

std::string huff::HuffTree::find_code(char character){}

void huff::HuffTree::print_tree(std::shared_ptr<Node> current){
	if (current!=nullptr) {
		if (current->e == nullptr && current->d == nullptr){
			std::cout << "folha[ valor: " << current->info[0] << " frequência: "  << current->frequency << " ]\n";
		} else if (current->e == nullptr) {
			std::cout << "folha[ valor: "; 
			for (std::vector<char>::iterator i = current->info.begin(); i != current->info.end(); ++i)
			{
				std::cout << *i << " ";
			}
			std::cout << " frequência: "  << current->frequency << " ]\n";
			print_tree(current->d);
		} else if (current->d == nullptr) {
			std::cout << "folha[ valor: "; 
			for (std::vector<char>::iterator i = current->info.begin(); i != current->info.end(); ++i)
			{
				std::cout << *i << " ";
			}
			std::cout << " frequência: "  << current->frequency << " ]\n";
			print_tree(current->e);
		} else {
			std::cout << "folha[ valor: "; 
			for (std::vector<char>::iterator i = current->info.begin(); i != current->info.end(); ++i)
			{
				std::cout << *i << " ";
			}
			std::cout << " frequência: "  << current->frequency << " ]\n";
			print_tree(current->e);
			print_tree(current->d);
		}
	}
}
