#include <stdio.h>
#include <math.h>
#include "DetectLoss.h"

void printbit(double a)
{
	bitdouble b;
	b.d = a;
	for(int i = 0; i < 1; ++i)
		printf("%d", (int)((b.b >> (63 - i)) & 1));
	printf(" ");
	for(int i = 1; i < 12; ++i)
		printf("%d", (int)((b.b >> (63 - i)) & 1));
	printf(" ");
	for(int i =12; i < 64; ++i)
		printf("%d", (int)((b.b >> (63 - i)) & 1));
	printf(" %f\n", a);
}

int main()
{
	double a = 0.0122715, b = 0.0736144, c, eps = 1e-12;
	printf("%g - %g:%d\n", a, b, DetectSignificantLoss(a, b));
	DoubleBit A = CreateDoubleBit(a), B = CreateDoubleBit(b);
	printf("%f:%s, %f:%s\n", a, A.significant, b, B.significant);
	b = 0.06;
	printf("%g - %g:%d\n", a, b, DetectSignificantLoss(b, a));
	b = 0.00092;
	printf("%g - %g:%d\n", a, b, DetectSignificantLoss(a, b));
	a = 0.112344, b = 0.112343;
	printf("%g - %g:%d\n", a, b, DetectSignificantLoss(a, b));
	b = 4000, a = 0.02, c = 0.02;
	printf("a = %g, b = %g, c = %g\n", a, b, c);
	printf("b - root(b*b - 4*a*c):%d\n", DetectSignificantLoss(b, sqrt(b*b - 4*a*c)));

	printf("\n\n---------------------\n\n");

	bitdouble aa, bb;
	aa.d = a = 0.0122715;
	bb.d = b = 0.06;
	printf("S");
	printf(" ");
	for(int i = 0; i < 11; ++i)
		printf("E");
	printf(" ");
	for(int i = 0; i < 52; ++i)
		printf("S");
	printf("\n");
	
	printbit(1);
	printbit(1.5);
	printbit(1.25);
	printbit(-1);
	printbit(-1.5);
	printbit(-1.25);
	printbit(2);
	printbit(2.5);
	printbit(2.25);

	printf("\n");
	printf("%g - %g:%d\n", 1.5, 1.25, DetectSignificantLoss(1.5, -1.25));
	printbit(1.5 - 1.25);
	printf("\n");

	printbit(a);
	printbit(b);
	printf("\n");
	
	printbit(a*4);
	printbit(b);
	printbit(b - a);
	

	return 0;
}
