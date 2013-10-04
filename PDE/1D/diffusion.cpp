#include "ODE/RKMethod/ERKMethod.h"
#include "ODE/RKMethod/EulerMethod.h"
#include "ODE/RKMethod/ButcherTable.h"
#include "GPDriver.h"
#include <cmath>
#include <cstdint>
#include <ctime>
#include <iostream>

using namespace zarath;
using namespace GPDriver;

void* Diffusion1(double *x, void *param, double* dx);
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
	uint64_t dim = 400;
	double t = 0, dt = 0, tmax = 7;
	double abs_err = 0, rel_err = 1e-0;
	double xy[2*dim];
	double x[dim];

	range.min = -M_PI/2;
	range.max = M_PI/2;
	range.point_num = dim;

	//3point runge-kutta 0.69986 - 0.69985
	//5point runge-kutta 0.52489 - 0.52488
	dt = 0.501 * ((range.max - range.min)/dim)*((range.max - range.min)/dim);

	for(int i = 0; i < dim; ++i)
		x[i] = cos(pos(i));

	InitializeButcherTable();
	SetButcherTable(GetButcherTable(Euler));

	rkmethod rm = EulerMethod;
	GPData gpd = CreateGPData();
	SetWindow(&gpd, 0, 0, 640, 640);
	SetRange(&gpd, range.min, range.max, -0.2, 1.2);

			for(unsigned int i = 0; i < dim; ++i)
				xy[2*i] = pos(i), xy[2*i + 1] = x[i];
			Plot(&gpd, xy, dim);
	do
	{
		usleep(100);
		rm(x, &dim, x, Diffusion1, &dt, &abs_err, &rel_err);
		if((clock() - tick) > (CLOCKS_PER_SEC/60))
		{
			tick = clock();
			for(unsigned int i = 0; i < dim; ++i)
				xy[2*i] = pos(i), xy[2*i + 1] = x[i];
			Plot(&gpd, xy, dim);
			usleep(100);
			std::cerr << "\rt = " << t;
		}
	}while((t += dt) < tmax);

	std::cerr << std::endl;

	FinalizeButcherTable();
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
	return index*(range.max - range.min)/(range.point_num - 1) + range.min;
}
