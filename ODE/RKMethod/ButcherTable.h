#ifndef ZARATH_ODE_BUTCHER_TABLE_H
#define ZARATH_ODE_BUTCHER_TABLE_H

#ifdef __cplusplus
#include <stdint.h>
#include <iostream>
#else
#include <stdint.h>
#endif

#ifdef __cplusplus
namespace zarath
{
	extern "C"
	{
#endif
		/*
			buf = {double c[stage], double a[stage - 1][x], double b[embed][stage], double *a[stage - 1], double *b[embed], uint64_t *precision[embed]}
		*/
		typedef struct tag_BucherTable
		{
			void *buf;
			double *c;
			double **b;
			double **a;
			uint64_t stage;
			uint64_t embed;	
			uint64_t *precision;
		}ButcherTable;

		typedef enum tag_RKMethodType
		{
			Euler,
			RungeKutta,
			RungeKutta3_8,
			RKF45,
		}RKMethodType;

		extern ButcherTable euler;

		void InitializeButcherTable();
		ButcherTable GetButcherTable(RKMethodType type);
		void FinalizeButcherTable();

		ButcherTable CreateERKButcherTable(uint64_t stage, uint64_t embed);
		void DeleteERKButcherTable(ButcherTable *b);

#ifdef __cplusplus
	}
	std::ostream &operator<<(std::ostream &dest, ButcherTable &b);
}
#endif

#endif
