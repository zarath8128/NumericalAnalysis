#ifndef ZARATH_MATH_MATRIX_BASE_HPP
#define ZARATH_MATH_MATRIX_BASE_HPP

namespace zarath
{
	namespace Matrix
	{
		template<class T>
		class Matrix_base
		{
		public:
			virtual T &operator()(int r, int c) = 0;
			virtual int Row() = 0;
			virtual int Column() = 0;
		};
	}
}

#endif
