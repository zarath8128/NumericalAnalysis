#ifndef ZARATH_MATH_MATRIX_MATRIX_H
#define ZARATH_MATH_MATRIX_MATRIX_H

#include <iostream>
#include "Matrix_base.hpp"

namespace zarath
{
	namespace Matrix
	{
		class Matrix
			:Matrix_base<double>
		{
		public:
			Matrix(unsigned int r, unsigned int c):r(r), c(c), buf(new double[r*c]){};
			~Matrix(){delete [] buf;};

			double &operator()(int r, int c){return buf[r*this->c + c];};
			int Row(){return r;};
			int Column(){return c;};

		private:
			double *buf;
			const unsigned int r, c;
		};

		std::ostream &operator<<(std::ostream &dest, Matrix &m);
	}
}

#endif
