#include <cstdio>
#include <cmath>
#include "CosSum.h"

using namespace zarath;

int main()
{
	FILE *gp = popen("gnuplot -persist", "w");
	double min = -1, max = 1;
	double a[10], v[10], p[10], dx = 0.01, x = min - dx;
	a[0] = 1;
	v[0] = 0;
	p[0] = 0;

	fprintf(gp, "plot '-' w l\n");
	while((x += dx) < max)
		fprintf(gp, "%f %f\n", x, CosSum(x, a, v, p, 1));
	fprintf(gp, "e\n");
	fflush(gp);
	fclose(gp);
	return 0;
}
