#ifndef ZARATH_LEQ_ITERATIVE_METHOD_CG_METHOD_H
#define ZARATH_LEQ_ITERATIVE_METHOD_CG_METHOD_H

#ifdef __cplusplus 
#include <cstdint>
#else 
#include <stdint.h>
#endif 

#ifdef __cplusplus 
extern "C" 
{
#endif 

	uint64_t CGMethod(double *A, double *x0, double *b, uint64_t dim, double eps, uint64_t max);

#ifdef __cplusplus 
}
#endif 

#endif 
