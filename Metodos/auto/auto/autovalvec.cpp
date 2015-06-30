#include "autovalvec.h"
#include <armadillo>
#include <iostream>
#include <cmath>
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
    return retorno;
}


resultado_transformacao householder_simpl(mat A)
{
    mat Ares = A;
    mat acum(A.n_rows, A.n_cols, fill::eye);
    //Aplica a simplificação nas colunas 0..(n-3)
    for (unsigned int j = 1; j <= A.n_cols-2; j++){
        //Constrói a matriz de householder
        mat H(A.n_rows, A.n_cols, fill::eye);
        vec n = construir_n(Ares,j);
        H = H - 2*(n*n.t());
        H.print("Householder: ");
        //Aplica a matriz de householder em A, e também acumula
        acum = acum * H;
        Ares = H * Ares * H;
    }
    resultado_transformacao res;
    res.newmat = Ares;
    res.transformationseq = acum;
    return res;
}


vec construir_n(mat A, int j)
{
    vec n(A.n_rows, fill::zeros);

    vec p(A.n_rows-j, fill::zeros);
    for (unsigned int i = 0; i < A.n_rows-j; i++){
        p(i) = A(j+i, j-1);
    }
    p.print("p: ");

    double p_norm = norm(p);
    vec p2(A.n_rows-j, fill::zeros);
    p2[0] = -1 * std::copysign(1.0, p(0)) * p_norm;
    p2.print("p2: ");

    vec dist = p - p2;
    double dist_norm = norm(dist);
    dist.print("dist: ");

    vec ntemp(A.n_rows - j);
    ntemp = (1/dist_norm) * dist;
    for (unsigned int i = 0; i < A.n_rows-j; i++){
        n(j+i) = ntemp(i);
    }
    n.print("n: ");
    return n;
}


resultado_transformacao jacobi(mat A, double epsilon)
{
    mat Ares = A;
    mat acum(A.n_rows, A.n_cols, fill::eye);
    while (!diagonal(Ares, epsilon)) {
        for (unsigned int j=0; j < A.n_cols-1 ; j++){

            for (unsigned int i=j+1; i < A.n_cols; i++){
                //Prenche com a identidade
                 mat J(A.n_rows, A.n_cols, fill::eye);

                 //Calcula o ângulo desejado
                 double theta = M_PI/4;
                 if (Ares(i,i) != Ares(j,j)) {
                     theta = std::atan( -2*Ares(i,j)/ (Ares(i,i)-Ares(j,j)) ) / 2;
                 }

                 J(i,i) = std::cos(theta);
                 J(j,j) = std::cos(theta);
                 J(i,j) = std::sin(theta);
                 J(j,i) = -1*std::sin(theta);

                 Ares = J.t() * Ares * J;
                 acum = acum * J;

            }
        }
        //Ares.print("Matriz do passo:");
    }

    resultado_transformacao res;
    res.newmat = Ares;
    res.transformationseq = acum;
    return res;
}


bool diagonal(mat A, double epsilon)
{
    for (unsigned int i = 0; i < A.n_rows; i++) {
        for (unsigned int j = 0; j < A.n_cols; j++) {
            //Se existe algum elemento fora da diagonal que é maior que epsilon...
            if ( (i!=j) && (std::fabs(A(i,j)) > epsilon) ) {
                return false;
            }
        }
    }
    //Se percorreu todos e não encontrou nenhum fora da diagonal maior que epsilon...
    return true;
}


resultado_transformacao diagonalizacao_QR(mat A, double epsilon)
{
    mat Ares = A;
    mat acum(A.n_rows, A.n_cols, fill::eye);

    while(!diagonal(Ares, epsilon)){

        mat QT(A.n_rows, A.n_cols, fill::eye);

        for (unsigned int j=0; j < A.n_cols-1 ; j++){
            for (unsigned int i=j+1; i < A.n_cols; i++){
                //Prenche com a identidade
                mat JT(A.n_rows, A.n_cols, fill::eye);

                //Calcula o ângulo desejado
                double theta = M_PI/2;
                if (Ares(j,j) != 0) {
                    theta = std::atan(Ares(i,j)/Ares(j,j));
                }

                JT(i,i) = std::cos(theta);
                JT(j,j) = std::cos(theta);
                JT(i,j) = -1*std::sin(theta);
                JT(j,i) = std::sin(theta);

                Ares = JT*Ares;

                QT = JT*QT;

            }
        }

        mat Q = QT.t();
        //Ares é R, multiplica por Q
        //Ares.print("Matriz R:");
        Ares = Ares * Q;
        //Acumula Q
        acum = acum * Q;
    }

    resultado_transformacao res;
    res.newmat = Ares;
    res.transformationseq = acum;
    return res;
}


std::vector<resultado> jacobi_aplicado(mat A, double epsilon)
{
    std::vector<resultado> autovalvec;
    resultado_transformacao res = jacobi(A, epsilon);
    //Encontra os autovetores da matriz resultado
    for (unsigned int i = 0; i < A.n_cols; i++){
        //Autovetores da matriz diagonal são as bases do espaço
        vec autov_mod(A.n_rows, fill::zeros);
        autov_mod(i) = 1.0;
        //Multiplica pela sequência de transformações
        vec autov = res.transformationseq * autov_mod;
        //autov.print("autov:");
        resultado r;
        r.autoval = res.newmat(i,i);
        r.autovec = autov;
        autovalvec.push_back(r);
    }

    return autovalvec;
}


std::vector<resultado> QR_aplicado(mat A, double epsilon)
{
    std::vector<resultado> autovalvec;
    resultado_transformacao res = diagonalizacao_QR(A, epsilon);
    //Encontra os autovetores da matriz resultado
    for (unsigned int i = 0; i < A.n_cols; i++){
        //Autovetores da matriz diagonal são as bases do espaço
        vec autov_mod(A.n_rows, fill::zeros);
        autov_mod(i) = 1.0;
        //Multiplica pela sequência de transformações
        vec autov = res.transformationseq * autov_mod;
        //autov.print("autov:");
        resultado r;
        r.autoval = res.newmat(i,i);
        r.autovec = autov;
        autovalvec.push_back(r);
    }

    return autovalvec;
}


std::vector<resultado> householder_aplicado(mat A, double epsilon)
{
    std::vector<resultado> autovalvec;
    //Aplica Householder, resultado: matriz tridiagonal
    resultado_transformacao res_house = householder_simpl(A);
    //Aplica QR, resultado: matriz diagonal
    resultado_transformacao res_QR = diagonalizacao_QR(res_house.newmat, epsilon);
    //Encontra os autovetores da matriz resultado
    for (unsigned int i = 0; i < A.n_cols; i++){
        //Autovetores da matriz diagonal são as bases do espaço
        vec autov_mod(A.n_rows, fill::zeros);
        autov_mod(i) = 1.0;
        //Multiplica pela sequência de transformações
        vec autov = res_house.transformationseq * res_QR.transformationseq * autov_mod;
        //autov.print("autov:");
        resultado r;
        r.autoval = res_QR.newmat(i,i);
        r.autovec = autov;
        autovalvec.push_back(r);
    }

    return autovalvec;
}
