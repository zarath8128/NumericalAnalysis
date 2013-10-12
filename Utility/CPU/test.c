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
	return 0;
}
