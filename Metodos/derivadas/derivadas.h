#ifndef derivadas
#define derivadas

typedef double(*funcao)(double);

//Fórmulas com erro linear
double first_derivative_forward_linear_error(funcao f, double x, double delta);
double first_derivative_backward_linear_error(funcao f, double x, double delta);
double second_derivative_forward_linear_error(funcao f, double x, double delta);
double second_derivative_backward_linear_error(funcao f, double x, double delta);

//Fórmulas com erro quadrático
double first_derivative_forward_quadratic_error(funcao f, double x, double delta);
double first_derivative_backward_quadratic_error(funcao f, double x, double delta);
double first_derivative_central_quadratic_error(funcao f, double x, double delta);
double second_derivative_forward_quadratic_error(funcao f, double x, double delta);
double second_derivative_backward_quadratic_error(funcao f, double x, double delta);
double second_derivative_central_quadratic_error(funcao f, double x, double delta);


//Fórmulas com erro cúbico
double first_derivative_central_fourth_error(funcao f, double x, double delta);
double second_derivative_central_fourth_error(funcao f, double x, double delta);

double x2(double x);
double x3(double x);
double teste(double x);

#endif