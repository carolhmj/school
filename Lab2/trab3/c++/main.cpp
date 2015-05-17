#include "genericheap.h"
#include <vector>
#include <iostream>

int main()
{
	std::vector<int> v = {10,9,8,7,6,5};
	genheap::GenericHeap<int> heap(v);
	heap.print_heap();
	heap.inserir_heap(1);
	heap.print_heap();
	std::cout << heap.extrair() << "\n";
	heap.print_heap();
	std::vector<std::string> x = {"Carol", "Daniel", "Mariana", "Heitor", "Erick", "André"};
	genheap::GenericHeap<std::string> heap2(x);
	heap2.print_heap();
	return 0;
}