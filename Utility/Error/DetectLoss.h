#ifndef ZARATH_UTILITY_ERROR_DETECT_LOSS_H
#define ZARATH_UTILITY_ERROR_DETECT_LOSS_H

#include <stdint.h>

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
int DetectLoss(double x);
int DetectSignificantLoss(double a, double b);

#endif
