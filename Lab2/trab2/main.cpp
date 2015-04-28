#include "node.h"
#include "minheap.h"
#include "hufftree.h"
#include "filereader.h"
#include <iostream>
#include <memory>
#include <limits>
int main(){
	huff::compress("chapeuzinho.txt","lobo.dat");
	huff::decompress("lobo.txt","ehn");
}