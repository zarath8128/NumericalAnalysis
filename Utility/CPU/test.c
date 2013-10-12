#include <stdio.h>
#include "CPU.h"

int main()
{
	MXCSR m;
	m = 0;
	printf("mxcsr = %d\n", m);
	GetMXCSR(&m);
	printf("mxcsr = %d\n", m);
	printf("rouding is %d\n", MXCSR_RC(m));
	printf("00000000000000001111111111111111\n");
	uint32_t t = 8064;
	for(int i = 0; i < 32; ++i)
		printf("%d", (t >> (31 - i)) & 1);
	printf("\n");
	for(int i = 0; i < 32; ++i)
		printf("%d", (m >> (31 - i)) & 1);
	printf("\n");
	return 0;
}
