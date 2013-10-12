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

struct
{
	double min, max;
	unsigned int point_num;
	double D;
	int freq;
}range;

double u_exact(double t, double x){return exp(-range.D*M_PI*M_PI*range.freq*range.freq*t)*cos(M_PI*range.freq*x);}
double integ(double* x, int len)
{
	double dx = fabs(x[1] - x[0]);
	double sum = 0;
	for(int i = 0; i < len; ++i)
		sum += x[i]*dx;
	return sum;
}

double err(uint64_t dim, double ar_err, double h, rkmethod solver, void *(*diffusion)(double*, void*, double*))
{
	double t = 0, *tdt;

	double err_array[dim];
	double x[dim];

	for(unsigned int i = 0; i < dim; ++i)
		x[i] = cos(M_PI*range.freq * pos(i));
	double err_max = 0, err_integ;

	while(t < 1)
	{
		tdt = (double*)solver(x, &dim, x, diffusion, &h, &ar_err, &ar_err);
		t += ((tdt)?(*tdt):(h));

		for(unsigned int i = 0; i < dim; ++i)
			err_array[i] = fabs(x[i] - u_exact(t, pos(i)));
		err_integ = integ(err_array, dim);
		err_max = ((err_max < err_integ)?(err_integ):(err_max));
	}
	return err_max;
}

int main()
{
	uint64_t dim = 20;
	range.min = -0.5;
	range.max = 0.5;
	range.point_num = dim;
	range.D = 1;
	range.freq = 1;
	double dx = (range.max - range.min)/dim;
	double dt = 0.5*dx*dx;
	double ar_err = 1e-14;

	InitializeButcherTable();
	SetButcherTable(GetButcherTable(RungeKutta));

/*	for(int i = 1; i < 101; i++)
	{
		dim = i*10;
		range.point_num = dim;
		dx = (range.max - range.min)/dim;
		for(int j = 1; j < 6; ++j)
		{
			dt = 0.1*j*dx*dx;
			std::cout << dt << " " << dim << " " << err(dim, ar_err, dt, ERKMethod, Diffusion2) << std::endl;
		}
		std::cout << std::endl;
	}
*/
	for(int i = 1; i < 31; i++)
	{
		dim = i*10;
		range.point_num = dim;
		dx = (range.max - range.min)/dim;
		dt = 0.5*dx*dx;
		std::cout << dt << " " << dim << " " << err(dim, ar_err, dt, ERKMethod, Diffusion1) << std::endl;
	}
	std::cout << std::endl;
	for(int i = 1; i < 31; i++)
	{
		dim = i*10;
		range.point_num = dim;
		dx = (range.max - range.min)/dim;
		dt = 0.5*dx*dx;
		std::cout << dt << " " << dim << " " << err(dim, ar_err, dt, ERKMethod, Diffusion2) << std::endl;
	}


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
