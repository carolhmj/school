#include "inic.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double teste(double y, double t){
	return -20*y+7*exp(0.5*t);
}

int main()
{
	double res = foward_euler(teste,5,0,0.01,2);
	printf("resultado é: %lf\n", res);
	return 0;
}