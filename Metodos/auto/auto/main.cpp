#include <iostream>
#include <armadillo>
#include "autovalvec.h"

using namespace arma;

int main(int argc, char *argv[])
{
    std::cout << "Começando os trabalhos\n";

    mat A("1 2; 0 2");
    //A.print(std::cout);
    vec x(2);
    x.fill(1);
    resultado r;
    r = potencia_inversa(A,x,0.001);
    std::cout << "O autovalor é: " << r.autoval << " e o autovetor é: \n";
    r.autovec.print(std::cout);
    std::cout << "\n";
}
