#include "node.h"
#include "minheap.h"
#include "hufftree.h"
#include "filereader.h"
#include <iostream>
#include <cstring>

int main(int argc, char const *argv[])
{
	switch(argc){
	case 4:
		if (strcmp(argv[1],"--c")==0){
			huff::compress(argv[2],argv[3]);
		} else if (strcmp(argv[1],"--d")==0){
			huff::decompress(argv[2],argv[3]);
		} else {
			std::cout << "Sintaxe dos argumentos incorreta\n";
			return 1;
		}
		break;
	case 5:
		if (strcmp(argv[1],"--c")==0){
			huff::compress(argv[2],argv[3],argv[4]);
		} else if (strcmp(argv[1],"--d")==0){
			huff::decompress(argv[2],argv[3],argv[4]);
		} else {
			std::cout << argv[1] << "\n";
			std::cout << "Sintaxe dos argumentos incorreta\n";
			return 1;
		}
		break;	
	default:
		std::cout << "Número de argumentos incorreto. Por favor informe os argumentos\n";
		return 1;
	}
	return 0;
}