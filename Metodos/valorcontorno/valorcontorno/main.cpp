#include "diferencafinita.h"
#include <vector>
#include <armadillo>
#include <cmath>

using namespace arma;

int main()
{
    mask m1, m2, m3;
    //máscara 89/25 -32/25
    m1.n_left = 0;
    m1.n_right = 1;
    m1.val = {89/25, -32/25};

    //máscara -32/25 89/25 -32/25
    m2.n_left = 1;
    m2.n_right = 1;
    m2.val = {-32/25, 89/25, -32/25};

    //máscara -64/25 169/25
    m3.n_left = 1;
    m3.n_right = 0;
    m3.val = {-64/25, 169/25};

    std::vector<mask> m = {m1, m3};

    std::vector<int> p = {0,7}; //pontos com máscaras especiais

    boundary b1 = [](double x) {return 32/25 + std::exp(-0.2*x);} ;
    boundary b2 = [](double x) {return std::exp(-0.2*x);} ;
    boundary b3 = [](double x) {return std::exp(-0.2*x);} ;

    vec res = diferenca_finita(5/4, 10, 8, m2, b2, b1, b3, p, m);
    res.print("Valores nos pontos");
}
