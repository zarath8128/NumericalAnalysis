#ifndef ZARATH_APPROXIMATE_POLYMINAL_APPROXIMATE_POLYMINAL_H
#define ZARATH_APPROXIMATE_POLYMINAL_APPROXIMATE_POLYMINAL_H

#ifdef __cplusplus 
#include <cstdint>
#else
#include <stdint.h>
#endif 

#ifdef __cplusplus
extern "C"
{
	namespace zarath
	{
		namespace ApproximatePolyminal
		{
#endif 

			typedef struct 
			{
				uint64_t dim;
				double *x, *inv;
			}Lagrange;

			Lagrange CreateLagrange(const double *x, const double *y, uint64_t dim);
			double LagrangeInterpolation(double x, Lagrange L);
			void DeleteLagrange(Lagrange *L);

			typedef struct 
			{
				uint64_t dim, preserved;
				double *x, *div, *div_buf;
			}Newton;

			Newton CreateNewton(const double *x, const double *y, uint64_t dim);
			double NewtonInterPolation(double x, Newton N);
			void NewtonAdd(double x, double y);
			void DeleteNewton(Newton *N);
#ifdef __cplusplus 
		}
	}
}
#endif 

#endif
