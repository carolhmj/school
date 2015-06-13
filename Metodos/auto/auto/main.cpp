#include <iostream>
#include <armadillo>
#include "autovalvec.h"

using namespace arma;

int main()
{
    std::cout << "Começando os trabalhos\n";

    mat A("4 2 2 1; 2 -3 1 1; 2 1 3 1; 1 1 1 2");
    std::cout << "A matriz é: \n";
    A.print(std::cout);
    std::cout << "\n";
    resultado_transformacao res = householder_simpl(A);
    std::cout << "A matriz diagonal resultado de householder é: \n";
    res.newmat.print(std::cout);
    std::cout << "\n";
}
