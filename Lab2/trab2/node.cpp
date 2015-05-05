#include "node.h"

#include <vector>
#include <iostream>
#include <memory>

huff::Node::Node(char info_c, int frequency_c){
	std::vector<char> v {info_c};
	this->info = v;
	this->frequency = frequency_c;
}

huff::Node::Node(std::vector<char> info_v, int frequency_c){
	this->info = info_v;
	this->frequency = frequency_c;
}

void huff::Node::print_node(){

	std::cout << "[ {"; 

	std::vector<char> v = this->info;
	for (std::vector<char>::iterator i = v.begin(); i != v.end(); ++i)
	{
		std::cout << *i << " ";
	}

	std::cout << "} | " << this->frequency << " ]\n"; 
}

huff::Node::Node(const Node& n){
	this->info = n.info;
	this->frequency = n.frequency;
	this->p = n.p;
	this->e = n.e;
	this->d = n.d;
}

std::shared_ptr<huff::Node> huff::Node::combine_nodes(std::shared_ptr<huff::Node> a, std::shared_ptr<huff::Node> b){
	std::vector<char> result;

	std::vector<char>::iterator a_iter = (a->info).begin();
	std::vector<char>::iterator b_iter = (b->info).begin();
	std::vector<char>::iterator a_end  = (a->info).end();
	std::vector<char>::iterator b_end  = (b->info).end();

	//Faz um merge dos infos dos dois nós
	while (a_iter != a_end && b_iter != b_end){
		if ((*a_iter) <= (*b_iter)){
			result.push_back(*a_iter);
			a_iter++;
		} else {
			result.push_back(*b_iter);
			b_iter++;
		}
	}
	//Sai do while porque um dos vetores chegou ao fim, vê se o outro ainda tem elementos para inserir
	if (a_iter != a_end){
		result.insert(result.end(), a_iter, a_end);
	}
	if (b_iter != b_end){
		result.insert(result.end(), b_iter, b_end);
	}

	int combined_frequency = a->frequency + b->frequency;
	std::shared_ptr<huff::Node> no(new huff::Node(result,combined_frequency));

	return no;	
}

bool huff::Node::char_in_node(char character){
	//Realiza uma busca binária no vetor de caracteres
	std::vector<char> list = this->info;
	
	int min_val = 0;
	int max_val = list.size() - 1;
	int mid_val;

	while (max_val >= min_val) {
		mid_val = min_val + ((max_val - min_val) / 2);

		if (list[mid_val] == character) {
			return true;
		} else if (list[mid_val] < character){
			min_val = mid_val + 1;
		} else {
			max_val = mid_val - 1;
		}
	}

	return false;
}