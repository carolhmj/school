#include "inic.h"
#include <stdio.h>
#include <stdlib.h> 

double foward_euler(funcao f, double val_inicial, double time_inicial, double timestep, int numsteps){
	double current_val;
	double ant_val = val_inicial; //Valor em step = 0

	for (int n=1; n<=numsteps; n++){
		printf("n: %d ", n);
		current_val = ant_val + timestep*f(ant_val, time_inicial + n*timestep);
		ant_val = current_val;
		printf("curr val: %lf \n", current_val);
	}

	return current_val;
}