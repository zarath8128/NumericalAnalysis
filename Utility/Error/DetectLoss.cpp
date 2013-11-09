#include "DetectLoss.h"

#define ABS(x) (((x) < 0)?(-(x)):((x)))

using namespace zarath;

extern "C"
{
	DoubleBit CreateDoubleBit(double d)
	{
		DoubleBit db;
		bitdouble bd;
		bd.d = d;
		db.d = d;
		db.sn = (bd.b >> 63);
		db.exp = ((bd.b >> 52) & ((1 << 11) - 1));
		db.sig = (bd.b & ((1L << 52) - 1));
		for(int i = 0; i < 52; ++i)
			db.significant[i] = ((db.sig >> (51 - i)) & 1) + '0';
		db.significant[52] = '\0';
		for(int i = 0; i < 11; ++i)
			db.exponential[i] = ((db.exp >> (10 - i)) & 1) + '0';
		db.exponential[11] = '\0';
		db.sign[0] = db.sn + '0';
		db.sign[1] = '\0';
	
		return db;
	}

	int DetectSignificantLoss(double a, double b)
	{
		DoubleBit A = CreateDoubleBit(a), B = CreateDoubleBit(b);
		uint64_t lsig, ssig, asig, bsig;
		if(A.exp == B.exp)
			asig = (A.sig | (1L << 52)), bsig = (B.sig | (1L << 52));
		else if(A.exp > B.exp)
			asig = (A.sig | (1L << 52)), bsig = ((B.sig | (1L << 52) >> (A.exp - B.exp)));
		else
			bsig = (B.sig | (1L << 52)), asig = ((A.sig | (1L << 52) >> (B.exp - A.exp)));
		
		int i = 53;
		lsig = ((asig > bsig)?(asig):(bsig));
		ssig = ((asig > bsig)?(bsig):(asig));
		uint64_t sig = lsig - ssig;
		if((!sig) || (A.sn != B.sn))
			return 0;
		while(i-- > 0)
			if(sig & (1L << i))
				break;
		return 52 - i;
	}

	int DetectInformationLoss(double a, double b)
	{
		if(a == 0 || b == 0)
			return 0;
		DoubleBit A = CreateDoubleBit(a), B = CreateDoubleBit(b);
		return (ABS(A.exp - B.exp) > 54)?(54):(ABS(A.exp - B.exp));
	}
}

/*int DigitAlignment(Double &a, Double &b)
{
	return 0;
}*/

