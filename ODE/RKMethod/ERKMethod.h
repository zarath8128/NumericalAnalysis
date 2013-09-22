#ifndef ZARATH_ODE_ERKMETHOD_H
#define ZARATH_ODE_ERKMETHOD_H

#ifdef __cplusplus
#endif

#include "ButcherTable.h"
#include "../ODE.h"

#ifdef __cplusplus
namespace zarath
{
	extern "C"
	{
#endif
		extern ButcherTable bt;
		void SetButcherTable(ButcherTable butcher);
		void ClearButcherTable();
		void *ERKMethod(double *start, void *param, double *next, vfunc f, double *h, double *abs_err, double *rel_err);
	 
#ifdef __cplusplus
	}
}
#endif

#endif
