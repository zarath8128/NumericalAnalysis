#ifndef ZARATH_ODE_ODE_H
#define ZARATH_ODE_ODE_H

#ifdef __cplusplus
#include <stdint.h>
#include <cmath>
#else
#include <stdint.h>
#include <math.h>
#endif

#ifdef __cplusplus
namespace zarath
{
	extern "C"
	{
#endif

		//ベクトルを引数に取る関数のインターフェース。
		//param[0]はuint64_t型の次元。
		typedef void* (*vfunc)(double *arg, void *param, double *ret);
		//一般的なRnge-Kutta法のインターフェース。abs_err, rel_errは刻み幅(h)の自動制御が有効である場合に用いられる。
		//h, abs_err, rel_errはスカラー値へのポインタ。
		//返り値は追加情報。*((double*)return val) = time step;
		typedef void* (*rkmethod)(double *start, void *param, double *next, vfunc f, double *h, double *abs_err, double *rel_err);
		typedef void* (*odesolver)(const double *x0, void *f_param, double *x1, vfunc f, void *s_param);
#ifdef __cplusplus
		
	}
}
#endif
#endif
