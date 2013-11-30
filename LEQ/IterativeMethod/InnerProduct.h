#ifndef ZARATH_LEQ_ITERATIVE_METHOD_INNER_PRODUCT_H
#define ZARATH_LEQ_OTERATIVE_METHOD_INNER_PRODUCT_H

#ifdef __cplusplus 
#include <cstdint>
#else 
#include <stdint.h>
#endif 

#ifdef __cplusplus
extern "C" 
{
#endif

	double InnerProduct(double *vector1, double *matrix, double *vector2, uint64_t dim);

#ifdef __cplusplus 
}
#endif 

#endif 
