#include "InnerProduct.h"
#include <iostream>

extern "C"
{
	double InnerProduct(double *v1, double *m, double *v2, uint64_t d)
	{
		double ret = 0, buf = 0;
		if(m)
			for(uint64_t i = 0; i < d; ret += buf*v1[i++], buf = 0)
				for(uint64_t j = 0; j < d; ++j)
					buf += m[i*d + j]*v2[j];
		else
			for(uint64_t i = 0; i < d; ++i)
				ret += v1[i]*v2[i];
		return ret;
	}
}
