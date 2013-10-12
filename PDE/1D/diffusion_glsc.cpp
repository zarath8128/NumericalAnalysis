#include "ODE/RKMethod/ERKMethod.h"
#include "ODE/RKMethod/EulerMethod.h"
#include "ODE/RKMethod/ButcherTable.h"
#include <cmath>
#include <stdint.h>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <unistd.h>
#include <glsc.h>

using namespace zarath;

void* Diffusion1(double *x, void *param, double* dx);
void* Diffusion2(double *x, void *param, double* dx);
double pos(unsigned int index);

double d12345;

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
	uint64_t dim = 128;
	double t = 0, dt = 0;
	double abs_err = 1e-1, rel_err = abs_err;
	double next[dim];
	double x[dim];
	double sym_err = 0, x_sym_err;
	double *tdt;

	range.min = -0.5;
	range.max = 0.5;
	range.point_num = dim;
	range.D = 1;

	//3point runge-kutta 0.69983 - 0.69984 time:20
	//5point runge-kutta 0.52487 - 0.52488 time:20
	double DT = dt = 0.75 * ((range.max - range.min)/dim)*((range.max - range.min)/dim);

	for(unsigned int i = 0; i < dim; ++i)
		x[i] = cos(M_PI*pos(i));

	InitializeButcherTable();
	SetButcherTable(GetButcherTable(RKF45));

	rkmethod rm = ERKMethod;//EulerMethodAuto;//ERKMethod;

	g_init("plot", 150, 100);
	g_device(G_DISP);

	g_def_scale(0, range.min - margin, range.max + margin, -1 - margin, 1 + margin, 0, 0, 150, 100);

	g_sel_scale(0);
	do
	{
		g_sleep(0.1);
		//g_sleep(G_STOP);
		g_cls();

		g_line_color(G_BLACK);
		g_move(range.min, 0);
		g_plot(range.max, 0);

		g_move(0, range.min);
		g_plot(0, range.max);

		x_sym_err = sym_err = 0;
		Diffusion1(x, &dim, next);
		for(unsigned int i = 0; i < dim; ++i)
			sym_err += fabs(next[i] - next[dim - 1 - i]), x_sym_err += fabs(x[i] - x[dim - 1 - i]);
		sym_err *= 0.5;
		x_sym_err *= 0.5;

		tdt = (double*)rm(x, &dim, next, Diffusion1, &dt, &abs_err, &rel_err);
		t += ((tdt)?(*tdt):(dt));
		for(unsigned int i = 0; i < dim; ++i)
			x[i] = next[i];
	 	//dt = DT;

		for(unsigned int i = 0; i < dim/2; ++i)
			next[i] = (x[i] + x[i + 1])/2;
		for(unsigned int i = dim/2; i < dim; ++i)
			next[i] = (x[i - 1] + x[i])/2;
		

		g_line_color(G_GREEN);
		g_move(pos(0), x[0]);
		for(unsigned int i = 0; i < dim; ++i)
			g_plot(pos(i), next[i]);		

		double err[dim];
		for(unsigned int i = 0; i < range.point_num; ++i)
			err[i] = fabs(x[i] - u_exact(t , pos(i)));

		double err_integ = integ(err, dim);

		g_line_color(G_BLUE);
		g_move(pos(0), u_exact(t, pos(0)));
		for(unsigned int i = 0; i < dim; ++i)
			g_plot(pos(i), u_exact(t, pos(i)));

		for(unsigned int i = 0; i < range.point_num; ++i)
			err[i] = (x[i] - x[dim - 1 - i])*10;//(x[i] - u_exact(t , pos(i)))*10;

		g_line_color(G_RED);
		g_move(pos(0), err[0]);
		for(unsigned int i = 0; i < dim; ++i)
			g_plot(pos(i), err[i]);

		//std::cout << std::scientific << integ(err, range.point_num) << " " << t << std::endl;
		std::cerr << "\r" << "a_err = " << std::scientific << err_integ << " t = " << t << " sym_err = " << sym_err
			<< " x_sym_err = " << x_sym_err;
		printf("d12345 = %15.15f", d12345);
	}while(t > 0);

	g_term();

	FinalizeButcherTable();
}

//3-points
void* Diffusion1(double *x, void *param, double* dx)
{
	uint64_t dim = *((uint64_t*)param);
	double dx2inv = 1/((pos(1) - pos(0))*(pos(1) - pos(0))); 
	dx[0] = (-3*x[0] + x[1])*dx2inv;
	for(unsigned int i = 1; i < dim - 1; ++i)
	{
		double a = x[i- 1], b = x[i], c = x[i + 1];	
		//dx[i] = (a + c - 2*b)*dx2inv;
		dx[i] = ((c - b) + (a - b))*dx2inv;
		//dx[i] = (-2*x[i] + x[i - 1] + x[i + 1])*dx2inv;
		//dx[i] = (x[i - 1] - 2*x[i] + x[i + 1])*dx2inv;
		//dx[i] = (x[i - 1] +(- 2*x[i] + x[i + 1]))*dx2inv;
		//dx[i] = 0.5*((a - 2*b + c) + (c - 2*b + a))*dx2inv;
		//d12345 = (i == 30)?(d12345):(dx[i]);
	}
	dx[dim - 1] = (x[dim - 2] - 3*x[dim - 1])*dx2inv;
	return 0;
}

//5-points
void* Diffusion2(double *x, void *param, double* dx)
{
	uint64_t dim = *((uint64_t*)param);
	double dx2inv = 1/(12*(pos(1) - pos(0))*(pos(1) - pos(0)));
	dx[0] = ((-46*x[0] - x[2]) + 17*x[1])*dx2inv;
	dx[1] = (17*x[0] + 16*x[2] + (- 30*x[1] - x[3]))*dx2inv;
	for(unsigned int i = 2; i < dim - 2; ++i)
		dx[i] = ((-x[i - 2] - x[i + 2] - 30*x[i]) + (16*x[i - 1] + 16*x[i + 1]))*dx2inv;
	dx[dim - 2] = ((-x[dim - 4] - 30*x[dim - 2]) + (17*x[dim - 1] + 16*x[dim - 3]))*dx2inv;
	dx[dim - 1] = ((-x[dim - 3] - 46*x[dim - 1]) + 17*x[dim - 2])*dx2inv;
	return 0;
}

double pos(unsigned int index)
{
	double dx = (range.max - range.min)/range.point_num;
	return index*dx + range.min + dx/2;
}
