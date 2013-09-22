#include <stdlib.h>
#include "ButcherTable.h"

#ifdef __cplusplus
namespace zarath
{
#endif

	ButcherTable euler, rk_c, rk3_8, rkf45;

	void InitializeButcherTable()
	{
		//Euler Method
		euler = CreateERKButcherTable(1, 1);
		euler.c[0] = 0;
		euler.b[0][0] = 1;
		euler.precision[0] = 2;

		//Classical Runge-Kutta Method
		rk_c = CreateERKButcherTable(4, 1);
		rk_c.precision[0] = 5;
		rk_c.c[0] = 0;
		rk_c.c[1] = 1./2;
		rk_c.c[2] = 1./2;
		rk_c.c[3] = 1;
		rk_c.a[1][0] = 1./2;
		rk_c.a[2][0] = 0;
		rk_c.a[2][1] = 1./2;
		rk_c.a[3][0] = 0;
		rk_c.a[3][1] = 0;
		rk_c.a[3][2] = 1;
		rk_c.b[0][0] = 1./6;
		rk_c.b[0][1] = 1./3;
		rk_c.b[0][2] = 1./3;
		rk_c.b[0][3] = 1./6;

		//Runge-Kutta 3/8 Method
		rk3_8 = CreateERKButcherTable(4, 1);
		rk3_8.precision[0] = 5;
		rk3_8.c[0] = 0;
		rk3_8.c[1] = 1./3;
		rk3_8.c[2] = 2./3;
		rk3_8.c[3] = 1;
		rk3_8.a[1][0] = 1./3;	
		rk3_8.a[2][0] = -1./3;	
		rk3_8.a[2][1] = 1;	
		rk3_8.a[3][0] = 1;	
		rk3_8.a[3][1] = -1;	
		rk3_8.a[3][2] = 1;
		rk3_8.b[0][0] = 1./8;
		rk3_8.b[0][1] = 3./8;
		rk3_8.b[0][2] = 3./8;
		rk3_8.b[0][3] = 1./8;

		//Runge-Kutta-Fehlberg 4(5) Method
		rkf45 = CreateERKButcherTable(6, 2);
		rkf45.c[0] = 0;
		rkf45.c[1] = 1./4;
		rkf45.c[2] = 3./8;
		rkf45.c[3] = 12./13;
		rkf45.c[4] = 1;
		rkf45.c[5] = 1./2;
		rkf45.a[1][0] = 1./4;
		rkf45.a[2][0] = 3./32;
		rkf45.a[2][1] = 9./32;
		rkf45.a[3][0] = 1932./2197;
		rkf45.a[3][1] = -7200./2197;
		rkf45.a[3][2] = 7296./2197;
		rkf45.a[4][0] = 439./216;
		rkf45.a[4][1] = -8;
		rkf45.a[4][2] = 3680./513;
		rkf45.a[4][3] = -845./4104;
		rkf45.a[5][0] = -8./27;
		rkf45.a[5][1] = 2;
		rkf45.a[5][2] = -3544./2565;
		rkf45.a[5][3] = 1859./4104;
		rkf45.a[5][4] = -11./40;
		rkf45.precision[0] = 6;
		rkf45.b[0][0] = 16./135;
		rkf45.b[0][1] = 0;
		rkf45.b[0][2] = 6656./12825;
		rkf45.b[0][3] = 28561./56430;
		rkf45.b[0][4] = -9./50;
		rkf45.b[0][5] = 2./55;
		rkf45.precision[1] = 5;
		rkf45.b[1][0] = 25./216;
		rkf45.b[1][1] = 0;
		rkf45.b[1][2] = 1408./2565;
		rkf45.b[1][3] = 2197./4104;
		rkf45.b[1][4] = -1./5;
		rkf45.b[1][5] = 0;
	}

	ButcherTable GetButcherTable(RKMethodType type)
	{
		ButcherTable dammy = {0, 0, 0, 0, 0, 0, 0};
		switch(type)
		{
		case Euler:
			return euler;
		case RungeKutta:
			return rk_c;
		case RungeKutta3_8:
			return rk3_8;
		case RKF45:
			return rkf45;
		default:
			return dammy;
		}
	}

	void FinalizeButcherTable()
	{
		DeleteERKButcherTable(&euler);
		DeleteERKButcherTable(&rk3_8);
		DeleteERKButcherTable(&rkf45);
	}

	ButcherTable CreateERKButcherTable(uint64_t stage, uint64_t embed)
	{
		ButcherTable b = {0, 0, 0, 0, 0, 0};
		b.stage = stage;
		b.embed = embed;
		b.buf = malloc(sizeof(double)*(b.stage + b.stage*(b.stage - 1)/2 + b.stage*b.embed) + sizeof(void*)*(b.stage - 1 + b.embed + b.embed));
		b.a = (double**)((double*)b.buf + b.stage + b.stage*(b.stage - 1)/2 + b.stage*b.embed) - 1;
		b.c = (double*)b.buf;
		for(int i = 1; i < b.stage; ++i)
			b.a[i] = b.c + b.stage + i*(i - 1)/2;
		b.b = b.a + b.stage;
		for(int i = 0; i < b.embed; ++i)
			b.b[i] = b.c + b.stage + (b.stage - 1)*b.stage/2 + i*b.stage;
		b.precision = (uint64_t*)b.b + b.embed;
		return b;
	}

	void DeleteERKButcherTable(ButcherTable *b)
	{
		free(b->buf);
		b->stage = b->embed = 0;
		b->buf = 0;
		b->c = 0;
		b->a = b->b = 0;
		b->precision = 0;
	}

#ifdef __cplusplus

	std::ostream &operator<<(std::ostream &dest, ButcherTable &b)
	{
		if(b.stage == 0)
		{
			dest << "this is not available table..." << std::endl;
			return dest;
		}

		dest << "stage:\t" << b.stage << "\n";
		dest << "embed:\t" << b.embed << "\n";
		if(b.c[0] == 0)
		{
			std::cout << "k0 = f(t0, x0)\n";
			for(int i = 1; i < b.stage; ++i)
			{
				dest << "k" << i << " = " << "f(t0 + " << b.c[i] << "h, x0 + h(";
				dest << b.a[i][0] << "k0";
				for(int j = 1; j < i; ++j)
					dest << " + " << b.a[i][j] << "k" << j;
				dest << "))\n";
			}
		}

		for(int i = 0; i < b.embed; ++i)
		{
			dest << "x1_" << i << " = x0 + h(";
			dest << b.b[i][0] << "k0";
			for(int j = 1; j < b.stage; ++j)
				dest << " + " << b.b[i][j] << "k" << j ;
			dest << ")\n";
			dest << "local precision:\t" << b.precision[i] << "\n";
		}
		return dest;
	}
}

#endif
