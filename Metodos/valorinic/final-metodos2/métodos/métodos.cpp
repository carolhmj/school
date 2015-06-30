#include "métodos.h"
#include <cassert>
#include <cmath>
#include <cstdio>

double chp::ForwardEuler::operator()(double x) {
	double y = y0;
	for (double i = 0; fabs(x-i) >= step; i+=step) {
		y += step*f(y,i);
	}
	return y;
}

double chp::BackwardEuler::operator()(double x) {
	// (yn+1)^0 = yn
	// (yn+1)^k = yn + step*f((yn+1)^k-1,x)
	double y = y0;
	for (double i = 0; fabs(x-i) >= step; i+=step) {
		y = chp::pontoFixo([&](double yn){return y+step*f(yn,i+step);},epsilon,y);
	}
	return y;
}

double chp::EulerModificado::operator()(double x){
	double yn1 = y0;
	for (double i=0; fabs(x-i)>=step; i+=step) {
		yn1 = chp::pontoFixo([&](double yn2){return yn1+(step/2)*(f(yn2,i+step)+f(yn1,i));},epsilon,yn1);
	}
	return yn1;
}

double chp::RungeKutta::operator()(double x){
	double yn1 = y0, k1, k2;
	for (double i=0;fabs(x-i)>=step;i+=step){
		k1 = step*f(yn1,i);
		k2 = step*f(yn1+k1,i+step);
		yn1 = yn1 + (k1+k2)/2;
	}
	return yn1;
}

double chp::RungeKutta3::operator()(double x) {
	double y = y0, k[3];
	for (double i = 0; fabs(x-i) >= step; i+=step) {
		k[0] = step*f(y,i);
		k[1] = step*f(y+k[0]/2,i+(step/2));
		k[2] = step*f(y-k[0]+2*k[1],i+step);
		y += (k[0]+4*k[1]+k[2])/6;
	}
	return y;
}

double chp::RungeKutta4::operator()(double x) {
	double y = y0, k[4];

	for (double i = 0; fabs(x-i) >= step; i+=step) {
		k[0] = step * f(y, i);
		k[1] = step * f(y + k[0]/3, i + step/3); 
		k[2] = step * f(y + k[0]/3 + k[1]/3, i + 2*step/3);
		k[3] = step * f(y + k[0] - k[1] + k[2], i + step);
		y += (k[0] + 3*k[1] + 3*k[2] + k[3])/8;
	}

	return y;	
}

double chp::PreditorCorretor3::operator()(double x) {
	double yDeriv[4], y[4], i = 0;
	
	y[0] = y0;
	yDeriv[0] = f(y[0], i);
	
	y[1] = y[0] + step*f(y[0], i);
	i += step;
	yDeriv[1] = f(y[1], i);

	if (fabs(x-i) < step) {
		return y[1]; 
	}

	y[2] = y[1] + step*f(y[1], i);
	i += step;
	yDeriv[2] = f(y[2], i);

	if (fabs(x-i) < step) {
		return y[2]; 
	}
 
	while (fabs(x-i) >= step) {
		//Predição
		y[3] = y[2] + (step/12) * (23*yDeriv[2] - 16*yDeriv[1] + 5*yDeriv[0]);
		i += step;
		yDeriv[3] = f(y[3], i);

		//Correção
		y[3] = y[2] + (step/12) * (5*yDeriv[3] + 8*yDeriv[2] - yDeriv[1]);
		yDeriv[3] = f(y[3], i);

		//Atualização
		for (int j = 0; j < 3; j++){
			y[j] = y[j+1];
			yDeriv[j] = yDeriv[j+1];
		}
	}

	return y[3]; 
}

double chp::PreditorCorretor4::operator()(double x) {
	double yDeriv[5], y[5], t = 0;
	
	y[0] = y0;
	yDeriv[0] = f(y[0], t);
 
	for (int j = 1; j < 4; j++){
		y[j] = y[j-1] + step*f(y[j-1], t);
		t += step;
		yDeriv[j] = f(y[j], t);

		if (fabs(x-t) < step) {
			return y[j];
		} 
	}

	while (fabs(x-t) >= step) {
		//Predição
		y[4] = y[3] + (step/24) * (55*yDeriv[3] - 59*yDeriv[2] + 37*yDeriv[1] - 9*yDeriv[0]);
		t += step;
		yDeriv[4] = f(y[4], t);

		//Correção
		y[4] = y[3] + (step/24) * (9*yDeriv[4] + 19*yDeriv[3] - 5*yDeriv[2] + yDeriv[1]);
		yDeriv[4] = f(y[4], t);

		//Atualização
		for (int j = 0; j < 4; j++){
			y[j] = y[j+1];
			yDeriv[j] = yDeriv[j+1];
		}
	}

	return y[4]; 
}

double chp::pontoFixo(funcaoReal f, double epsilon, double x0) {
	double x = x0;
	while(fabs(f(x) - x) >= epsilon) {
		x = f(x);
	}
	return f(x);
}
