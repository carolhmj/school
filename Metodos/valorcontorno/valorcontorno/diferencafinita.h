#ifndef DIFERENCAFINITA_H
#define DIFERENCAFINITA_H

#include <armadillo>
#include <vector>

using namespace arma;

typedef struct mask_ {
    std::vector<double> val;
    int n_left;
    int n_right;
} mask;

typedef std::function<double(double)> boundary;

//Recebe os pontos do intervalo [a,b], qtde de subdivisões, a máscara regular, a condição regular, as condições de contorno, a posição dos pontos em que há máscaras especiais e as máscaras especiais
vec diferenca_finita(double a, double b, int N, mask regular_mask, boundary regular_condition, boundary condition_a, boundary condition_b, std::vector<int> special_points, std::vector<mask> special_masks);

#endif // DIFERENCAFINITA_H
