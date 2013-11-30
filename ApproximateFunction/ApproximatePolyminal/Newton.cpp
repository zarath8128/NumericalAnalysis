#include "ApproximatePolyminal.h"

extern "C"
{
	using namespace zarath::ApproximatePolyminal;

	Newton CreateNewton(const double *x, const double *y, uint64_t dim)
	{
		Newton N;
		N.dim = dim;
		N.preserved = dim*1.5;
		N.x = new double[N.preserved];
		N.div = new double[N.preserved];
		N.div_buf = new double[N.preserved];
		for(uint64_t i = 0; i < dim; ++i)
		{
			N.x[i] = x[i];
			N.div[i] = y[i];
		}

		for(uint64_t i = 0; i < dim; ++i)
		{
			for(uint64_t j = dim - 1; j > i; --j)
				N.div[j] = (N.div[j] - N.div[j - i - 1])/(x[j] - x[j - i - 1]);
			N.div[i] = N.div[i + 1];
			N.div\buf[i] = N.div[dim - 1 - i];
		}
		return N;
	}

	double NewtonInterpolation(double x, Newton N)
	{
		double ret = 0;
		for(uint64_t i = 0; i < N.dim; ++i)
		{
			double buf = N.div[i];
			for(uint64_t j = 0; j < i; ++j)
				buf *= (x - x[j]);
			ret += buf;
		}
		return ret;
	}

	void DeleteNewton(Newton *N)
	{
		delete [] N->x;
		delete [] N->div;
		delete [] N->div_buf;
		N->x = N->div = N->div_buf = nullptr;
	}
}
