#ifndef ZARATH_MATH_VECTOR_VECTOR_BASE_HPP
#define ZARATH_MATH_VECTOR_VECTOR_BASE_HPP

namespace zarath
{
	namespace Vector
	{
		template<class T>
		class Vector_base
		{
		public:
			virtual T &operator()(int i) = 0;
			virtual int length() = 0;
		};
	}
}

#endif
