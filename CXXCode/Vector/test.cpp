#include "Vector.hpp"

using namespace zarath::Vector;

int main()
{
	Vector<40> v, w;
	for(int i = 0; i < 4; ++i)
		v[i] = i*i*0.1, w[i] = i + 0.2;
	Vector<40> u = v + w;
	return 0;
}
