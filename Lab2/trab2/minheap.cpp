#include "minheap.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <memory>

huff::MinHeap::MinHeap(std::vector<huff::Node> list){
	
	for (std::vector<huff::Node>::iterator i = list.begin(); i != list.end(); ++i)
	{
		inserir_heap(*i);	
	}
}

huff::MinHeap::MinHeap(Node* list, int tamanho){

	Node *search, *end = list+tamanho;
	for (search = list; search < end; ++search)
	{
		inserir_heap(*search);
	}
}

int huff::MinHeap::pai(int i){
	return std::floor((i-1)/2);
}
int huff::MinHeap::filho_esq(int i){
	return 2*i+1;
}
int huff::MinHeap::filho_dir(int i){
	return 2*i+2;
}

int huff::MinHeap::heap_size(){
	return (this->members).size();
}

void huff::MinHeap::subir_no_heap(int i){
	//Compara o elemento de índice i com seu pai, se este for maior, troca os dois e continua recursivamente; senão, ou se chegar na raiz, para
	while( (i>0) && (this->members[pai(i)].frequency > this->members[i].frequency) ){
		Node aux = this->members[i];
		this->members[i] = this->members[pai(i)];
		this->members[pai(i)] = aux;
		i = pai(i);
	} 
}
void huff::MinHeap::descer_no_heap(int i){
	//Compara o elemento de índice i com seus filhos, se for maior que algum deles, troca com algum e continua recursivamente; senão, ou se chegar em uma folha, para
	int menor = i;
	if ((filho_esq(i) < heap_size()) && (this->members[i].frequency > this->members[filho_esq(i)].frequency)) {
		menor = filho_esq(i);
	}
	if ((filho_dir(i) < heap_size()) && (this->members[menor].frequency > this->members[filho_dir(i)].frequency)){
		menor = filho_dir(i);
	}
	if (menor!=i){
		Node aux = this->members[i];
		this->members[i] = this->members[menor];
		this->members[menor] = aux;
		descer_no_heap(menor);
	} 
		
}

void huff::MinHeap::inserir_heap(huff::Node n){
	this->members.push_back(n);
	subir_no_heap(heap_size()-1);
}

huff::Node huff::MinHeap::extrair_min(){
	if (heap_size() != 0) {
		huff::Node retorno = (this->members)[0];
		this->members[0] = (this->members)[heap_size()-1];
		(this->members).pop_back();
		descer_no_heap(0);
		return retorno;
	} else {
		throw std::range_error("a"); 
	}
}

void huff::MinHeap::print_heap(){
	std::vector<Node> v = this->members;
	std::cout << "(\n";
	for (std::vector<Node>::iterator i = v.begin(); i != v.end(); ++i)
	{
		i->print_node();
	}
	std::cout << ")\n";
}