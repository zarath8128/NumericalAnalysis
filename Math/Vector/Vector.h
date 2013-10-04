#ifndef ZARATH_MATH_VECTOR_VECTOR_H
#define ZARATH_MATH_VECTOR_VECTOR_H

#include "Vector_base.hpp"
#include <iostream>

namespace zarath
{
	namespace Vector
	{
		class Vector
			:Vector_base<double>
		{
		public:
			Vector(unsigned int len):len(len), buf(new double[len]){}

			double &operator()(int i){return buf[i];}
			int length(){return len;}
		private:
			double *buf;
			const unsigned int len;
		};

		std::ostream &operator<<(std::ostream &dest, Vector &v);
	}
}

#endif
