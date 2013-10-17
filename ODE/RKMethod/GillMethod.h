#ifndef ZARATH_ODE_GILL_METHOD_H
#define ZARATH_ODE_GILL_METHOD_H

#include "../ODE.h"

#ifdef __cplusplus
namespace zarath
{
	extern "C"
	{
#endif

		void *GillMethod(double *strat, void *param, double *next, vfunc f, double *h, double *abs_err, double *rel_err);
		void InitializeGillMethod(uint64_t dim);
		void FinalizeGillMethod();
#ifdef __cplusplus
	}
}
#endif

#endif
