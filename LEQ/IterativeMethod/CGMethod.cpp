#include "CGMethod.h"
#include "InnerProduct.h"
#include <iostream>

void mul(double*, double*, double*, uint64_t);

extern "C" 
{
	uint64_t CGMethod(double *A, double *x, double *b, uint64_t dim, double eps, uint64_t max)
	{
		max = (max?max:dim);
		double *r = new double[dim];
		double *p = new double[dim];
		double *Ap = new double[dim];
		mul(A, x, Ap, dim);


		for(uint64_t i = 0; i < dim; ++i)
			r[i] = p[i] = b[i] - Ap[i];

		for(uint64_t k = 0; k < max; ++k)
		{
			mul(A, p, Ap, dim);
			double alpha = InnerProduct(r, 0, p, dim)/InnerProduct(p, 0, Ap, dim);
			double beta = 1./InnerProduct(r, 0, r, dim);

			for(uint64_t i = 0; i < dim; ++i)
				x[i] += alpha*p[i], r[i] -= alpha*Ap[i];

			double gamma = InnerProduct(r, 0, r, dim);
			if(gamma < eps)
			{
				delete [] r;
				delete [] p;
				delete [] Ap;
				return k + 1;
			}
			beta *= gamma;
			for(uint64_t i = 0; i < dim; ++i)
				p[i] = r[i] + beta*p[i];
		}
		delete [] r;
		delete [] p;
		delete [] Ap;
		return max;
	}
}

void mul(double *mat, double *v, double *ans, uint64_t dim)
{
	for(uint64_t i = 0; i < dim; ++i)
	{
		ans[i] = 0;
		for(uint64_t j = 0; j < dim; ++j)
			ans[i] += mat[i*dim + j]*v[j];
	}
}
