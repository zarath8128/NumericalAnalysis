#include <stdio.h>
#include "InnerProduct.h"

int main()
{
	double v[] = {1, 2, 3};
	double w[] = {2, 3, 4};
	double m[] = {0, 1, 0, 0, 0, 1, 1, 0, 0};
	printf("%f\n", InnerProduct(v, 0, w, 3));
	printf("%f\n", InnerProduct(v, m, w, 3));
}
