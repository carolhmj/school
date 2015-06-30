#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integrais.h"

int main(int argc, char const *argv[])
{
	double result = improper_integral_simple_exponencial(teste, 1, INFINITY, 1000, 0.0001);
	printf("O resultado da integral é: %f\n", result);
	//double tester = g_simple_exponencial(teste, 2, 1, 10);
	//printf("%lf\n", tester);
	return 0;
}

double teste(double x){
	return 1/pow(x,3);
}
double teste_dupla(double x, double y){
	return x+y;
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
		integral_atual = m(f, N, a, b);
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

double gauss_legendre(funcao f, double a, double b, int degree, int step_limit, double epsilon){
	//Fonte dos pesos: http://pomax.github.io/bezierinfo/legendre-gauss.html
	double sup, inf, sum, integral_ant, integral = 0.0, weighs[degree], abc[degree], interval;
	int k = 1, N;
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

	while (k < step_limit) {

		integral_ant = integral;
		N = 1*k;

		integral = 0.0;

		interval = (b-a)/N;
		
		for (int i = 0; i < N; ++i)
		{
			
			inf = a + i*interval;
			sup = inf + interval;
			printf("inf: %lf, sup: %lf\n", inf, sup);
			sum = 0.0;

			for (int j = 0; j < degree; ++j)
			{
				double g = f(xi_to_x_gauss(abc[j], inf, sup));
				printf("xi to x: %lf\n", xi_to_x_gauss(abc[j], inf, sup));
				double w = weighs[j];
				printf("g: %lf, w: %lf\n", g, w);
				sum += g*w;
				printf("sum: %f\n", sum);
			}

			integral += (sup-inf)*(1.0/2.0)*sum;
			printf("%lf\n", integral);
		
		}

		k++;

		if (fabs(integral_ant - integral) < epsilon){
			return integral;
		}
	}
	
	printf("Número de passos superou o máximo!\n");
	return NAN; 
}


double gauss_hermite(funcao f, int degree){
	//Fonte dos pesos: http://www.efunda.com/math/num_integration/findgausshermite.cfm
	double integral = 0.0, weighs[degree], abc[degree];

	//Armazena as abcissas e os pesos = peso_k * e^(-(abcissa_k)^2)
	if (degree == 2){

		double assign_w[] = {1.46114118266, 1.46114118266};
		double assign_abc[] = {-0.707106781187, 0.707106781187};

		for (int i = 0; i < degree; ++i) {
			weighs[i] = assign_w[i];
			abc[i] = assign_abc[i];
		}	
	} else if (degree == 3){
		double assign_w[] = {1.32393117521, 1.1816359006, 1.32393117521};
		double assign_abc[] = {-1.22474487139, 0, 1.22474487139};

		for (int i = 0; i < degree; ++i) {
			weighs[i] = assign_w[i];
			abc[i] = assign_abc[i];
		}	
	} else if (degree == 4) {
		double assign_w[] = {1.2402258177, 1.05996448289, 1.05996448289, 1.2402258177};
		double assign_abc[] = {-1.65068012389, -0.524647623275, 0.524647623275, 1.65068012389};	
		
		for (int i = 0; i < degree; ++i) {
			weighs[i] = assign_w[i];
			abc[i] = assign_abc[i];
		}
	} else {
		printf("Por favor, informe um grau entre 2 e 4.\n");
		return NAN;
	}


	for (int i = 0; i < degree; i++) {
		integral += weighs[i] * f(abc[i]);
	}

	return integral;
}


double gauss_laguerre(funcao f, int degree){
	//Fonte dos pesos: http://www.efunda.com/math/num_integration/findgausslaguerre.cfm
	double integral = 0.0, weighs[degree], abc[degree];

	//Armazena as abcissas e os pesos = peso_k * e^(abcissa_k)
	if (degree == 2){
		double assign_w[] = {1.53332603312, 4.45095733505};
		double assign_abc[] = {0.585786437627, 3.41421356237};

		for (int i = 0; i < degree; ++i) {
			weighs[i] = assign_w[i];
			abc[i] = assign_abc[i];
		}	
	} else if (degree == 3){
		double assign_w[] = {1.07769285927, 2.7621429619, 5.60109462543};
		double assign_abc[] = {0.415774556783, 2.29428036028, 6.28994508294};

		for (int i = 0; i < degree; ++i) {
			weighs[i] = assign_w[i];
			abc[i] = assign_abc[i];
		}	
	} else if (degree == 4) {
		double assign_w[] = {0.832739123838, 2.04810243845, 3.63114630582, 6.48714508441};
		double assign_abc[] = {0.322547689619, 1.74576110116, 4.53662029692, 9.3950709123};	
		
		for (int i = 0; i < degree; ++i) {
			weighs[i] = assign_w[i];
			abc[i] = assign_abc[i];
		}
	} else {
		printf("Por favor, informe um grau entre 2 e 4.\n");
		return NAN;
	}

	for (int i = 0; i < degree; i++) {
		integral += weighs[i] * f(abc[i]);
	}

	return integral;
}

double gauss_cheby(funcao f, int degree){
	//Fonte dos pesos: http://keisan.casio.com/exec/system/1329114617
	double integral = 0.0, weighs[degree], abc[degree];

	//Armazena as abcissas e os pesos = peso_k * 1/(sqrt(1-abcissa_k^2))
	if (degree == 2){
		double assign_w[] = {1.1107207345396, 1.1107207345396};
		double assign_abc[] = {-0.70710678118655,0.70710678118655};

		for (int i = 0; i < degree; ++i) {
			weighs[i] = assign_w[i];
			abc[i] = assign_abc[i];
		}	
	} else if (degree == 3){
		double assign_w[] = {0.5235987755983, 1.0471975511966, 0.5235987755983};
		double assign_abc[] = {-0.86602540378444, 0, 0.86602540378444};

		for (int i = 0; i < degree; ++i) {
			weighs[i] = assign_w[i];
			abc[i] = assign_abc[i];
		}	
	} else if (degree == 4) {
		double assign_w[] = {0.30055886494217, 0.72561328803486, 0.72561328803486, 0.3005588649422};
		double assign_abc[] = {-0.92387953251129, -0.38268343236509, 0.38268343236509, 0.92387953251129};	
		
		for (int i = 0; i < degree; ++i) {
			weighs[i] = assign_w[i];
			abc[i] = assign_abc[i];
		}
	} else {
		printf("Por favor, informe um grau entre 2 e 4.\n");
		return NAN;
	}

	for (int i = 0; i < degree; i++) {
		integral += weighs[i] * f(abc[i]);
	}

	return integral;
}

double g_simple_exponencial(funcao f, double xi, double a, double b){
	double deriv = (b-a)*(2.0/(exp(2*xi)+2+exp(-2*xi)));
	printf("%lf deriv\n",deriv);
	double x = (a+b)/2.0 + ((b-a)/2.0)*tanh(xi);
	printf("%lf x\n", x);
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
		//printf("xi_inf: %lf xi_sup: %lf\n", xi_inf, xi_sup);
		//printf("i: %d\n", i);
		for (int j = 1; j <= step_limit; ++j)
		{
			N = 2*i;

			double xi, interval = (xi_sup-xi_inf)/N, sum = 0.0;
			printf("j: %d, N: %d\n", j, N);
			for (int k = 0; k < N; ++k)
			{
				//printf("k: %d\n", k);
				xi = xi_inf+(2.0*k+1.0)*(interval/2.0);
				//printf("xi: %lf ", xi);
				sum += g_simple_exponencial(f, xi, a, b);
				//sum += g_simple_exponencial(f, xi, xi_inf, xi_sup);
				printf("sum: %lf\n", sum);
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
	printf("Número de passos excedido!\n");
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
			//printf("yi_val: %lf ys_val: %lf\n", yi_val, ys_val);
			constant_y = (ys_val-yi_val)/2.0;
			//printf("const_y: %lf\n", constant_y);
			y = xi_to_x_gauss(abc[xi], yi_val, ys_val);

			sum += constant_y*weighs[eta]*weighs[xi]*f(x,y);
			//printf("sum: %lf\n", sum);
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