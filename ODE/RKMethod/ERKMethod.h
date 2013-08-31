#ifndef ZARATH_ODE_ERKMETHOD_H
#define ZARATH_ODE_ERKMETHOD_H

#ifdef __cplusplus
#endif

#include "ButcherTable.h"

#ifdef __cplusplus
namespace zarath
{
	extern "C"
	{
#endif
		extern ButcherTable bt;
		void SetButcherTable(ButcherTable butcher);
	 
#ifdef __cplusplus
	}
}
#endif

#endif
