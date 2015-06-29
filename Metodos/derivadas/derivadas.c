#include "derivadas.h"
#include <math.h>
#include <stdio.h>

int main(){
	double result = first_derivative_central_fourth_error(teste, 2, 0.0001);
	printf("O resultado da derivada é: %lf\n", result);
	return 0;
}

double x2(double x){
	return x*x;
}

double x3(double x){
	return x*x*x;
}

double teste(double x){
	return sqrt(x*x+sin(x));
}

double first_derivative_forward_linear_error(funcao f, double x, double delta){
	return (f(x+delta)-f(x)) / delta;
}
double first_derivative_backward_linear_error(funcao f, double x, double delta){
	return (f(x)-f(x-delta)) / delta;
}
double second_derivative_forward_linear_error(funcao f, double x, double delta){
	return (f(x+2*delta)-2*f(x+delta)+f(x)) / pow(delta,2);
}
double second_derivative_backward_linear_error(funcao f, double x, double delta){
	return (f(x)-2*f(x-delta)+f(x-2*delta)) / pow(delta,2);
}

double first_derivative_forward_quadratic_error(funcao f, double x, double delta){
	return (-1*f(x+2*delta)+4*f(x+delta)-3*f(x)) / (2*delta);
}
double first_derivative_backward_quadratic_error(funcao f, double x, double delta){
	return (f(x-2*delta)-4*f(x-delta)+3*f(x)) / (2*delta);
}
double first_derivative_central_quadratic_error(funcao f, double x, double delta){
	return (f(x+delta)-f(x-delta)) / (2*delta);
}

double second_derivative_forward_quadratic_error(funcao f, double x, double delta){
	return (-f(x+3*delta)+4*f(x+2*delta)-5*f(x+delta)+2*f(x)) / pow(delta,2);
}
double second_derivative_backward_quadratic_error(funcao f, double x, double delta){
	return (-f(x-3*delta)+4*f(x-2*delta)-5*f(x-delta)+2*f(x)) / pow(delta,2);
}
double second_derivative_central_quadratic_error(funcao f, double x, double delta){
	return (f(x+delta)-2*f(x)+f(x-delta)) / pow(delta, 2);
}

double first_derivative_central_fourth_error(funcao f, double x, double delta){
	return (-f(x+2*delta)+8*f(x+delta)-8*f(x-delta)+f(x-2*delta)) / (12*delta);
}
double second_derivative_central_fourth_error(funcao f, double x, double delta){
	return (-f(x+2*delta)+16*f(x+delta)-30*f(x)+16*f(x-delta)-f(x-2*delta)) / (12.0*pow(delta,2));
}