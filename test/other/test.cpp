#include <iostream>
#include <iomanip>

int main()
{
	double y = 1, k = 0.023, q = 0.001, t;

	std::cout << std::setprecision(16) << (t = y + (0.5*k - q)) - y << std::endl;

	return 0;
}
