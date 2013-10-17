#include <iostream>
#include <cmath>
#include <ctime>

#include "EulerMethod.h"
#include "ERKMethod.h"
#include "GillMethod.h"

using namespace zarath;

uint64_t f_count = 0;

void *f(double *arg, void *param, double *ret)
{
	++f_count;
	for(int i = 0; i < ((uint64_t*)param)[0]; ++i)
		ret[i] = (10*i + 1.000000000001)*arg[i];
	return 0;
}

constexpr double ttt(double x)
{
	return sqrt(x);
}

int main()
{
	InitializeButcherTable();

	//SetButcherTable(GetButcherTable(RKF45));
	SetButcherTable(GetButcherTable(RungeKutta));

	rkmethod proc = GillMethod;//ERKMethod;//EulerMethodAuto;
	int64_t dim = 30;
	double x1[dim], x2[dim];
	double *x = x1, *y = x2, *temp;
	double a_err = 0, r_err = 1e-12;
	double h = 0.00001, t = 0;
	uint64_t count = 0;

	InitializeGillMethod(dim);

	for(int i = 0; i < dim; ++i)
		x[i] = 1;

	clock_t t0 = clock();
	while(t < 0.01)
	{
		count++;
		temp = (double*)proc(x, &dim, y, f, &h, &a_err, &r_err);
		t += ((temp == 0)?(h):(*temp));
		temp = x;
		x = y;
		y = temp;
	}
	clock_t t1 = clock();
	std::cout << "time" << (t1 - t0)/(double)CLOCKS_PER_SEC << std::endl;
	std::cout << t << std::endl;
	std::cout << count << std::endl;
	std::cout << f_count << std::endl;
	for(int i = 0; i < dim; ++i)
	{
		std::cout << "x(0)  = " << 1 << std::endl;
		std::cout << "x(" << t << ") = " << x[i] << std::endl;
		std::cout << "x_tru = " << exp((10*i + 1.000000000001)*t) << std::endl;
		std::cout << "r_err = " << fabs((x[i] - exp((10*i + 1.000000000001)*t))/ exp((10*i + 1.000000000001)*t)) << "...:" << pow(1 + fabs((x[i] - exp((10*i + 1.000000000001)*t))/ exp((10*i + 1.000000000001)*t)), 1./count) - 1 <<  std::endl << std::endl;
	}

	FinalizeGillMethod();
	FinalizeButcherTable();

	return 0;
}
