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
				N.div[i] = (N.div[j] - N.div[j - 1])/(x[j] - x[j - i]);
		}
		return N;
	}
}
