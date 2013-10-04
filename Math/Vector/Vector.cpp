#include "Vector.h"
#include <iomanip>

namespace zarath
{
	namespace Vector
	{
		std::ostream &operator <<(std::ostream &dest, Vector &v)
		{
			for(int i = 0; i < v.length(); ++i)
				dest << "\t" << std::scientific << std::setw(8) << v(i);
		}
	}
}
