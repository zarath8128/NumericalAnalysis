#include "ApproximatePolyminal.h"

extern "C"
{
	using namespace zarath::ApproximatePolyminal;
	Lagrange CreateLagrange(const double *x, const double *y, uint64_t dim)
	{
		Lagrange L;
		L.dim = dim;
		L.x = new double[dim];
		L.inv = new double[dim];
		for(uint64_t i = 0; i < dim; ++i)
		{
			L.x[i] = x[i];
			L.inv[i] = 1;
			for(uint64_t j = 0; j < i; ++j)
				L.inv[i] *= x[i] - x[j];
			for(uint64_t j = i + 1; j < dim; ++j)
				L.inv[i] *= x[i] - x[j];
			L.inv[i] = y[i]/L.inv[i];
		} 
		return L;
	}

	void DeleteLagrange(Lagrange *L)
	{
		delete [] L->x;
		delete [] L->inv;
		L->x = L->inv = nullptr;
	}

	double LagrangeInterpolation(double x, Lagrange L)
	{
		double ret = 0;
		for(uint64_t i = 0; i < L.dim; ++i)
		{
			double buf = L.inv[i];
			for(uint64_t j = 0; j < i; ++j)
				buf *= x - L.x[j];
			for(uint64_t j = i + 1; j < L.dim; ++j)
				buf *= x - L.x[j];
			ret += buf;
		}
		return ret;
	}
}
