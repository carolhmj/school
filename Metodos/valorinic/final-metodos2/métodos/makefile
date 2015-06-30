# usando g++ como compilador
CC = g++

# compiler flags:
#  -g        adiciona informações de debug no executável
#  -Wall     ativa a maioria dos erros de compilação
#  -std=c+11 usa o standard mais recente
CFLAGS  = -g -Wall -std=c++11 -L lib

default: testar

testar: bin/testes
	bin/testes -s --force-colour -d yes | less -Sr

bin/métodos.o: métodos.cpp métodos.h
	$(CC) $(CFLAGS) -c métodos.cpp -o bin/métodos.o

bin/testes: testes.cpp bin/métodos.o métodos.cpp hlibs/catch.hpp
	$(CC) $(CFLAGS) testes.cpp bin/métodos.o -o bin/testes
