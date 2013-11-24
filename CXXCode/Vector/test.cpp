#include "Vector.hpp"
#include <iostream>
#include <ctime>

using namespace zarath::Vector;

template<uint64_t dim>
class vector
{
public:
	vector():val(new double[dim]){}
	~vector(){delete [] val;}

	constexpr double &operator[](uint64_t index) const{return val[index];}
	constexpr const vector &operator=(const vector &v){for(uint64_t i = 0; i < dim; ++i)val[i] = v.val[i];return *this;}
private:
	double *val;
};

int main()
{
	constexpr uint64_t times = 40;
	constexpr uint64_t dim = 40000000;
	double *s = new double[dim], *t = new double[dim];
	Vector<dim> v, w;
	vector<dim> a, b;
	for(uint64_t i = 0; i < dim; ++i)
	{
		v[i] = s[i] = a[i] = 0;
		w[i] = t[i] = b[i] = 1./i;
	}

	clock_t t0 = clock();
	for(uint64_t time = 0; time< times; ++time)
		v = w;
	clock_t t1 = clock();
	for(uint64_t time = 0; time < times; ++time)
	for(uint64_t i = 0; i < dim; ++i)
		s[i] = t[i];
	clock_t t2 = clock();
	//for(uint64_t i = 0; i < dim; ++i)
	//	a[i] = b[i];
	for(uint64_t time = 0; time < times; ++time)
	a = b;
	clock_t t3 = clock();

	std::cout << "Vector   time = " << (t1 - t0)/(double)CLOCKS_PER_SEC << std::endl;
	std::cout << "double[] time = " << (t2 - t1)/(double)CLOCKS_PER_SEC << std::endl;
	std::cout << "simple v time = " << (t3 - t2)/(double)CLOCKS_PER_SEC << std::endl;

	for(uint64_t i = 0; i < dim; ++i)
	{
		if(v[i] != s[i])
		{
			std::cout << "failed index " << i << "\n";
			break;
		}
	}

	std::cout << "check is end" << std::endl;
	
	for(uint64_t i = 0; i < dim; ++i)
	{
		if(a[i] != s[i])
		{
			std::cout << "failed index " << i << "\n";
			break;
		}
	}

	std::cout << "check is end" << std::endl;
	
	delete [] s;
	delete [] t;

	return 0;
}
