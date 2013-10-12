#ifndef ZARATH_UTILITY_CPU_CPU_H
#define ZARATH_UTILITY_CPU_CPU_H

#ifdef __cplusplus
#include<cstdint>
#else
#include<stdint.h>
#endif

typedef uint32_t MXCSR;

#ifdef __cplusplus
extern "C"
{
#endif

	//flags
	#define MXCSR_IE(mxcsr) ((mxcsr >> 0) & 1) //invalid opelation
	#define MXCSR_DE(mxcsr) ((mxcsr >> 1) & 1) //denormal
	#define MXCSR_ZE(mxcsr) ((mxcsr >> 2) & 1) //divide by 0
	#define MXCSR_OE(mxcsr) ((mxcsr >> 3) & 1) //over flow
	#define MXCSR_UE(mxcsr) ((mxcsr >> 4) & 1) //under flow
	#define MXCSR_PE(mxcsr) ((mxcsr >> 5) & 1) //precision
	//mask
	#define MXCSR_IM(mxcsr) ((mxcsr >> 7) & 1)
	#define MXCSR_DM(mxcsr) ((mxcsr >> 8) & 1) //denormal
	#define MXCSR_ZM(mxcsr) ((mxcsr >> 9) & 1) //divide by 0
	#define MXCSR_OM(mxcsr) ((mxcsr >>10) & 1) //over flow
	#define MXCSR_UM(mxcsr) ((mxcsr >>11) & 1) //under flow
	#define MXCSR_PM(mxcsr) ((mxcsr >>12) & 1) //precision

	#define MXCSR_RC(mxcsr) ((mxcsr >>13) & 3) //rounding control
	#define MXCSR_ZF(mxcsr) ((mxcsr >>15) & 1) //zero flash
	void GetMXCSR(MXCSR *mxcsr);

#ifdef __cplusplus
}
#endif

#endif
