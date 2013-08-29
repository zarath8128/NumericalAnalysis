#ifndef ZARATH_ODE_ODE_H
#define ZARATH_ODE_ODE_H

#ifdef __cplusplus
namespace zarath
{
	extern "C"
	{
#endif
		//ベクトルを引数に取る関数のインターフェース。
		typedef double (*r_vfunc)(double *arg, void *param);
		typedef double (*v_vfunc)(double *arg, void *param, double *ret);
		//一般的なRnge-Kutta法のインターフェース。abs_err, rel_errは刻み幅(h)の自動制御が有効である場合に用いられる他、推定された誤差を返す。
		typedef double (*rkmethod)(double *start, void *param, double *next, double *h, double *abs_err, double *rel_err);
#ifdef __cplusplus
	}
}
#endif
#endif
