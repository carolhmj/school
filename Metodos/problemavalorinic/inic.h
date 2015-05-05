#ifndef INIC_H
#define INIC_H

typedef double(*funcao)(double,double);

double foward_euler(funcao f, double val_inicial, double time_inicial, double timestep, int numsteps);

#endif