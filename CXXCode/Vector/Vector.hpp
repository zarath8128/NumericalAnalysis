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
			:public AbstractVector<F, V>
		{
		public:
			virtual N &operator[](uint64_t index) = 0;
			constexpr virtual explicit operator uint64_t() final {return dim;}
		};

		template<uint64_t dim>
		class Vector
			:public NumericVector<double, double, Vector<dim>, dim>
		{
		public:
			Vector():val(new double[dim]){}
			Vector(double *a, double *b, void (*ope)(double *, double *, double *)):Vector(){ope(a, b, val);}
			Vector(const Vector &v):Vector(){for(uint64_t i = 0; i < dim; ++i)val[i] = v.val[i];}
			Vector(Vector &&v):val(v.val){v.val = nullptr;}
			~Vector(){delete [] val;}

			double &operator[](uint64_t index){return val[index];} 
			const Vector &operator=(Vector &v)
			{
				for(uint64_t i = 0; i < dim - 2*(rem?1:0); i += 2)
				{
					val[i] = v.val[i];
					val[i + 1] = v.val[i + 1];
					//val[i + 2] = v.val[i + 2];
					//val[i + 3] = v.val[i + 3];
				}
				for(uint64_t i = 0; i < rem; ++i)
					val[2*quo + i] = v.val[2*quo + i];
				return *this;
			}
			const Vector &operator=(Vector &&v){val = v.val; v.val = nullptr;return *this;}
			bool operator==(Vector &v){for(uint64_t i = 0; i < dim; ++i)if(v[i] != val[i])return false;return true;}
			bool operator!=(Vector &v){return !(*this == v);}
			Vector operator+(Vector &v){return Vector(val, v.val, Add);}
			const Vector &operator+=(Vector &v){for(uint64_t i = 0; i < dim; ++i)val[i] += v[i]; return *this;}
			Vector operator-(Vector &v){return Vector(val, v.val, Sub);}
			const Vector &operator-=(Vector &v){for(uint64_t i = 0; i < dim; ++i)val[i] -= v[i]; return *this;}
			Vector operator*(double &v){return Vector(val, &v, Mul);}
			Vector operator*(double v){return Vector(val, &v, Mul);}
			const Vector &operator*=(double &v){for(uint64_t i = 0; i < dim; ++i)val[i] *= v; return *this;}
		private:
			static void Add(double *a, double *b, double *ans){for(uint64_t i = 0; i < dim; ++i)ans[i] = a[i] + b[i];}
			static void Sub(double *a, double *b, double *ans){for(uint64_t i = 0; i < dim; ++i)ans[i] = a[i] - b[i];}
			static void Mul(double *a, double *b, double *ans){for(uint64_t i = 0; i < dim; ++i)ans[i] = a[i] * *b;}
			static constexpr uint64_t rem = dim % 2;
			static constexpr uint64_t quo = dim / 2;
			double *val;
		};

		template<uint64_t dim>
		constexpr uint64_t Vector<dim>::rem;

		template<uint64_t dim>
		constexpr uint64_t Vector<dim>::quo;

		template<uint64_t dim>
		std::ostream &operator<<(std::ostream &dest, Vector<dim> &src)
		{
			for(uint64_t i = 0; i < dim - 1; ++i)
				dest << src[i] << "\n";
			dest << src[dim - 1];
			return dest;
		}

		template<uint64_t dim>
		std::ostream &operator<<(std::ostream &dest, Vector<dim> &&src)
		{
			for(uint64_t i = 0; i < dim - 1; ++i)
				dest << src[i] << "\n";
			dest << src[dim - 1];
			return dest;
		}
	}
}

#endif
