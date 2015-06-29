#ifndef INTEGRAIS_H
#define INTEGRAIS_H

#define PI 3.14159265358979323846

typedef double(*funcao)(double);
typedef double(*metodo)(funcao, int, double, double);
typedef double(*funcao_dupla)(double, double);
typedef double(*dupla_integral_func)(funcao_dupla, double, double, funcao, funcao);

double rectangle_method(funcao f, int N, double a, double b);
double newton_c_first_closed(funcao f, int N, double a, double b);
double newton_c_second_closed(funcao f, int N, double a, double b);
double newton_c_third_closed(funcao f, int N, double a, double b);
double newton_c_first_open(funcao f, int N, double a, double b);
double newton_c_second_open(funcao f, int N, double a, double b);
double newton_c_third_open(funcao f, int N, double a, double b);
double calculate_newton_integral(funcao f, metodo m, double epsilon, int step_limit, double a, double b);
double xi_to_x_gauss(double xi, double a, double b);
double xi_to_x_hermite(double xi, double a, double b);
double gauss_legendre(funcao f, double a, double b, int degree, int step_limit, double epsilon);
double gauss_hermite(funcao f, int N, int degree, double a, double b);
double gauss_laguerre(funcao f, int N, int degree, double a, double b);
double gauss_cheby(funcao f, int N, int degree, double a, double b);
double improper_integral_simple_exponencial(funcao f, double a, double b, int step_limit, double epsilon);
double improper_integral_double_exponencial(funcao f, double a, double b, int step_limit, double epsilon);
double g_simple_exponencial(funcao f, double xi, double a, double b);
double g_double_exponencial(funcao f, double xi, double a, double b);
double double_integral(funcao_dupla f, double xa, double xb, funcao zi, funcao zs);
double calc_double_integral(funcao_dupla f, dupla_integral_func d, double xa, double xb, funcao zi, funcao zs, double epsilon, double step_limit);	
double teste(double x);
double teste_dupla(double x, double y);
#endif