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
	uint64_t dim = *(uint64_t*)param;
	double buf[dim], buf2[dim];
	ERKMethod(x, param, buf, f, dt, abs_err, rel_err);
	f(buf, param, buf2);
	for(int i = 0; i < dim; ++i)
		next_x[i] = x[i] + buf2[i]* *dt;
}

struct
{
	double min, max;
	unsigned int point_num;
	double D;
}range;

double u_exact(double t, double x){return exp(-range.D*t)*cos(x);}
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
	uint64_t dim = 50, w = 2000, c = 0, n = 1;
	double t = 0, dt = 0, tmax = 20;
	double abs_err = 0, rel_err = 1e-0;
	double xy[2*dim];
	double x[dim];
	double ue[dim];

	range.min = -M_PI/2;
	range.max = M_PI/2;
	range.point_num = dim;
	range.D = 1;

	//3point runge-kutta 0.69983 - 0.69984 time:20
	//5point runge-kutta 0.52487 - 0.52488 time:20
	double DT = dt = 0.75 * ((range.max - range.min)/dim)*((range.max - range.min)/dim);

	for(int i = 0; i < dim; ++i)
		x[i] = cos(pos(i));

	InitializeButcherTable();
	SetButcherTable(GetButcherTable(RKF45));

	rkmethod rm = ERKMethod;

	g_init("plot", 200, 200);
	g_device(G_DISP);

	g_def_scale(0, range.min - 1, range.max + 1, range.min - 1, range.max + 1, 0, 0, 200, 200);

	g_sel_scale(0);
	do
	{
		g_sleep(1./60);
		g_cls();

		g_line_color(G_BLACK);
		g_move(range.min, 0);
		g_plot(range.max, 0);

		g_move(0, range.min);
		g_plot(0, range.max);

		t += *(double*)rm(x, &dim, x, Diffusion1, &dt, &abs_err, &rel_err);
	 	dt = DT;

		g_line_color(G_GREEN);
		g_move(pos(0), x[0]);
		for(int i = 0; i < dim; ++i)
			g_plot(pos(i), x[i]);
		
		double err[dim];
		for(int i = 0; i < range.point_num; ++i)
			err[i] = fabs(x[i] - (ue[i] = u_exact(t, pos(i))));

		g_line_color(G_BLUE);
		g_move(pos(0), ue[0]);
		for(int i = 0; i < dim; ++i)
			g_plot(pos(i), ue[i]);


		std::cout << std::scientific << integ(err, range.point_num) << " " << t << std::endl;
		std::cerr << "\r" << "r_err = " << std::scientific << integ(err, range.point_num)/integ(ue, dim) << " t = " << t;
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
}

void* Wave11(double *x, void *param, double *dx)
{
	uint64_t dim = *((uint64_t*)param);
	double dx2inv = 1/((pos(1) - pos(0)));
	dx[0] = (x[dim - 1] - x[1])*dx2inv;
	for(unsigned int i = 1; i < dim - 1; ++i)
		dx[i] = (x[i - 1] - x[i + 1])*dx2inv;
	dx[dim - 1] = (x[dim - 2] - x[1])*dx2inv;
}

void* Wave21(double *x, void *param, double *dx)
{
	uint64_t dim = *((uint64_t*)param);
	double dx2inv = 1/((pos(1) - pos(0)));
	dx[0] = (x[1] - x[1])*dx2inv;
	for(unsigned int i = 1; i < dim - 1; ++i)
		dx[i] = (x[i - 1] - x[i + 1])*dx2inv;
	dx[dim - 1] = (x[dim - 2] - x[dim - 2])*dx2inv;
}

//3-points
void* Diffusion1(double *x, void *param, double* dx)
{
	uint64_t dim = *((uint64_t*)param);
	double dx2inv = 1/((pos(1) - pos(0))*(pos(1) - pos(0)));
	dx[0] = (-2*x[0] + x[1])*dx2inv;
	for(unsigned int i = 1; i < dim - 1; ++i)
		dx[i] = (x[i - 1] - 2*x[i] + x[i + 1])*dx2inv;
	dx[dim - 1] = (x[dim - 2] - 2*x[dim - 1])*dx2inv;
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
}

double pos(unsigned int index)
{
	double dx = (range.max - range.min)/range.point_num;
	return index*dx + range.min + dx/2;
}
