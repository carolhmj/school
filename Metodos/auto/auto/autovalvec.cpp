#include "autovalvec.h"
#include <armadillo>
#include <iostream>
using namespace arma;

resultado potencia_regular(mat A, vec inicial, double epsilon)
{
    vec aux, y, x = inicial;
    double lambda_atual, lambda_ant;

    //Primeira aplicação do método para encontrar o lambda inicial
    y = normalise(x);
    x = A*y;
    aux = y.t()*x;
    lambda_atual = aux(0);

    //Continua a aplicar para refinar as aproximações
    do{
        lambda_ant = lambda_atual;

        y = normalise(x);
        x = A*y;
        aux = y.t()*x;
        lambda_atual = aux(0);

    } while (fabs(lambda_atual - lambda_ant) > epsilon);

    resultado r;

    r.autoval = lambda_atual;
    r.autovec = y;
    return r;
}


resultado potencia_inversa(mat A, vec inicial, double epsilon)
{
    vec aux, y, x = inicial;
    double lambda_atual, lambda_ant;

    //Primeira aplicação do método para encontrar o lambda inicial
    y = normalise(x);
    x = solve(A,y);
    aux = y.t()*x;
    lambda_atual = aux(0);

    //Continua a aplicar para refinar as aproximações
    do{
        lambda_ant = lambda_atual;

        y = normalise(x);
        x = solve(A,y);
        aux = y.t()*x;
        lambda_atual = aux(0);

    } while (fabs(lambda_atual - lambda_ant) > epsilon);

    resultado r;

    r.autoval = 1.0/lambda_atual;
    r.autovec = y;
    return r;
}



std::vector<resultado> potencia_deslocamento(mat A, vec inicial, double epsilon, double deslocamento)
{
    double maior_autov = potencia_regular(A,inicial,epsilon).autoval;
    double menor_autov = potencia_inversa(A,inicial,epsilon).autoval;
    std::vector<resultado> retorno;
    resultado res_atual;
    double deslocamento_atual = deslocamento;

    mat I(A.n_rows,A.n_cols,fill::eye);
    mat B = A - deslocamento_atual*I;

    while (true){
        res_atual = potencia_inversa(B,inicial,epsilon);
        if ((res_atual.autoval + deslocamento_atual < maior_autov) && (res_atual.autoval + deslocamento_atual > menor_autov)){
            retorno.push_back(res_atual);
            deslocamento_atual += deslocamento;
        } else {
            break;
        }
    }
}
