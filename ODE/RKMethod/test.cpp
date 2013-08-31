#include <iostream>
#include <cmath>

#include "EulerMethod.h"
#include "ERKMethod.h"

using namespace zarath;

uint64_t f_count = 0;

void *f(double *arg, void *param, double *ret)
{
	++f_count;
	for(int i = 0; i < ((uint64_t*)param)[0]; ++i)
		ret[i] = (10*i + 1)*arg[i];
	return 0;
}

int main()
{
	rkmethod proc = EulerMethodAuto;
	int64_t dim = 30;
	double x1[dim], x2[dim];
	double *x = x1, *y = x2, *temp;
	double a_err = 0, r_err = 1e-4;
	double h = 0.000005, t = 0;
	uint64_t count = 0;
	ButcherTable b;

	for(int i = 0; i < dim; ++i)
		x[i] = 1;

	while(t < 1)
	{
		count++;
		temp = (double*)proc(x, &dim, y, f, &h, &a_err, &r_err);
		t += ((temp == 0)?(h):(*temp));
		temp = x;
		x = y;
		y = temp;
	}
	std::cout << t << std::endl;
	std::cout << count << std::endl;
	std::cout << f_count << std::endl;
	for(int i = 0; i < dim; ++i)
	{
		std::cout << "x(0)  = " << 1 << std::endl;
		std::cout << "x(10) = " << x[i] << std::endl;
		std::cout << "x_tru = " << exp(10*i + 1) << std::endl;
		std::cout << "r_err = " << fabs((x[i] - exp(10*i + 1))/ exp(10*i + 1)) << "...:" << fabs((x[i] - exp(10*i + 1))/ exp(10*i + 1))/count <<  std::endl << std::endl;
	}

	InitializeButcherTable();
	FinalizeButcherTable();

	return 0;
}
