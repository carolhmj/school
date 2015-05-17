#include "genericheap.h"
#include <vector>
#include <iostream>

int main()
{
	std::vector<int> v = {10,9,8,7,6,5};
	genheap::GenericHeap<int> heap(v);
	heap.print_heap();
	return 0;
}