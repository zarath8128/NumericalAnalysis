#include "Matrix.h"

using namespace zarath::Matrix;

int main()
{
	constexpr int row = 10;
	constexpr int col = 12;

	Matrix m(row, col);

	for(int r = 0; r < row; ++r)
	for(int c = 0; c < col; ++c)
		m(r, c) = 1./(1 + r + c);

	std::cout << m;
	return 0;
}
