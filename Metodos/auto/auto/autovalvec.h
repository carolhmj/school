#ifndef AUTOVALVEC_H
#define AUTOVALVEC_H
#include <armadillo>

using namespace arma;

#define SIGN(x) (x>0) - (x<0)

typedef struct resultado_{
    vec autovec;
    double autoval;
} resultado;

typedef struct resultado_transformacao_{
    mat newmat;
    mat transformationseq;
} resultado_transformacao;

//Função que aplica o método da potência regular para encontrar o maior autovalor de A, e seu vetor correspondente. Assume que A possui um único maior autovalor
resultado potencia_regular(mat A, vec inicial, double epsilon);
//Função que aplica o método da potência inversa para encontrar o menor autovalor de A, e seu vetor correspondente. Assume que A possui um único menor autovalor
resultado potencia_inversa(mat A, vec inicial, double epsilon);
//Função que aplica o método da potência com deslocamento para encontrar os autovalores possíveis entre o menor e o maior autovalores. Assume que A possui um maior autovalor, um menor autovalor e autovalores distintos entre eles
std::vector<resultado> potencia_deslocamento(mat A, vec inicial, double epsilon, double deslocamento);
//Função que simplifica a matriz dada usando a técnica de householder
resultado_transformacao householder_simpl(mat A);
//Função usada na técnica de householder, que obtém a normal do espelho
vec construir_n(mat A, int j);
#endif // AUTOVALVEC_H
