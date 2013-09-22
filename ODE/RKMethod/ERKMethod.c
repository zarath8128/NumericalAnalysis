#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ERKMethod.h"

#define ABS(x) (((x) < 0)?(-(x)):(x))
#define MAX(x, y) (((x) > (y))?(x):(y))

ButcherTable bt = {0, 0, 0, 0, 0, 0};

void SetButcherTable(ButcherTable butcher)
{
	bt = butcher;
}

void ClearButcherTable()
{
}

void *ERKMethod(double *start, void *param, double *next, vfunc f, double *h, double *abs_err, double *rel_err)
{
	static double H;
	uint64_t stage = bt.stage, dim = ((uint64_t*)param)[0];
	double *buf = (double*)malloc(sizeof(double) * (stage*(1 + bt.embed) + 1)*dim);
	double *k[stage];
	double *x1[bt.embed];

	for(uint64_t i = 0; i < stage; ++i)
		k[i] = buf + (i + 1)*dim;

	for(uint64_t i = 0; i < bt.embed; ++i)
		x1[i] = buf + (stage + 1)*dim + i*dim;

next_loop:

	f(start, param, k[0]);

	for(uint64_t i = 1; i < stage; ++i)
	{
		for(uint64_t j = 0; j < dim; ++j)
			buf[j] = start[j];

		for(uint64_t j = 0; j < i; ++j)
			for(uint64_t p = 0; p < dim; ++p)
				buf[p] += *h * k[j][p] * bt.a[i][j];

		f(buf, param, k[i]);
	}

	for(uint64_t i = 0; i < bt.embed; ++i)
	{
		for(uint64_t j = 0; j < dim; ++j)
			x1[i][j] = start[j];

		for(uint64_t j = 0; j < stage; ++j)
			for(uint64_t p = 0; p < dim; ++p)
				x1[i][p] += *h * k[j][p] * bt.b[i][j];
	}

	H = *h;

	if(bt.embed > 1)
	{
		double err[bt.embed];
	
		for(int i = 1; i < bt.embed; ++i)
		{
			err[i] = 0;
			for(int j = 0; j < dim; ++j)
			{
				err[0] = ABS(x1[0][j] - x1[i][j])/(*abs_err + MAX(ABS(x1[0][j]), ABS(x1[i][j])) * *rel_err);
				err[i] = ((err[0] > err[i])?(err[0]):(err[i]));
			}
		}

		if(err[1] == 0)
		{
			goto end;
		}

		*h *= 0.9*pow(err[1], -1./bt.precision[1]);

		if(H > *h)
			goto next_loop;
	}
end:
	for(int i = 0; i < dim; ++i)
		next[i] = x1[0][i];

	free(buf);

	return &H;
}
