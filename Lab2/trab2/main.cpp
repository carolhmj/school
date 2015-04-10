#include "node.h"
#include "heap.h"
#include <iostream>

int main(){
	huff::Node y('c', 10);
	huff::Node m('d', 1);
	huff::Node c('%', 2);
	huff::Node a('v', 0);
	std::vector<huff::Node> list {y,m,c,a};
	huff::MinHeap z(list);
	z.print_heap();
	z.subir_no_heap(3);
	z.print_heap();
}