#ifndef ZARATH_ODE_EULER_METHOD_H
#define ZARATH_ODE_EULER_METHOD_H

#include "../ODE.h"

#ifdef __cplusplus
namespace zarath
{
	extern "C"
	{
#endif
		void *EulerMethod(double *strat, void *param, double *next, vfunc f, double *h, double *abs_err, double *rel_err);
		void *EulerMethodAuto(double *strat, void *param, double *next, vfunc f, double *h, double *abs_err, double *rel_err);
		void *EulerMethodRetErr(double *strat, void *param, double *next, vfunc f, double *h, double *abs_err, double *rel_err);

#ifdef __cplusplus
	}
}
#endif

#endif
