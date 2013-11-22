#ifndef ZARATH_CXXCODE_VECTOR_VECTOR_HPP
#define ZARATH_CXXCODE_VECTOR_VECTOR_HPP

#include <cstdint>
#include <iostream>

namespace zarath
{
	namespace Vector
	{
		template<class F, class V>
		class AbstractVector
		{
		public:
			virtual const V &operator=(V &v) = 0;
			virtual bool operator==(V &v) = 0;
			virtual bool operator!=(V &v) = 0;
			virtual V operator+(V &v) = 0;
			virtual const V &operator+=(V &v) = 0;
			virtual V operator*(F &v) = 0;
			virtual const V &operator*=(F &v) = 0;
		};

		template<class F, class N, class V, uint64_t dim>
		class NumericVector
			:AbstractVector<F, V>
		{
		public:
			virtual N &operator[](uint64_t index) = 0;
			constexpr virtual operator uint64_t() final {return dim;}
		};

		template<uint64_t dim>
		class Vector
			:NumericVector<double, double, Vector<dim>, dim>
		{
		public:
			Vector():val(new double[dim]){std::cout << 11 << std::endl;}
			Vector(const Vector &v):val(new double[dim]){for(uint64_t i = 0; i < dim; ++i)val[i] = v.val[i]; std::cout << 13 << std::endl;}
			Vector(Vector &&v):val(v.val){v.val = nullptr;std::cout << 1000 << std::endl;}
			~Vector(){delete [] val; std::cout << 12 << std::endl;}

			double &operator[](uint64_t index){return val[index];} 
			const Vector &operator=(Vector &v){for(uint64_t i = 0; i < dim; ++i)val[i] = v[i];std::cout << "into" << std::endl;return *this;}
			const Vector &operator=(Vector &&v){val = v.val; v.val = nullptr; std::cout << "move" << std::endl;return *this;}
			bool operator==(Vector &v){for(uint64_t i = 0; i < dim; ++i)if(v[i] != val[i])return false;return true;}
			bool operator!=(Vector &v){return !(*this == v);}
			Vector operator+(Vector &v){Vector<dim> ret; for(uint64_t i = 0; i < dim; ++i)ret[i] = val[i] + v[i]; std::cout << "add" << std::endl;return ret;}
			const Vector &operator+=(Vector &v){for(uint64_t i = 0; i < dim; ++i)val[i] += v[i]; return *this;}
			Vector operator*(double &v){Vector<dim> ret;for(uint64_t i = 0; i < dim; ++i)ret[i] = val[i]*v; return ret;}
			const Vector &operator*=(double &v){for(uint64_t i = 0; i < dim; ++i)val[i] *= v; return *this;}
		private:
			double *val;
		};

		template<uint64_t dim>
		std::ostream &operator<<(std::ostream &dest, Vector<dim> &src)
		{
			for(int i = 0; i < dim - 1; ++i)
				dest << src[i] << "\n";
			dest << src[dim - 1];
			return dest;
		}
	}
}

#endif
