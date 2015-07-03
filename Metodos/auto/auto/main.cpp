#include <iostream>
#include <armadillo>
#include <vector>
#include "autovalvec.h"

using namespace arma;

int main()
{
    mat A("4 2 1; 2 8 2; 1 2 6");
    A.print("Matriz:");
    vec t = {1,2,2};

    resultado z = potencia_regular(A, t, 0.001);
    std::cout << "Autovalor " << z.autoval << "\n";
    z.autovec.print("Autovetor Potência Regular");

    resultado x = potencia_inversa(A, t, 0.001);
    std::cout << "Autovalor " << x.autoval << "\n";
    x.autovec.print("Autovetor Potência Inversa");

    std::vector<resultado> y = potencia_deslocamento(A, t, 0.001, 1);
    for (unsigned int k = 0; k < y.size(); k++){
        std::cout << "Autovalor " << y[k].autoval << "\n";
        y[k].autovec.print("Autovetor Potência Deslocamento");
    }

    std::vector<resultado> r = householder_aplicado(A, 0.001);
    for (unsigned int i = 0; i < r.size(); i++){
        std::cout << "Autovalor " << r[i].autoval << "\n";
        r[i].autovec.print("Autovetor Householder+QR:");
    }

    std::vector<resultado> v = jacobi_aplicado(A, 0.001);
    for (unsigned int i = 0; i < v.size(); i++){
        std::cout << "Autovalor " << v[i].autoval << "\n";
        v[i].autovec.print("Autovetor Jacobi:");
    }

    std::vector<resultado> l = QR_aplicado(A, 0.001);
    for (unsigned int i = 0; i < l.size(); i++){
        std::cout << "Autovalor " << l[i].autoval << "\n";
        l[i].autovec.print("Autovetor QR:");
    }
}
