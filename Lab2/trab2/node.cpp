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