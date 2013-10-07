#include "ODE/RKMethod/ERKMethod.h"
#include "ODE/RKMethod/EulerMethod.h"
#include "ODE/RKMethod/ButcherTable.h"
#include <cmath>
#include <stdint.h>
#include <ctime>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <glsc.h>

using namespace zarath;

void* Wave1(double *x, void *param, double *dx);
void* Wave11(double *x, void *param, double *dx);
void* Wave21(double *x, void *param, double *dx);
void* Diffusion1(double *x, void *param, double* dx);
void* Diffusion11(double *x, void *param, double* dx);
void* Diffusion21(double *x, void *param, double* dx);
void* Diffusion2(double *x, void *param, double* dx);
double pos(unsigned int index);

void *PCMethod(double *x, void *param, double *next_x, vfunc f, double *dt, double *abs_err, double *rel_err)
{
	double *DT;
	uint64_t dim = *(uint64_t*)param;
	double buf[dim], buf2[dim];
	DT = (double*)ERKMethod(x, param, buf, f, dt, abs_err, rel_err);
	f(buf, param, buf2);
	for(int i = 0; i < dim; ++i)
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
	double margin = 0.1;
	uint64_t dim = 64, w = 2000, c = 0, n = 1;
	double t = 0, dt = 0, tmax = 20, *dtd;
	double abs_err = 1e-1, rel_err = abs_err;
	double x[dim], next[dim];

	range.min = -0.5;
	range.max = 0.5;
	range.point_num = dim;
	range.D = 1;

	//3point runge-kutta 0.69983 - 0.69984 time:20
	//5point runge-kutta 0.52487 - 0.52488 time:20
	double DT = dt = 0.701 * ((range.max - range.min)/dim)*((range.max - range.min)/dim);

	for(int i = 0; i < dim; ++i)
		x[i] = cos(M_PI*pos(i));

//	for(int i = 0; i < dim; ++i)
//		std::cout << x[i] - x[dim - 1 - i] << std::endl;

//	exit(0);

	InitializeButcherTable();
	SetButcherTable(GetButcherTable(RungeKutta));

	rkmethod rm = ERKMethod;

	g_init("plot", 200, 200);
	g_device(G_DISP);

	g_def_scale(0, range.min - margin, range.max + margin, -1 - margin, 1 + margin, 0, 0, 200, 200);

	g_sel_scale(0);
	do
	{
		g_sleep(1./60);
	//	g_sleep(G_STOP);
		g_cls();

		g_line_color(G_BLACK);
		g_move(range.min, 0);
		g_plot(range.max, 0);

		g_move(0, range.min);
		g_plot(0, range.max);
		dtd = (double*)rm(x, &dim, next, Diffusion1, &dt, &abs_err, &rel_err);
		for(int i = 0; i < dim; ++i)
			x[i] = next[i];
		std::cout << (t += ((!dtd)?(*dtd):(DT)));
	 	//dt = DT;

		g_line_color(G_GREEN);
		g_move(pos(0), x[0]);
		for(int i = 0; i < dim; ++i)
			g_plot(pos(i), x[i]);
		
		double err[dim];
		for(int i = 0; i < range.point_num; ++i)
			err[i] = fabs(x[i] - u_exact(t , pos(i)));

		double err_integ = integ(err, dim);

		g_line_color(G_BLUE);
		g_move(pos(0), u_exact(t, pos(0)));
		for(int i = 0; i < dim; ++i)
			g_plot(pos(i), u_exact(t, pos(i)));

		for(int i = 0; i < range.point_num; ++i)
			err[i] = (x[i] - u_exact(t , pos(i)))*10;

		g_line_color(G_RED);
		g_move(pos(0), err[0]);
		for(int i = 0; i < dim; ++i)
			g_plot(pos(i), err[i]);

		//std::cout << std::scientific << integ(err, range.point_num) << " " << t << std::endl;
		std::cerr << "\r" << "a_err = " << std::scientific << err_integ << " t = " << t;
	}while(t > 0);

	g_term();

	FinalizeButcherTable();
}

void* Wave1(double *x, void *param, double *dx)
{
	uint64_t dim = *((uint64_t*)param);
	double dx2inv = 1/((pos(1) - pos(0)));
	dx[0] = ( - x[1])*dx2inv;
	for(unsigned int i = 1; i < dim - 1; ++i)
		dx[i] = (x[i - 1] - x[i + 1])*dx2inv;
	dx[dim - 1] = (x[dim - 2])*dx2inv;
	return 0;
}

void* Wave11(double *x, void *param, double *dx)
{
	uint64_t dim = *((uint64_t*)param);
	double dx2inv = 1/((pos(1) - pos(0)));
	dx[0] = (x[dim - 1] - x[1])*dx2inv;
	for(unsigned int i = 1; i < dim - 1; ++i)
		dx[i] = (x[i - 1] - x[i + 1])*dx2inv;
	dx[dim - 1] = (x[dim - 2] - x[1])*dx2inv;
	return 0;
}

void* Wave21(double *x, void *param, double *dx)
{
	uint64_t dim = *((uint64_t*)param);
	double dx2inv = 1/((pos(1) - pos(0)));
	dx[0] = (x[1] - x[1])*dx2inv;
	for(unsigned int i = 1; i < dim - 1; ++i)
		dx[i] = (x[i - 1] - x[i + 1])*dx2inv;
	dx[dim - 1] = (x[dim - 2] - x[dim - 2])*dx2inv;
	return 0;
}

//3-points
void* Diffusion1(double *x, void *param, double* dx)
{
	uint64_t dim = *((uint64_t*)param);
	double dx2inv = 1/((pos(1) - pos(0))*(pos(1) - pos(0)));
	dx[0] = (-3*x[0] + x[1])*dx2inv;
	for(unsigned int i = 1; i < dim - 1; ++i)
	{
		double xi = x[i];
		dx[i] = (x[i - 1] - 2*x[i] + x[i + 1])*dx2inv;
		if(xi != x[i])
			std::cout << "check" << std::endl;
	}
	dx[dim - 1] = (x[dim - 2] - 3*x[dim - 1])*dx2inv;
	return 0;
}

//3-points
void* Diffusion11(double *x, void *param, double* dx)
{
	uint64_t dim = *((uint64_t*)param);
	double dx2inv = 1/((pos(1) - pos(0))*(pos(1) - pos(0)));
	dx[0] = (x[dim - 1] -2*x[0] + x[1])*dx2inv;
	for(unsigned int i = 1; i < dim - 1; ++i)
		dx[i] = (x[i - 1] - 2*x[i] + x[i + 1])*dx2inv;
	dx[dim - 1] = (x[dim - 2] - 2*x[dim - 1] + x[0])*dx2inv;
	return 0;
}

//3-points
void* Diffusion21(double *x, void *param, double* dx)
{
	uint64_t dim = *((uint64_t*)param);
	double dx2inv = 1/((pos(1) - pos(0))*(pos(1) - pos(0)));
	dx[0] = (x[1] -2*x[0] + x[1])*dx2inv;
	for(unsigned int i = 1; i < dim - 1; ++i)
		dx[i] = (x[i - 1] - 2*x[i] + x[i + 1])*dx2inv;
	dx[dim - 1] = (x[dim - 2] - 2*x[dim - 1] + x[dim - 2])*dx2inv;
	return 0;
}

//5-points
void* Diffusion2(double *x, void *param, double* dx)
{
	uint64_t dim = *((uint64_t*)param);
	double dx2inv = 1/(12*(pos(1) - pos(0))*(pos(1) - pos(0)));
	dx[0] = (-30*x[0] + 16*x[1] - x[2])*dx2inv;
	dx[1] = (16*x[0] - 30*x[1] + 16*x[2] - x[3])*dx2inv;
	for(unsigned int i = 2; i < dim - 2; ++i)
		dx[i] = (-x[i - 2] + 16*x[i - 1] - 30*x[i] + 16*x[i + 1] - x[i + 2])*dx2inv;
	dx[dim - 2] = (-x[dim - 4] + 16*x[dim - 3] - 30*x[dim - 2] + 16*x[dim - 1])*dx2inv;
	dx[dim - 1] = (-x[dim - 3] + 16*x[dim - 2] - 30*x[dim - 1])*dx2inv;
	return 0;
}

double pos(unsigned int index)
{
	double dx = (range.max - range.min)/range.point_num;
	return index*dx + range.min + dx/2;
}
