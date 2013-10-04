#include "Matrix.h"
#include <iomanip>

namespace zarath
{
	namespace Matrix
	{
		std::ostream &operator<<(std::ostream &dest, Matrix &m)
		{
			for(int i = 0; i < m.Row(); ++i)
			{
				for(int j = 0; j < m.Column(); ++j)
					dest << "\t" << std::scientific << std::setw(8) << m(i, j);
				dest << "\n";
			}
			return dest;
		}
	}
}
