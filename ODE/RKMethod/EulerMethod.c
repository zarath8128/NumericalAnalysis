#include "EulerMethod.h"
#include <stdio.h>

void *EulerMethod(double *start, void *param, double *next, vfunc f, double *h, double *abs_err, double *rel_err)
{
	f(start, param, next);
	for(int i = 0; i < ((uint64_t*)param)[0]; ++i)
		next[i] *= *h, next[i] += start[i];
	return 0;
}

void *EulerMethodAuto(double *start, void *param, double *next, vfunc f, double *h, double *abs_err, double *rel_err)
{
	uint64_t dim = ((uint64_t*)param)[0];
	double temp[dim];
	double temp2[dim];
	double e_max = 0, a_err = *abs_err, r_err = *rel_err, t_err, t = 0;
	static double H;
	do
	{
		t = e_max = 0;
		f(start, param, temp2);
		for(int i = 0; i < dim; ++i)
			next[i] = start[i] + 0.5 * *h * temp2[i], temp[i] = start[i] + *h * temp2[i];

		f(next, param, temp2);
		for(int i = 0; i < dim; ++i)
			next[i] += 0.5 * *h *temp2[i];

		for(int i = 0; i < dim; ++i)
		{
			t_err = fabs(temp[i] - next[i]) + next[i] * fabs((temp[i] - next[i])/next[i]);
			t = ((t_err > e_max)?(fabs(next[i])):(t));
			e_max = ((t_err > e_max)?(t_err):(e_max));
		}
		H = *h;
		*h *= 0.95 * pow((a_err + t*r_err)/e_max, 0.5);
	}while(e_max > (a_err + r_err * t));
	
	return &H;
}
