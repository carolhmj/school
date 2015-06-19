#include <iostream>
#include <armadillo>
#include "autovalvec.h"

using namespace arma;

int main()
{
    std::cout << "Começando os trabalhos\n";

    mat A("4 2 1; 2 8 2; 1 2 6");
    std::cout << "A matriz é: \n";
    A.print(std::cout);
    std::cout << "\n";
    resultado_transformacao res = diagonalizacao_QR(A, 0.0001);
    std::cout << "A matriz diagonal resultado de jacobi é: \n";
    res.newmat.print(std::cout);
    std::cout << "\n";
}
