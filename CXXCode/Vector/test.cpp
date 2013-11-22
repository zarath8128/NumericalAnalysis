#include "Vector.hpp"

using namespace zarath::Vector;

int main()
{
	Vector<4> v, w;
	for(int i = 0; i < 4; ++i)
		v[i] = i*i*0.1, w[i] = i + 0.2;
	Vector<4> u;
	u = v + w;
	std::cout << v << std::endl << std::endl;
	std::cout << w << std::endl << std::endl;
	std::cout << u << std::endl << std::endl;
	return 0;
}
