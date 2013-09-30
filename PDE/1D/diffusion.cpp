#include "ODE/RKMethod/ERKMethod.h"
#include "ODE/RKMethod/EulerMethod.h"
#include "ODE/RKMethod/ButcherTable.h"
#include "GPDriver.h"
#include <cmath>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <unistd.h>

using namespace zarath;
using namespace GPDriver;

void* Wave1(double *x, void *param, double *dx);
void* Wave11(double *x, void *param, double *dx);
void* Wave21(double *x, void *param, double *dx);
void* Diffusion1(double *x, void *param, double* dx);
void* Diffusion11(double *x, void *param, double* dx);
void* Diffusion21(double *x, void *param, double* dx);
void* Diffusion2(double *x, void *param, double* dx);
double pos(unsigned int index);

struct
{
	double min, max;
	unsigned int point_num;
}range;

int main()
{
	clock_t tick = clock();
	uint64_t dim = 400, w = 200, c = 0;
	double t = 0, dt = 0, tmax = 20;
	double abs_err = 0, rel_err = 1e-13;
	double xy[2*dim];
	double x[dim];
	timespec slp;
	slp.tv_sec = 0;
	slp.tv_nsec = 1000000*26;

	range.min = -M_PI/2;
	range.max = M_PI/2;
	range.point_num = dim;

	//3point runge-kutta 0.69983 - 0.69984 time:20
	//5point runge-kutta 0.52487 - 0.52488 time:20
	dt = 0.000001;//0.5 * ((range.max - range.min)/dim)*((range.max - range.min)/dim);

	for(int i = 0; i < dim; ++i)
		x[i] = cos(pos(i));

	InitializeButcherTable();
	SetButcherTable(GetButcherTable(RungeKutta));

	rkmethod rm = ERKMethod;
	GPData gpd = CreateGPData();
	SetWindow(&gpd, 0, 0, 640, 640);
	SetRange(&gpd, range.min, range.max, -2, 2);

			for(unsigned int i = 0; i < dim; ++i)
				xy[2*i] = pos(i), xy[2*i + 1] = x[i];
			Plot(&gpd, xy, dim);
	do
	{
		if(c++ % w == 0)
			rm(x, &dim, x, Wave21, &dt, &abs_err, &rel_err), t += dt;
		if(abs(clock() - tick)/(double)CLOCKS_PER_SEC > (1./60))
		{
			tick = clock();
			for(unsigned int i = 0; i < dim; ++i)
				xy[2*i] = pos(i), xy[2*i + 1] = x[i];
			Plot(&gpd, xy, dim);
			std::cerr << "\rt = " << t << std::fflush;
		}
	}while(t < tmax);

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
	return index*(range.max - range.min)/(range.point_num - 1) + range.min;
}
