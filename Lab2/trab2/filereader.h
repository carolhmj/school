#ifndef FILEREADER_H
#define FILEREADER_H


namespace huff{
	void compress(const char* input, const char* output, const char* tree = "arvore");
	void decompress(const char *input, const char* output, const char* tree = "arvore");
}


#endif