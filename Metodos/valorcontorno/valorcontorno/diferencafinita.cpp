#include "diferencafinita.h"
#include <vector>
#include <armadillo>
#include <algorithm>
#include <cmath>

vec diferenca_finita(double a, double b, int N, mask regular_mask, boundary regular_condition, boundary condition_a, boundary condition_b, std::vector<int> special_points, std::vector<mask> special_masks)
{
    mat M_mask(N, N, fill::zeros);
    vec V_boundary(N, fill::zeros);
    double interval = (b-a)/(N-1);
    //Constrói a matriz com os valores da máscara e o vetor com os valores de contorno
    for (int i = 0; i < N; i++){
        double x = a + i * interval;

        //Checa se i é uma das pontas e aplica a condição apropriada no vetor de condições
        if (i == 0) {
            V_boundary(i) = condition_a(x);
        } else if (i == N-1) {
            V_boundary(i) = condition_b(x);
        } else {
            V_boundary(i) = regular_condition(x);
        }

        //Checa se i é um dos pontos em que existe uma máscara especial para aplicar no vetor de máscaras; caso contrário aplica a máscara regular
        std::vector<int>::iterator find_ind = std::find(special_points.begin(), special_points.end(), i);
        mask m;
        if (find_ind != special_points.end()) {
            int index = find_ind - special_points.begin();
            m = special_masks[index];
        } else {
            m = regular_mask;
        }
        //Insere os valores da máscara escolhida na matriz
        int k = 0;
        for (int j = i - m.n_left ; j <= i + m.n_right ; j++) {
            M_mask(i,j) = m.val[k];
            k++;
        }
    }

    M_mask.print("Matriz de máscaras");
    V_boundary.print("Vetor de contornos");

    vec result = solve(M_mask, V_boundary);
    return result;
}
