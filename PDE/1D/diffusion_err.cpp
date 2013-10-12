#include "ODE/RKMethod/ERKMethod.h"
#include "ODE/RKMethod/EulerMethod.h"
#include "ODE/RKMethod/ButcherTable.h"
#include <cmath>
#include <stdint.h>
#include <iostream>

using namespace zarath;

void* Diffusion1(double *x, void *param, double* dx);
void* Diffusion2(double *x, void *param, double* dx);
double pos(unsigned int index);

void *PCMethod(double *x, void *param, double *next_x, vfunc f, double *dt, double *abs_err, double *rel_err)
{
	double *DT;
	uint64_t dim = *(uint64_t*)param;
	double buf[dim], buf2[dim];
	DT = (double*)ERKMethod(x, param, buf, f, dt, abs_err, rel_err);
	f(buf, param, buf2);
	for(unsigned int i = 0; i < dim; ++i)
		next_x[i] = x[i] + buf2[i]* *dt;
	return DT;
}

struct
{
	double min, max;
	unsigned int point_num;
	double D;
}range;

double u_exact(double t, double x){return exp(-range.D*M_PI*M_PI*t)*cos(M_PI*x);}
double integ(double* x, int len)
{
	double dx = fabs(x[1] - x[0]);
	double sum = 0;
	for(int i = 0; i < len; ++i)
		sum += x[i]*dx;
	return sum;
}

int main()
{
	uint64_t dim = 256;
	double t = 0, dt = 0;
	double abs_err = 1e-14, rel_err = abs_err;
	double next[dim];
	double x[dim];
	double sym_err = 0, x_sym_err;
	double *tdt;

	range.min = -0.5;
	range.max = 0.5;
	range.point_num = dim;
	range.D = 1;

	//3point runge-kutta 0.69983 - 0.69984 
	//5point runge-kutta 0.52487 - 0.52488 
	dt = 0.5 * ((range.max - range.min)/dim)*((range.max - range.min)/dim);

	for(unsigned int i = 0; i < dim; ++i)
		x[i] = cos(M_PI*pos(i));

	InitializeButcherTable();
	SetButcherTable(GetButcherTable(RungeKutta));

	rkmethod rm = ERKMethod;//EulerMethodAuto;//ERKMethod;

	do
	{
		x_sym_err = sym_err = 0;
		Diffusion1(x, &dim, next);
		for(unsigned int i = 0; i < dim; ++i)
			sym_err += fabs(next[i] - next[dim - 1 - i]), x_sym_err += fabs(x[i] - x[dim - 1 - i]);
		sym_err *= 0.5;
		x_sym_err *= 0.5;

		tdt = (double*)rm(x, &dim, x, Diffusion2, &dt, &abs_err, &rel_err);
		t += ((tdt)?(*tdt):(dt));
		//for(unsigned int i = 0; i < dim; ++i)
		//	x[i] = next[i];
	 	//dt = DT;

		double err[dim];
		for(unsigned int i = 0; i < range.point_num; ++i)
			err[i] = fabs(x[i] - u_exact(t , pos(i)));

		double err_integ = integ(err, dim);


		//std::cout << std::scientific << t << " " << err_integ << std::endl;
		std::cerr << "\r" << "a_err = " << std::scientific << err_integ << " t = " << t << " sym_err = " << sym_err
			<< " x_sym_err = " << x_sym_err;
	}while(t > 0 && 1 > t);

	std::cerr << std::endl;

	FinalizeButcherTable();
}

//3-points
void* Diffusion1(double *x, void *param, double* dx)
{
	uint64_t dim = *((uint64_t*)param);
	double dx2inv = 1/((pos(1) - pos(0))*(pos(1) - pos(0)));
	dx[0] = (-3*x[0] + x[1])*dx2inv;
	for(unsigned int i = 1; i < dim - 1; ++i)
		dx[i] = (x[i - 1] + x[i + 1] - 2*x[i])*dx2inv;
	dx[dim - 1] = (x[dim - 2] - 3*x[dim - 1])*dx2inv;
	return 0;
}

void* Diffusion2(double *x, void *param, double* dx)
{
	uint64_t dim = *((uint64_t*)param);
	double dx2inv = 1/(12*(pos(1) - pos(0))*(pos(1) - pos(0)));
	dx[0] = ((-46*x[0] - x[2]) + 17*x[1])*dx2inv;
	dx[1] = ((17*x[0] + 16*x[2]) + (-x[3] - 30*x[1]))*dx2inv;
	for(unsigned int i = 2; i < dim - 2; ++i)
		dx[i] = ((-x[i - 2] - x[i + 2] - 30*x[i]) + (16*x[i - 1] + 16*x[i + 1]))*dx2inv;
	dx[dim - 2] = ((-x[dim - 4]- 30*x[dim - 2]) + (17*x[dim - 1] + 16*x[dim - 3]))*dx2inv;
	dx[dim - 1] = ((-x[dim - 3] - 46*x[dim - 1]) + 17*x[dim - 2])*dx2inv;
	return 0;
}

double pos(unsigned int index)
{
	double dx = (range.max - range.min)/range.point_num;
	return index*dx + range.min + dx/2;
}
