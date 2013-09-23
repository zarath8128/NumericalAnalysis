#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
#include "GPDriver.h"

using namespace zarath;
using namespace GPDriver;

void ExplicitMethod(double *x, unsigned int len,double dt);
void ExplicitMethod2(double *x, unsigned int len,double dt);

int main()
{
	struct timespec ts;
	int dim = 200;
	double t = 0, dt = 0.5*(0.378 + 0.377)*(2*M_PI/dim)*(2*M_PI/dim);
	ts.tv_sec = 0;
	ts.tv_nsec = 1000000000/1000;
	double d[dim*2];
	for(int i = 0; i < dim; ++i)
		d[2*i] = M_PI*(-1 + i/(double)(dim/2)), d[i*2 + 1] = 0.5*cos(d[2*i]) + 0.5;
	GPData gpd = CreateGPData();
	SetRange(&gpd, -M_PI, M_PI, 0, 1);
	InitializeGP(&gpd);
	while(t < 10)
	{
		Plot(&gpd, d, dim);
		ExplicitMethod2(d, dim, dt);
		t += dt;
		nanosleep(&ts, 0);
	}
	DeleteGPData(&gpd);
	return 0;
}

void ExplicitMethod(double *x, unsigned int len, double dt)
{
	double dx[len];

	dx[0] = (- 2*x[1] + x[3])/pow(((x[2] - x[0])), 2);
	for(unsigned int i = 1; i < len - 1; ++i)
		dx[i] = (x[2*(i - 1) + 1] - 2*x[2*i + 1] + x[2*(i + 1) + 1])/pow((x[2*(i)] - x[2*(i - 1)]), 2);
	dx[len - 1] = (x[2*(len - 1 - 1) + 1] - 2*x[2*(len - 1) + 1])/pow(((x[2*(len - 1)] - x[2*(len - 1 - 1)])), 2);

	for(int i = 0; i < len; ++i)
		x[2*i + 1] += dt*dx[i];
}

void ExplicitMethod2(double *x, unsigned int len,double dt)
{
	double dx[len];
	double dx2 = (x[2] - x[0])*(x[2] - x[0]);

	dx[0] = (-30*x[1] + 16*x[3] - x[5])/(12*dx2);
	dx[1] = (16*x[1] - 30*x[3] + 16*x[5] - x[7])/(12*dx2);
	for(unsigned int i = 2; i < len - 2; ++i)
		dx[i] = (-x[2*(i - 2) + 1] + 16*x[2*(i - 1) + 1] - 30*x[2*i + 1] + 16*x[2*(i + 1) + 1] - x[2*(i + 2) + 1])/(12*dx2);
	dx[len - 2] = (-x[2*(len - 2 - 2) + 1] + 16*x[2*(len - 2 - 1) + 1] - 30*x[2*(len - 2) + 1] + 16*x[2*(len - 2 + 1) + 1])/(12*dx2);
	dx[len - 1] = (-x[2*(len - 1 - 2) + 1] + 16*x[2*(len - 1 - 1) + 1] - 30*x[2*(len - 1) + 1])/(12*dx2);

	for(int i = 0; i < len; ++i)
		x[2*i + 1] += dt*dx[i];
}
