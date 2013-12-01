#include <iostream>
#include <ctime>
#include <thread>
#include "CGMethod.h"

void matmulsub(double *m, double *v, double *ans, uint64_t dim, uint64_t start, uint64_t length)
{
	for(uint64_t i = 0; i < length; ++i)
	{
		ans[i] = 0;
		for(uint64_t j = 0; j < dim; ++j)
			ans[i] += m[(start + i)*dim + j]*v[j];
	}
}

void matmul(double *m, double *v, double *ans, uint64_t dim)
{
	uint64_t worker_num = std::thread::hardware_concurrency();
	std::thread **worker = new std::thread*[worker_num];
	for(uint64_t i = 0; i < worker_num; ++i)
		worker[i] = new std::thread(matmulsub, m, v, ans + (dim/worker_num)*i, dim, (dim/worker_num)*i, dim/worker_num);
	for(uint64_t i = (dim/worker_num)*worker_num; i < dim; ++i)
	{
		ans[i] = 0;
		for(uint64_t j = 0; j < dim; ++j)
			ans[i] += m[i*dim + j]*v[i];
	}
	for(uint64_t i = 0; i < worker_num; ++i)
		worker[i]->join(), delete worker[i];
	delete [] worker;
}

void simple(double *m, double *v, double *ans, uint64_t dim)
{
	for(uint64_t i = 0; i < dim; ++i)
	{
		ans[i] = 0;
		for(uint64_t j = 0; j < dim; ++j)
			ans[i] += m[i*dim + j]*v[j];
	}
}

int main()
{
	constexpr uint64_t dim = 50000;
	double *A = new double[dim*dim], *x = new double[dim], *b = new double[dim];

	clock_t t = clock();
	for(uint64_t i = 0; i < dim; ++i)
	{
		x[i] = 1;
		for(uint64_t j = 0; j < dim; ++j)
			A[i*dim + j] = i;
	}
	clock_t s = clock();

	std::cout << "start" << std::endl;
	clock_t t0 = clock();
	matmul(A, x, b, dim);
	clock_t t1 = clock();
	std::cout << "end" << std::endl;
	clock_t t11 = clock();
	simple(A, x, b, dim);
	clock_t t2 = clock();
	for(uint64_t i = 0; i < 50; ++i)
		std::cout << b[i] << std::endl;
	std::cout << "multhd:" << (t1 - t0)/(double)CLOCKS_PER_SEC << "\nsimple:" << (t2 - t11)/(double)CLOCKS_PER_SEC << std::endl;

	delete [] A;
	delete [] x;
	delete [] b;

	return 0;
}
