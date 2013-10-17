#include <cstdint>
#include <cmath>
#include "GillMethod.h"
#include <iostream>

using namespace zarath;



extern "C"
{
	double *buf = 0, *k = 0, *y = 0, *q = 0;

	void InitializeGillMethod(uint64_t dim)
	{
		FinalizeGillMethod();
		buf = new double[dim * 3];
		k = buf;
		y = k + dim;
		q = y + dim;
		for(unsigned int i = 0; i < dim; ++i)
			q[i] = 0;
		return;
	}

	void FinalizeGillMethod()
	{
		delete [] buf;
		buf = k = y = q = 0;
		return;
	}

	void *GillMethod(double *start, void *param, double *next, vfunc f, double *h, double *abs_err, double *rel_err)
	{
		uint64_t dim = *((uint64_t*)param);
		double dt = *h, t;

//		/*
		//old ver.
 		f(start, param, k);

		for(unsigned int i = 0; i < dim; ++i)
			y[i] = start[i] + 0.5*dt*k[i];

		f(y, param, q);

		for(unsigned int i = 0; i < dim; ++i)
			y[i] += (1 - sqrt(0.5))*(q[i] - k[i])*dt;

		for(unsigned int i = 0; i < dim; ++i)
			q[i] = (2 - sqrt(2))*q[i] + (-2 + 3*sqrt(0.5))*k[i];

		f(y, param, k);

		for(unsigned int i = 0; i < dim; ++i)
			y[i] += (1 + sqrt(0.5))*(k[i] - q[i])*dt;

		for(unsigned int i = 0; i < dim; ++i)
			q[i] = (2 + sqrt(2))*k[i] + (-2 -3*sqrt(0.5))*q[i];

		f(y, param, k);

		for(unsigned int i = 0; i < dim; ++i)
			next[i] = y[i] + dt*(k[i] * (1./6) - q[i]*(1./3));
//		*/

		//improved ver.
		//decrease rounding error

	/*	
		f(start, param, k);

		for(unsigned int i = 0; i < dim; ++i)
			q[i] += 3*((y[i] = start[i] + (0.5*k[i]*dt - q[i])) - start[i]) - 0.5*k[i]*dt;

		f(y, param, k);

		for(unsigned int i = 0; i < dim; ++i)
			q[i] += 3*((t = y[i] + (1 - sqrt(0.5))*(k[i]*dt- q[i])) - y[i]) - (1 - sqrt(0.5))*k[i]*dt, y[i] = t;

		f(y, param, k);

		for(unsigned int i = 0; i < dim; ++i)
			q[i] += 3*((t = y[i] + (1 + sqrt(0.5))*(k[i]*dt- q[i])) - y[i]) - (1 + sqrt(0.5))*k[i]*dt, y[i] = t;

		f(y, param, k);

		
		for(unsigned int i = 0; i < dim; ++i)
			q[i] += 3*((next[i] = y[i] + (1./6)*(k[i]*dt- 2*q[i])) - y[i]) - 0.5*k[i]*dt;
	*/	

		return 0;
	}
}
