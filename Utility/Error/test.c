#include <stdio.h>
#include <math.h>
#include "DetectLoss.h"

int main()
{
	double a = 1.2, b = 1.2, c, eps = 1e-12;
	printf("%g - %g:%d\n", a, b, DetectSignificantLoss(a, b));
	b = 0.06;
	printf("%g - %g:%d\n", a, b, DetectSignificantLoss(a, b));
	b = 0.00092;
	printf("%g - %g:%d\n", a, b, DetectSignificantLoss(a, b));
	a = 0.112344, b = 0.112343;
	printf("%g - %g:%d\n", a, b, DetectSignificantLoss(a, b));
	b = 4000, a = 0.02, c = 0.02;
	printf("a = %g, b = %g, c = %g\n", a, b, c);
	printf("b - root(b*b - 4*a*c):%d\n", DetectSignificantLoss(b, sqrt(b*b - 4*a*c)));
	return 0;
}
