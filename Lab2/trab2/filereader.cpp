#include "filereader.h"
#include "minheap.h"
#include "node.h"
#include "hufftree.h"
#include <limits>
#include <fstream>
#include <iostream>
#include <bitset>
#include <memory>
#include <vector>

void huff::compress(const char* input, const char* output, const char* tree){
	const int qtde_char = std::numeric_limits<unsigned char>::max();
	int qtde_num_escritos = 0;
	std::array<int,qtde_char> frequencias {0};

	std::ifstream entrada(input, std::ios::binary);

	if (!entrada){
		std::cout << "Falha na leitura do arquivo de entrada!\n";
		return;
	}

	char current;
	int carlidos = 0, carescritos = 0;

	while(entrada.read(&current,1)){
		frequencias[(unsigned char) current]++;
		carlidos++;
	}

	std::vector<Node> lista_nos;
	for (int c = 0; c <= qtde_char; c++){
		if (frequencias[c] != 0){
			lista_nos.push_back(Node((unsigned char) c, frequencias[c]));
			qtde_num_escritos++;
		}
	}

	std::cout << carlidos << " caractreres lidos\n";

	huff::MinHeap input_heap(lista_nos);
	huff::HuffTree input_tree(input_heap);

	std::string printstring;

	input_tree.print_tree(input_tree.root,printstring,tree);
	
	std::ofstream saida(output, std::ios::binary);

	if (!saida){
		std::cout << "Falha na leitura do arquivo de saída!\n";
		return;
	}

	saida << carlidos;
	saida << "|";
	saida << qtde_num_escritos;
	for (std::vector<Node>::iterator i = lista_nos.begin(); i != lista_nos.end(); ++i)
	{
		saida << "[" << (int)i->info[0] << "|" << i->frequency << "]";
	}

	//Agora vamos percorrer o arquivo de entrada caractere por caractere e escrever seus códigos no arquivo de saída
	entrada.clear();
	entrada.seekg(0);

	//Buffer que vai guardar 8 caracteres a serem escritos como um char, inicialmente está vazio
	std::string buffer = "";
	std::string current_code;
	int tam_char_bits = sizeof(char)*8;
	int faltam;
	int num_escrito;
	char char_escrito;

	while(entrada.read(&current,1)){
		current_code = input_tree.find_code((unsigned char)current);
		//std::cout << current_code << " current code\n";

		//Enquanto caracteres podem ser escritos
		while (buffer.size()+current_code.size() >= tam_char_bits) {
			//Qtde de caracteres que faltam para encher o buffer
			faltam = tam_char_bits - buffer.size();
			//Coloca no buffer essa quantidade de caracteres do código atual
			buffer.append(current_code.substr(0,faltam));
			//Remove do código atual essa quantidade de caracteres
			current_code.erase(0,faltam);

			num_escrito = std::stoi(buffer,nullptr,2);
			char_escrito = (unsigned char)num_escrito;
			saida << char_escrito;
			carescritos++;
			buffer = "";
		}
		//Não há caracteres o suficiente no buffer+código atual para escrever
		buffer.append(current_code);
	}
	//std::cout << buffer << " buffer\n";
	if (buffer.size() > 0){
		//Ainda restaram caracteres no buffer (a quantidade de bits não era múltipla de 8, escrevemos o resto)
		faltam = tam_char_bits - buffer.size();
		buffer.append(faltam, '1');

		num_escrito = std::stoi(buffer,nullptr,2);
		char_escrito = (unsigned char)num_escrito;
		//std::cout << buffer << " buffer\n";

		saida << char_escrito;
		carescritos++;
		buffer = "";
	}

	std::cout << carescritos << " caracteres escritos\n"; 

	entrada.close();
	saida.close();
}

void huff::decompress(const char *input, const char* output, const char* tree){

	std::ifstream entrada(input, std::ios::binary);

	if (!entrada){
		std::cout << "Falha na leitura do arquivo de entrada!\n";
		return;
	}

	int qtde_num_escritos;
	std::vector<Node> lista_nos;
	int total_characters;
	char dummy;

	entrada >> total_characters;
	entrada >> dummy;
	entrada >> qtde_num_escritos;

	while (qtde_num_escritos > 0){
		int info_read;
		char info;
		char dummy;
		int frequency;

		//entrada >> "[" >> info >> "|" >> frequency >> "]";
		entrada >> dummy;
		entrada >> info_read;
		entrada >> dummy; 
		entrada >> frequency;
		entrada >> dummy;

		info = (unsigned char)info_read;

		//std::cout << "info: " << info << " frequency: " << frequency << "\n";

		lista_nos.push_back(Node(info,frequency));

		qtde_num_escritos--;
	}

	huff::MinHeap input_heap(lista_nos);
	huff::HuffTree input_tree(input_heap);

	std::string printstring;

	input_tree.print_tree(input_tree.root,printstring,tree);
	
	std::ofstream saida(output,std::ios::binary);

	if (!saida){
		std::cout << "Falha na leitura do arquivo de saída!\n";
		return;
	}

	char current; 
	std::string bit_buffer;
	char current_bit;
	std::shared_ptr<Node> current_position = input_tree.root;
	bool finished = false;

	int qtde_char_escritos = 0, qtde_char_lidos = 0;

	//Vê onde tá o ponteiro. Se não estiver na folha e tiver coisa no bit buffer, lê do bit buff, se não, lê um char novo, quando chegar na folha escreve e volta pra raiz
	while (!finished){
		while (current_position->e != nullptr && current_position->d != nullptr){
			//Enquanto não chegamos na folha da árvore, vamos pegar mais bits do arquivo de entrada
			if (bit_buffer.size() == 0) {
				//Se não tivermos bits bufferizados, lemos o próximo caractere, convertemos para bits e colocamos no buffer
				entrada.read(&current,1);
				qtde_char_lidos++;

				unsigned char current_ = (unsigned char)current;
				std::bitset<8> current_byte(current_);
				bit_buffer = current_byte.to_string();
				//std::cout << bit_buffer << " bit buffer\n";
			}
			//Pegamos o primeiro bit do buffer e vemos para onde vamos na árvore
			current_bit = bit_buffer[0];
			bit_buffer.erase(0,1);

			if (current_bit == '1'){
				current_position = current_position->e;
			} else {
				current_position = current_position->d;
			}
		}
		//Chegamos em uma folha, então escrevemos o caractere no arquivo de saída
		qtde_char_escritos++;
		//std::cout << qtde_char_escritos << " chars escritos\n";
		if (qtde_char_escritos == total_characters) {
			finished = true;
		}
		saida << current_position->info[0];
		//Voltamos para o começo da árvore
		current_position = input_tree.root;
	}

	std::cout << qtde_char_lidos << " caracteres lidos.\n";
	std::cout << qtde_char_escritos << " caracteres escritos.\n";

	entrada.close();
	saida.close();
}