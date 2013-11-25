#include <stdio.h>
#include <math.h>
#include "ApproximatePolyminal.h"

int main()
{
	double min = -5, max = 5;
	uint64_t dim = 15;
	double x[dim];
	double y[dim];
	double px;
	for(uint64_t i = 0; i < dim; ++i)
		x[i] = i*(max - min)/(dim - 1) + min, y[i] = cos(x[i]) - 2*sin(1.2*x[i]);
	Lagrange L = CreateLagrange(x, y, dim);

	for(uint64_t i = 0; i < dim*300; ++i)
		printf("%f %.15f\n", (px = i*(max - min)/(dim*300 - 1) + min), LagrangeInterpolation(px, L));
		//printf("%f %f\n", x[i], LagrangeInterpolation(x[i], L));
		//printf("%f %f\n", L.x[i], L.inv[i]);

	DeleteLagrange(&L);
	return 0;
}
