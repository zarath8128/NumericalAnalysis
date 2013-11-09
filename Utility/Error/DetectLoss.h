#ifndef ZARATH_UTILITY_ERROR_DETECT_LOSS_H
#define ZARATH_UTILITY_ERROR_DETECT_LOSS_H

#include <stdint.h>

#ifdef __cplusplus
namespace zarath
{
	extern "C"
	{
#endif

		typedef struct tag_doublebit
		{
			double d;
			uint64_t sig;//significant
			char significant[53];
			char exponential[12];
			char sign[2];
			uint16_t exp;
			uint8_t sn;
		}DoubleBit;

		typedef union tag_bitdouble
		{
			double d;
			uint64_t b;
		}bitdouble;

		DoubleBit CreateDoubleBit(double d);
		int DetectSignificantLoss(double a, double b);
		int DetectInformationLoss(double a, double b);
#ifdef __cplusplus
	}
	int DigitAlignment(DoubleBit &a, DoubleBit &b);
}
#endif
#endif
