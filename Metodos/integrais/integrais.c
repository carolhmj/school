#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
double gauss_legendre(funcao f, int N, int degree, double a, double b);
double gauss_hermite(funcao f, int N, int degree, double a, double b);
double gauss_laguerre(funcao f, int N, int degree, double a, double b);
double gauss_cheby(funcao f, int N, int degree, double a, double b);
double improper_integral_simple_exponencial(funcao f, double a, double b, int step_limit, double epsilon);
double improper_integral_double_exponencial(funcao f, double a, double b, int step_limit, double epsilon);
double g_simple_exponencial(funcao f, double xi, double a, double b);
double g_double_exponencial(funcao f, double xi, double a, double b);
double double_integral(funcao_dupla f, double xa, double xb, funcao zi, funcao zs);
double calc_double_integral(funcao_dupla f, dupla_integral_func d, double xa, double xb, funcao zi, funcao zs, double epsilon, double step_limit);	
double sen(double x);
double ident(double x);
double x3(double x);
double e_ident(double x);
double funct1(double x);
double func_dupl(double x, double y);

int main(int argc, char const *argv[])
{
	double result = calc_double_integral(func_dupl, double_integral, 0, 1, x3, sen, 0.0001, 10000);
	//double result = gauss_legendre(x3, 1000, 3, 0, 1);
	printf("Resultado foi: %f\n", result);
	return 0;
}

double sen(double x){
	return sin(x);
}

double ident(double x){
	return x;
}

double x3(double x){
	return x*x*x;
}

double e_ident(double x){
	return exp(-(x*x))*x;
}

double funct1(double x){
	return x/sqrt(1-x*x);
}

double func_dupl(double x, double y){
	return x*y;
}

double rectangle_method(funcao f, int N, double a, double b){
	double x, interval, sum = 0;
	interval = (b-a)/N;

	for (int i = 0; i < N-1 ; ++i)
	{

		x = a+(2.0*i+1.0)*(interval/2.0);
		sum += f(x);
	}

	return sum*interval;
}

double newton_c_first_closed(funcao f, int N, double a, double b){
	double x0, x1, interval, sum = 0;
	interval = (b-a)/N;

	for (int i = 0; i < N-1; ++i)
	{
		x0 = a + i*interval;
		x1 = x0 + interval;

		sum += f(x0) + f(x1);
	}
	return sum*(interval/2.0);
}

double newton_c_second_closed(funcao f, int N, double a, double b){
	double x0, x1, x2, interval, delta, sum = 0;
	interval = (b-a)/N;
	delta = interval/2.0;
	
	for (int i = 0; i < N-1; ++i)
	{

		x0 = a + i*interval;
		x1 = x0 + delta;
		x2 = x1 + delta;

		sum += f(x0) + 4.0*f(x1) + f(x2);
	}
	return 1.0/3.0 * sum * delta;
}

double newton_c_third_closed(funcao f, int N, double a, double b){
	double x0, x1, x2, x3, interval, delta, sum = 0;
	interval = (b-a)/N;
	delta = interval/3.0;

	for (int i = 0; i < N-1; ++i)
	{
		x0 = a + i*interval;
		x1 = x0 + delta;
		x2 = x1 + delta;
		x3 = x2 + delta;		
		
		sum += f(x0) + 3.0*f(x1) + 3.0*f(x2) + f(x3);
	}
	return 3.0/8.0 * sum * delta;
}

double newton_c_first_open(funcao f, int N, double a, double b){
	double x0, x1, interval, delta, sum = 0;
	interval = (b-a)/N;
	delta = interval/3.0;

	for (int i = 0; i < N-1; ++i)
	{
		x0 = a + i*interval + delta;
		x1 = x0 + delta;

		sum += f(x0) + f(x1);
	}

	return 3.0/2.0 * sum * delta;
}

double newton_c_second_open(funcao f, int N, double a, double b){
	double x0, x1, x2, interval, delta, sum = 0;
	interval = (b-a)/N;
	delta = interval/4.0;

	for (int i = 0; i < N-1; ++i)
	{
		x0 = a + i*interval + delta;
		x1 = x0 + delta;
		x2 = x1 + delta;

		sum += 2*f(x0) - f(x1) + 2*f(x2);
	}

	return 4.0/3.0 * sum * delta;
}

double newton_c_third_open(funcao f, int N, double a, double b){
	double x0, x1, x2, x3, interval, delta, sum = 0;
	interval = (b-a)/N;
	delta = interval/5.0;

	for (int i = 0; i < N-1; ++i)
	{
		x0 = a + i*interval + delta;
		x1 = x0 + delta;
		x2 = x1 + delta;
		x3 = x2 + delta;			
		sum += 11.0*f(x0) + f(x1) + f(x2) + 11.0*f(x3);
	}
	return 5.0/24.0 * sum * delta;	
}

double calculate_newton_integral(funcao f, metodo m, double epsilon, int step_limit, double a, double b){
	double integral_atual = 0.0, integral_ant = 0.0;
	int N, j = 1;
	
	while(j < step_limit) {
		N = 2*j;
		printf("N: %d\n", N);
		integral_atual = m(f, N, a, b);
		//printf("%lf (%lf)\n", integral_atual, fabs(integral_atual-integral_ant));
		if (fabs(integral_atual - integral_ant) < epsilon) {
			printf("Integral calculada com sucesso!\n");
			return integral_atual;
		}
		integral_ant = integral_atual;
		j++;
	}

	printf("Número de passos superou o máximo!\n");
	return NAN; 
}

double xi_to_x_gauss(double xi, double a, double b){
	return (a+b)*(1.0/2.0) + xi*(b-a)*(1.0/2.0);
}

double xi_to_x_hermite(double xi, double a, double b){
	return (a+b)*(1.0/2.0) + (b-a)*(1.0/2.0)*tanh(xi);
}

double gauss_legendre(funcao f, int N, int degree, double a, double b){
	//Fonte dos pesos: http://pomax.github.io/bezierinfo/legendre-gauss.html
	double sup, inf, sum, integral = 0.0, weighs[degree], abc[degree], interval = (b-a)/N;

	if (degree == 2){
		double assign_w[] = {1.0, 1.0};
		double assign_abc[] = {-0.5773502691896257, 0.5773502691896257};

		for (int i = 0; i < degree; ++i) {
			weighs[i] = assign_w[i];
			abc[i] = assign_abc[i];
		}	
	} else if (degree == 3){
		double assign_w[] = {0.8888888888888888, 0.5555555555555556, 0.5555555555555556};
		double assign_abc[] = {0.0000000000000000, -0.7745966692414834, 0.7745966692414834};

		for (int i = 0; i < degree; ++i) {
			weighs[i] = assign_w[i];
			abc[i] = assign_abc[i];
		}	
	} else if (degree == 4) {
		double assign_w[] = {0.6521451548625461, 0.6521451548625461, 0.3478548451374538, 0.3478548451374538};
		double assign_abc[] = {-0.3399810435848563, 0.3399810435848563, -0.8611363115940526, 0.8611363115940526};	
		
		for (int i = 0; i < degree; ++i) {
			weighs[i] = assign_w[i];
			abc[i] = assign_abc[i];
		}
	} else {
		printf("Por favor, informe um grau entre 2 e 4.\n");
		return NAN;
	}

	for (int i = 0; i < N; ++i)
	{
		
		inf = a + i*interval;
		sup = inf + interval;
		//printf("%lf, %lf\n", inf, sup);
		sum = 0.0;

		for (int j = 0; j < degree; ++j)
		{
			double g = f(xi_to_x_gauss(abc[j], inf, sup));
			double w = weighs[j];

			sum += g*w;
			//printf("%f\n", sum);
		}

		integral += (sup-inf)*(1.0/2.0)*sum;
		printf("%lf\n", integral);
	}

	return integral;
}

double gauss_hermite(funcao f, int N, int degree, double a, double b){
	//Fonte dos pesos: http://www.efunda.com/math/num_integration/findgausshermite.cfm
	double sup, inf, sum, integral = 0.0, weighs[degree], abc[degree], interval = (b-a)/N;

	if (degree == 2){

		double assign_w[] = {0.886226925453, 0.886226925453};
		double assign_abc[] = {-0.707106781187, 0.707106781187};

		for (int i = 0; i < degree; ++i) {
			weighs[i] = assign_w[i];
			abc[i] = assign_abc[i];
		}	
	} else if (degree == 3){
		double assign_w[] = {0.295408975151, 1.1816359006, 0.295408975151};
		double assign_abc[] = {-1.22474487139, 0, 1.22474487139};

		for (int i = 0; i < degree; ++i) {
			weighs[i] = assign_w[i];
			abc[i] = assign_abc[i];
		}	
	} else if (degree == 4) {
		double assign_w[] = {0.0813128354472, 0.804914090006, 0.804914090006, 0.0813128354472};
		double assign_abc[] = {-1.65068012389, -0.524647623275, 0.524647623275, 1.65068012389};	
		
		for (int i = 0; i < degree; ++i) {
			weighs[i] = assign_w[i];
			abc[i] = assign_abc[i];
		}
	} else {
		printf("Por favor, informe um grau entre 2 e 4.\n");
		return NAN;
	}

	for (int i = 0; i < N; ++i)
	{
		
		inf = a + i*interval;
		sup = inf + interval;
		//printf("%lf, %lf\n", inf, sup);
		sum = 0.0;

		for (int j = 0; j < degree; ++j)
		{
			double g = f(xi_to_x_hermite(abc[j], inf, sup));
			double w = weighs[j];

			sum += g*w*exp(pow(abc[j],2))*(1.0/pow(cosh(abc[j]),2));
			//printf("%f\n", sum);
		}

		integral += (sup-inf)*(1.0/2.0)*sum;
		//printf("%lf\n", integral);
	}

	return integral;
}

//Arrumar uma função que mapeia de 0 a infinito
double gauss_laguerre(funcao f, int N, int degree, double a, double b){
	//Fonte dos pesos: http://www.efunda.com/math/num_integration/findgausslaguerre.cfm
	double sup, inf, sum, integral = 0.0, weighs[degree], abc[degree], interval = (b-a)/N;

	if (degree == 2){
		double assign_w[] = {0.853553390593, 0.146446609407};
		double assign_abc[] = {0.585786437627, 3.41421356237};

		for (int i = 0; i < degree; ++i) {
			weighs[i] = assign_w[i];
			abc[i] = assign_abc[i];
		}	
	} else if (degree == 3){
		double assign_w[] = {0.711093009929, 0.278517733569, 0.0103892565016};
		double assign_abc[] = {0.415774556783, 2.29428036028, 6.28994508294};

		for (int i = 0; i < degree; ++i) {
			weighs[i] = assign_w[i];
			abc[i] = assign_abc[i];
		}	
	} else if (degree == 4) {
		double assign_w[] = {0.603154104342, 0.357418692438, 0.038887908515, 0.000539294705561};
		double assign_abc[] = {0.322547689619, 1.74576110116, 4.53662029692, 9.3950709123};	
		
		for (int i = 0; i < degree; ++i) {
			weighs[i] = assign_w[i];
			abc[i] = assign_abc[i];
		}
	} else {
		printf("Por favor, informe um grau entre 2 e 4.\n");
		return NAN;
	}

	for (int i = 0; i < N; ++i)
	{
		
		inf = a + i*interval;
		sup = inf + interval;
		//printf("%lf, %lf\n", inf, sup);
		sum = 0.0;

		for (int j = 0; j < degree; ++j)
		{
			double g = f(xi_to_x_gauss(abc[j], inf, sup));
			double w = weighs[j];

			sum += g*w*exp(abc[j]);
			//printf("%f\n", sum);
		}

		integral += (sup-inf)*(1.0/2.0)*sum;
		printf("%lf\n", integral);
	}

	return integral;
}

double gauss_cheby(funcao f, int N, int degree, double a, double b){
	double sup, inf, sum, integral = 0.0, interval = (b-a)/N;

	for (int i = 0; i < N; ++i)
	{
		inf = a + i*interval;
		sup = inf + interval;
		//printf("%lf, %lf\n", inf, sup);

		sum = 0.0;

		for (int j = 1; j <= degree; ++j)
		{
			double xi = cos( PI * (2.0*j-1.0)/(2.0*degree) );

			double g = f(xi_to_x_gauss(xi, inf, sup)) * sqrt(1-(xi*xi));
			//printf("raiz: %lf funcao: %lf\n", sqrt((1-xi*xi)), f(xi_to_x_gauss(xi, inf, sup)));
			sum += g;
			//printf("sum: \t%lf\n", sum);
		}
		
		integral += ( (PI/degree)*(sup-inf)*(1.0/2.0) ) * sum;
		//printf("%lf\n", integral);
	}

	return integral;
}

double g_simple_exponencial(funcao f, double xi, double a, double b){
	double deriv = (b-a)*(2.0/(exp(2*xi)+2+exp(-2*xi)));
	double x = (a+b)/2.0 + ((b-a)/2.0)*tanh(xi);

	return f(x)*deriv;
}

double g_double_exponencial(funcao f, double xi, double a, double b){
	double u = (PI/2.0)*sinh(xi);
	double deriv = (b-a)*( (PI * (exp(xi)+exp(-xi)) ) / (exp(2*u)+2+exp(-2*u)) );
	double x = (a+b)/2.0 + ((b-a)/2.0)*tanh((PI/2.0)*sinh(xi));

	return f(x)*deriv;
}

double improper_integral_simple_exponencial(funcao f, double a, double b, int step_limit, double epsilon){
	double inf_interval = -1, sup_interval = 1, xi_inf, xi_sup, integral_atual = 0.0, integral_ant = 0.0, integral_c_atual = 0.0, integral_c_anterior = 0.0;
	int N;

	for (int i = 1; i <= step_limit; ++i)
	{
		xi_inf = inf_interval*i;
		xi_sup = sup_interval*i;
		printf("xi_inf: %lf xi_sup: %lf\n", xi_inf, xi_sup);
		printf("i: %d\n", i);
		for (int j = 1; j <= step_limit; ++j)
		{
			N = 2*j;

			double xi, interval = (xi_sup-xi_inf)/N, sum = 0.0;
			printf("j: %d, N: %d\n", j, N);
			for (int k = 0; k < N; ++k)
			{
				printf("k: %d\n", k);
				xi = xi_inf+(2.0*k+1.0)*(interval/2.0);
				printf("xi: %lf ", xi);
				sum += g_simple_exponencial(f, xi, a, b);
				printf("sum: %lf\n", sum);
			}

			integral_atual = sum*interval;
			printf("integral_atual: %lf\n", integral_atual);

			if (fabs(integral_atual - integral_ant) < epsilon) {
				break;
			}

			integral_ant = integral_atual;
		}

		integral_c_atual = integral_atual;
		printf("integral_c_atual: %lf\n", integral_c_atual);
		printf("integral_c_anterior: %lf\n", integral_c_anterior);
		if (fabs(integral_c_atual - integral_c_anterior) < epsilon) {
			return integral_c_atual;
		}
		integral_c_anterior = integral_c_atual;
	}

	return NAN;
}

double improper_integral_double_exponencial(funcao f, double a, double b, int step_limit, double epsilon){
	double inf_interval = -1, sup_interval = 1, xi_inf, xi_sup, integral_atual = 0.0, integral_ant = 0.0, integral_c_atual = 0.0, integral_c_anterior = 0.0;
	int N;

	for (int i = 1; i <= step_limit; ++i)
	{
		xi_inf = inf_interval*i;
		xi_sup = sup_interval*i;
		//printf("xi_inf: %lf xi_sup: %lf\n", xi_inf, xi_sup);
		//printf("i: %d\n", i);
		for (int j = 1; j <= step_limit; ++j)
		{
			N = 2*j;

			double xi, interval = (xi_sup-xi_inf)/N, sum = 0.0;
			//printf("j: %d, N: %d\n", j, N);
			for (int k = 0; k < N; ++k)
			{
				//printf("k: %d\n", k);
				xi = xi_inf+(2.0*k+1.0)*(interval/2.0);
				//printf("xi: %lf ", xi);
				sum += g_double_exponencial(f, xi, a, b);
				//printf("sum: %lf\n", sum);
			}

			integral_atual = sum*interval;
			//printf("integral_atual: %lf\n", integral_atual);

			if (fabs(integral_atual - integral_ant) < epsilon) {
				break;
			}

			integral_ant = integral_atual;
		}

		integral_c_atual = integral_atual;
		//printf("integral_c_atual: %lf\n", integral_c_atual);
		//printf("integral_c_anterior: %lf\n", integral_c_anterior);
		if (fabs(integral_c_atual - integral_c_anterior) < epsilon) {
			return integral_c_atual;
		}
		integral_c_anterior = integral_c_atual;
	}

	return NAN;
}

double double_integral(funcao_dupla f, double xa, double xb, funcao yi, funcao ys){
	int degree = 3;
	double constant_x, constant_y, x, y, sum = 0.0, weighs[] = {0.8888888888888888, 0.5555555555555556, 0.5555555555555556}, abc[] = {0.0000000000000000, -0.7745966692414834, 0.7745966692414834};

	constant_x = (xb-xa)/2.0;
	for (int eta = 0; eta < degree; ++eta)
	{
		x = xi_to_x_gauss(abc[eta], xa, xb);
		for (int xi = 0; xi < degree; ++xi)
		{
			double yi_val = yi(x), ys_val = ys(x);
			printf("yi_val: %lf ys_val: %lf\n", yi_val, ys_val);
			constant_y = (ys_val-yi_val)/2.0;
			printf("const_y: %lf\n", constant_y);
			y = xi_to_x_gauss(abc[xi], yi_val, ys_val);

			sum += constant_y*weighs[eta]*weighs[xi]*f(x,y);
			printf("sum: %lf\n", sum);
		}
	}
	return sum*constant_x;
}

double calc_double_integral(funcao_dupla f, dupla_integral_func d, double xa, double xb, funcao zi, funcao zs, double epsilon, double step_limit){
	double integral_ant = 0.0, integral_atual = 0.0, x_inf, x_sup, interval, N;

	for (int i = 1; i <= step_limit; ++i)
	{
		N = 2*i;
		interval = (xb-xa)/N;
		integral_atual = 0.0;
		for (int j = 0; j < N; ++j)
		{
			x_inf = xa+interval*j;
			x_sup = x_inf+interval;

			integral_atual += d(f, x_inf, x_sup, zi, zs);
		}

		if (fabs(integral_atual-integral_ant) < epsilon) {
			return integral_atual;
		}

		integral_ant = integral_atual;
	}

	return NAN;
}