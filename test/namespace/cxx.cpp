#include <stdio.h>

extern "C"
void cxx()
{
	double as[1];
	for(int i = 0; i < 100; ++i)
		as[i] = 0;
	printf("cxx\n");
	return;
}
