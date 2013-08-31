#ifndef ZARATH_ODE_BUTCHER_TABLE_H
#define ZARATH_ODE_BUTCHER_TABLE_H

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#ifdef __cplusplus
namespace zarath
{
	extern "C"
	{
#endif
		typedef struct tag_BucherTable
		{
			void *buf;
			double *c;
			double *b;
			double **a;
			uint64_t stage;
			uint64_t embed;			
		}ButcherTable;

		typedef enum tag_RKMethodType
		{
			Euler,
		}RKMethodType;

		extern ButcherTable euler;

		void InitializeButcherTable();
		ButcherTable GetButcherTable(RKMethodType type);
		void FinalizeButcherTable();

		ButcherTable CreateERKButcherTable(uint64_t stage, uint64_t embed);
		void DeleteERKButcherTable(ButcherTable *b);

#ifdef __cplusplus
	}
}
#endif

#endif
