#include <iostream>
#include <cmath>
#include <ctime>
#include "Math.h"


int main()
{
	double base = 3, exp = 2;
	double temp = 0;
	int count = 100000;
	std::cout << pow(base, exp) << std::endl;
	clock_t t0 = clock();
	for(int i = 0; i < count; ++i)
		temp += std::pow(base, exp);
	clock_t t1 = clock();
	std::cout << "time\t:" << (t1 - t0)/(double)CLOCKS_PER_SEC << std::endl;
	std::cout << "val\t:" << temp << std::endl;
	temp = 0;
	t0 = clock();
	for(int i = 0; i < count; ++i)
		temp += zarath::pow(base, exp);
	t1 = clock();
	std::cout << "time\t:" << (t1 - t0)/(double)CLOCKS_PER_SEC << std::endl;
	std::cout << "val\t:" << temp << std::endl;
	return 0;
}
